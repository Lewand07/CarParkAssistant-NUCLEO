#include "park_assist_task.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Private Function Declarations */
static void send_car_instruction(Car_Direction direction, Car_Steering steering);
static bool check_obstacle(const Sensor_Data* sensor_data);
static uint32_t calculate_spot_depth(int32_t wall_distance);
static bool detect_parking_spot(const Sensor_Data* side_sensor_data, uint32_t required_depth,
                                uint8_t* valid_columns, bool is_right_sensor);
static uint32_t get_adjusted_delay(uint32_t base_delay_ms, int32_t distance);
static void predict_data(Sensor_Data* sensor_data, uint8_t speed, Car_Direction direction,
                         uint32_t delay);

void ParkAssistTask(void) {
    static Sensor_Data current_data[SENSORS_NUMBER];
    static ParkingState parking_state = PARKING_IDLE;
    static uint8_t valid_columns_left = 0U;
    static uint8_t valid_columns_right = 0U;
    uint32_t left_spot_depth = MIN_PARKING_SPOT_DEPTH_MM;
    uint32_t right_spot_depth = MIN_PARKING_SPOT_DEPTH_MM;
    bool left_spot_detected = false;
    bool right_spot_detected = false;
    int32_t wall_distance = 0;
    bool is_predicted = true;
    Car_Direction current_direction = CAR_FORWARD;

    vTaskDelay(pdMS_TO_TICKS(5000));  // wait for sensors to stabilize
    for (;;) {
        /* Lock mutex to access shared sensors_data */
        if (osOK == osMutexAcquire(SensorsDataMutexHandle, DATA_MUTEX_TIMEOUT_MS)) {
            memcpy(current_data, sensors_data, sizeof(current_data));
            osMutexRelease(SensorsDataMutexHandle);
            is_predicted = false;
        } else {
            printf("Predicting data...\n\r");
            uint16_t current_speed = (current_direction == CAR_STOP) ? 0U : CAR_SPEED_MM_S;
            predict_data(current_data, current_speed, current_direction, DATA_MUTEX_TIMEOUT_MS);
            is_predicted = true;
            uint8_t i, row, col;
            for (i = 0; i < SENSORS_NUMBER; ++i) {
                if (i != SENSOR_L3_FRONT && i != SENSOR_L3_REAR) {
                    continue;
                }
                printf("Sensor[%d] Data:\n\r", i);
                for (row = 0; row < sensors_data[i].rows; row++) {
                    for (col = 0; col < sensors_data[i].cols; col++) {
                        printf("%5d ", sensors_data[i].distances[row][col]);
                    }
                    printf("\n\r");
                }
            }
        }

        /* Parking Algorithm state machine*/
        switch (parking_state) {
            case PARKING_IDLE:
                if (check_obstacle(&current_data[SENSOR_L3_FRONT])) {
                    send_car_instruction(CAR_STOP, CAR_CENTER);
                    break;
                }
                send_car_instruction(CAR_FORWARD, CAR_CENTER);

                /* Detect parking spot only on real data */
                if (!is_predicted) {
                    left_spot_detected =
                            detect_parking_spot(&current_data[SENSOR_L5_LEFT], left_spot_depth,
                                                &valid_columns_left, false);
                    right_spot_detected =
                            detect_parking_spot(&current_data[SENSOR_L5_RIGHT], right_spot_depth,
                                                &valid_columns_right, true);
                }

                // recalculating spot depth if no spot detected
                if (!left_spot_detected && valid_columns_left == 0) {
                    left_spot_depth =
                            calculate_spot_depth(current_data[SENSOR_L3_LEFT].distances[0][0]);
                }
                if (!right_spot_detected && valid_columns_right == 0) {
                    right_spot_depth =
                            calculate_spot_depth(current_data[SENSOR_L3_RIGHT].distances[0][0]);
                }
                if (left_spot_detected || right_spot_detected) {
                    wall_distance = right_spot_detected ? right_spot_depth : left_spot_depth;
                    wall_distance -= MIN_PARKING_SPOT_DEPTH_MM;
                    send_car_instruction(CAR_STOP, CAR_CENTER);
                    parking_state = PARKING_ALIGN_FRONT;
                }
                break;
            case PARKING_ALIGN_FRONT:
                printf("Parking spot detected!\n\r");
                if (!check_obstacle(&current_data[SENSOR_L3_FRONT])) {
                    send_car_instruction(CAR_FORWARD, CAR_CENTER);
                    vTaskDelay(pdMS_TO_TICKS(BASE_ALIGN_DELAY_MS));
                }
                send_car_instruction(CAR_STOP, CAR_CENTER);
                parking_state = PARKING_REVERSE_STEER;
                break;
            case PARKING_REVERSE_STEER:
                send_car_instruction(CAR_BACKWARD, right_spot_detected ? CAR_RIGHT : CAR_LEFT);
                // get 45 degree angle
                vTaskDelay(BASE_STEER_DELAY_MS);
                send_car_instruction(CAR_STOP, CAR_CENTER);
                parking_state = PARKING_REVERSE_CENTER;
                break;
            case PARKING_REVERSE_CENTER:
                send_car_instruction(CAR_BACKWARD, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(get_adjusted_delay(BASE_REVERSE_DELAY_MS, wall_distance)));
                send_car_instruction(CAR_STOP, CAR_CENTER);
                parking_state = PARKING_ADJUST;
                break;
            case PARKING_ADJUST:
                send_car_instruction(CAR_BACKWARD, right_spot_detected ? CAR_LEFT : CAR_RIGHT);
                vTaskDelay(pdMS_TO_TICKS(BASE_ADJUST_DELAY_MS));
                send_car_instruction(CAR_STOP, CAR_CENTER);
                parking_state = PARKING_COMPLETE;
                break;
            case PARKING_COMPLETE:
                send_car_instruction(CAR_FORWARD, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(400U));
                send_car_instruction(CAR_STOP, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(BASE_COMPLETE_DELAY_MS));
                parking_state = PARKING_DRIVE_AWAY;
                break;
            case PARKING_DRIVE_AWAY:
                send_car_instruction(CAR_BACKWARD, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(300U));
                send_car_instruction(CAR_STOP, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(BASE_DRIVE_AWAY_DELAY_MS - 200U));
                send_car_instruction(CAR_FORWARD, right_spot_detected ? CAR_LEFT : CAR_RIGHT);
                vTaskDelay(pdMS_TO_TICKS(BASE_DRIVE_AWAY_DELAY_MS));
                send_car_instruction(CAR_FORWARD, CAR_CENTER);
                vTaskDelay(pdMS_TO_TICKS(BASE_DRIVE_AWAY_DELAY_MS));
                send_car_instruction(CAR_FORWARD, right_spot_detected ? CAR_RIGHT : CAR_LEFT);
                vTaskDelay(pdMS_TO_TICKS(BASE_DRIVE_AWAY_DELAY_MS));
                send_car_instruction(CAR_STOP, CAR_CENTER);
                parking_state = PARKING_RESET;
                break;
            case PARKING_RESET:
                valid_columns_left = 0U;
                valid_columns_right = 0U;
                left_spot_detected = false;
                right_spot_detected = false;
                parking_state = PARKING_IDLE;
                break;
            default:
                break;
        }

        // /* Delay between checks */
        // vTaskDelay(pdMS_TO_TICKS(SENSOR_SCAN_DELAY_MS));
    }
}

