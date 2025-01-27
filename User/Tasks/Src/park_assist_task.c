#include "park_assist_task.h"
#include <stdbool.h>
#include <stdio.h>

/* Private Function Declarations */
static void send_car_instruction(Car_Direction direction, Car_Steering steering);
static bool check_front_obstacle(const Sensor_Data* front_sensor_data);

void ParkAssistTask(void) {
    uint8_t i, row, col;

    for (;;) {
        /* Lock mutex to access shared sensors_data */
        if (osOK == osMutexAcquire(SensorsDataMutexHandle, osWaitForever)) {
            /* Check for front obstacles */
            if (check_front_obstacle(&sensors_data[SENSOR_L3_FRONT])) {
                send_car_instruction(CAR_STOP, CAR_CENTER);
                return;
            }
            send_car_instruction(CAR_FORWARD, CAR_CENTER);
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
