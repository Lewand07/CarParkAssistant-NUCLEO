#include "park_assist_task.h"
#include <stdbool.h>
#include <stdio.h>

/* Private Function Declarations */
static void send_car_instruction(Car_Direction direction, Car_Steering steering);
static bool check_front_obstacle(const Sensor_Data* front_sensor_data);
static uint32_t calculate_spot_depth(int32_t wall_distance);
static bool detect_parking_spot(const Sensor_Data* side_sensor_data, uint32_t required_depth,
                                uint8_t* valid_columns, bool is_right_sensor);

void ParkAssistTask(void) {
    static uint8_t valid_columns_left = 0U;
    static uint8_t valid_columns_right = 0U;
    uint32_t left_spot_depth = MIN_PARKING_SPOT_DEPTH_MM;
    uint32_t right_spot_depth = MIN_PARKING_SPOT_DEPTH_MM;
    bool left_spot_detected = false;
    bool right_spot_detected = false;

    for (;;) {
        /* Lock mutex to access shared sensors_data */
        if (osOK == osMutexAcquire(SensorsDataMutexHandle, osWaitForever)) {
            /* Check for front obstacles */
            if (check_front_obstacle(&sensors_data[SENSOR_L3_FRONT]) || left_spot_detected ||
                right_spot_detected) {
                send_car_instruction(CAR_STOP, CAR_CENTER);
                osMutexRelease(SensorsDataMutexHandle);
                continue;
            }
            send_car_instruction(CAR_FORWARD, CAR_CENTER);

            /* Detect parking spot */
            left_spot_detected = detect_parking_spot(&sensors_data[SENSOR_L5_LEFT], left_spot_depth,
                                                     &valid_columns_left, false);
            right_spot_detected = detect_parking_spot(&sensors_data[SENSOR_L5_RIGHT],
                                                      right_spot_depth, &valid_columns_right, true);

            // recalculating spot depth if no spot detected
            if (!left_spot_detected && valid_columns_left == 0) {
                left_spot_depth =
                        calculate_spot_depth(sensors_data[SENSOR_L3_LEFT].distances[0][0]);
            }
            if (!right_spot_detected && valid_columns_right == 0) {
                right_spot_depth =
                        calculate_spot_depth(sensors_data[SENSOR_L3_RIGHT].distances[0][0]);
            }
            osMutexRelease(SensorsDataMutexHandle);
        } else {
            printf("ParkAssistTask failed to acquire mutex.\n\r");
        }

        /* Delay between checks */
        vTaskDelay(pdMS_TO_TICKS(SENSOR_SCAN_DELAY_MS));
    }
}

/**
 * @brief Check for obstacles in front of the car.
 * @param front_sensor_data Pointer to the front sensor data.
 * @return true if an obstacle is detected, false otherwise.
 */
static bool check_front_obstacle(const Sensor_Data* front_sensor_data) {
    bool obstacle_detected = false;

    for (uint8_t row = 0U; row < front_sensor_data->rows; row++) {
        for (uint8_t col = 0U; col < front_sensor_data->cols; col++) {
            if ((front_sensor_data->distances[row][col] != SENSOR_INVALID_DATA) &&
                (front_sensor_data->distances[row][col] < MIN_OBSTACLE_DISTANCE_MM)) {
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