/**
 * @brief Check for obstacles in front of the car.
 * @param front_sensor_data Pointer to the front sensor data.
 * @return true if an obstacle is detected, false otherwise.
 */
static bool check_obstacle(const Sensor_Data* sensor_data) {
    bool obstacle_detected = false;

    for (uint8_t row = 0U; row < sensor_data->rows; row++) {
        for (uint8_t col = 0U; col < sensor_data->cols; col++) {
            if ((sensor_data->distances[row][col] != SENSOR_INVALID_DATA) &&
                (sensor_data->distances[row][col] < MIN_OBSTACLE_DISTANCE_MM)) {
                obstacle_detected = true;
                break;
            }
        }
        if (obstacle_detected) {
            break;
        }
    }

    return obstacle_detected;
}

/**
 * @brief Send car instructions to the message queue.
 * @param direction Direction of the car (e.g., FORWARD, BACKWARD).
 * @param steering Steering direction of the car (e.g., LEFT, RIGHT).
 */
static void send_car_instruction(Car_Direction direction, Car_Steering steering) {
    Car_Instruction instruction = {.direction = direction, .steering = steering};

    if (osOK != osMessageQueuePut(CarInstructionQueueHandle, &instruction, 0U, 0U)) {
        printf("Failed to send car instruction.\n\r");
    }
}

/**
 * @brief Calculate the required depth of a parking spot.
 * @param wall_distance Distance to the wall in mm.
 * @return Required parking spot depth in mm.
 */
static uint32_t calculate_spot_depth(int32_t wall_distance) {
    uint32_t spot_depth = MIN_PARKING_SPOT_DEPTH_MM;

    if (wall_distance != SENSOR_INVALID_DATA) {
        spot_depth = (uint32_t)wall_distance + MIN_PARKING_SPOT_DEPTH_MM;
    }

    return spot_depth;
}

/**
 * @brief Detect a parking spot with a minimum width of 350 mm.
 * @param side_sensor_data Pointer to the side sensor data.
 * @param required_depth Required depth of the parking spot in mm.
 * @param valid_columns Pointer to the variable storing the number of valid columns.
 * @param is_right_sensor true if the sensor is on the right side, false if on the left.
 * @return true if a parking spot is detected, false otherwise.
 */
static bool detect_parking_spot(const Sensor_Data* side_sensor_data, uint32_t required_depth,
                                uint8_t* valid_columns, bool is_right_sensor) {
    uint8_t row = 0U, col = 0U, i = 0U;
    bool column_valid = true;
    int32_t distance = 0;

    if (is_right_sensor) {
        /* Right sensor: process columns from right to left */
        for (i = 0; i < side_sensor_data->cols; i++) {
            col = side_sensor_data->cols - 1 - i;
            column_valid = true;
            // ignore very bottom row because it contains noise
            for (row = 0; row < side_sensor_data->rows - 1; row++) {
                distance = side_sensor_data->distances[row][col];
                if ((distance != SENSOR_INVALID_DATA) && (distance < (int32_t)required_depth)) {
                    column_valid = false;
                    break;
                }
            }
            if (column_valid) {
                (*valid_columns)++;
                if (*valid_columns >= MIN_CONSECUTIVE_COLUMNS) {
                    return true;
                }
            } else {
                *valid_columns = 0;
            }
        }
    } else {
        /* Left sensor: process columns from left to right */
        for (col = 0; col < side_sensor_data->cols; col++) {
            column_valid = true;
            // ignore very bottom row because it contains noise
            for (row = 0; row < side_sensor_data->rows - 1; row++) {
                distance = side_sensor_data->distances[row][col];
                if ((distance != SENSOR_INVALID_DATA) && (distance < (int32_t)required_depth)) {
                    column_valid = false;
                    break;
                }
            }
            if (column_valid) {
                (*valid_columns)++;
                if (*valid_columns >= MIN_CONSECUTIVE_COLUMNS) {
                    return true;
                }
            } else {
                *valid_columns = 0;
            }
        }
    }

    return false;
}

/**
 * @brief Calculate adjusted delay based on measured distance.
 * @param base_delay_ms Base delay for 100mm distance.
 * @param distance_mm Current measured distance in mm.
 * @return Adjusted delay in milliseconds.
 */
static uint32_t get_adjusted_delay(uint32_t base_delay_ms, int32_t distance) {
    if (distance <= 0) {
        return base_delay_ms;
    }
    return (base_delay_ms * distance) / BASE_DISTANCE_MM;
}

/**
 * @brief Predicts sensor data based on the car's speed, direction, and delay.
 * @param sensor_data  Pointer to the array of sensor data structures.
 * @param speed            Car speed in mm/s.
 * @param direction        Driving direction (CAR_FORWARD or CAR_BACKWARD).
 * @param delay            Delay time in milliseconds.
 */
static void predict_data(Sensor_Data* sensor_data, uint8_t speed, Car_Direction direction,
                         uint32_t delay) {
    if (!sensor_data || speed == 0 || delay == 0) {
        return;
    }

    uint32_t adjustment = (speed * delay) / 1000U;

    if (direction == CAR_FORWARD) {
        if (sensor_data[SENSOR_L3_FRONT].distances[0U][0U] != SENSOR_INVALID_DATA) {
            sensor_data[SENSOR_L3_FRONT].distances[0U][0U] =
                    (sensor_data[SENSOR_L3_FRONT].distances[0U][0U] > adjustment)
                            ? sensor_data[SENSOR_L3_FRONT].distances[0U][0U] - adjustment
                            : 0;  // Prevent negative values
        }
        if (sensor_data[SENSOR_L3_REAR].distances[0U][0U] != SENSOR_INVALID_DATA) {
            sensor_data[SENSOR_L3_REAR].distances[0U][0U] += adjustment;
        }
    } else if (direction == CAR_BACKWARD) {
        if (sensor_data[SENSOR_L3_FRONT].distances[0U][0U] != SENSOR_INVALID_DATA) {
            sensor_data[SENSOR_L3_FRONT].distances[0U][0U] += adjustment;
        }
        if (sensor_data[SENSOR_L3_REAR].distances[0U][0U] != SENSOR_INVALID_DATA) {
            sensor_data[SENSOR_L3_REAR].distances[0U][0U] =
                    (sensor_data[SENSOR_L3_REAR].distances[0U][0U] > adjustment)
                            ? sensor_data[SENSOR_L3_REAR].distances[0U][0U] - adjustment
                            : 0;  // Prevent negative values
        }
    }
}
