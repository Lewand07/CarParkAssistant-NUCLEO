#include "sensors_task.h"

void SensorsTask(void) {
    uint8_t i, row, col;

    for (;;) {
        /* Scan each sensor */
        for (i = 0; i < SENSORS_NUMBER; ++i) {
            if (SENSOR_OK == Sensor_ReadData(&sensors[i], &sensors_data[i])) {
                /* Lock mutex before printing or processing data */
                if (osMutexAcquire(SensorsDataMutexHandle, osWaitForever) == osOK) {
                    printf("Sensor[%d] Data:\n\r", i);
                    for (row = 0; row < sensors_data[i].rows; row++) {
                        for (col = 0; col < sensors_data[i].cols; col++) {
                            printf("%5d ", sensors_data[i].distances[row][col]);
                        }
                        printf("\n\r");
                    }
                    osMutexRelease(SensorsDataMutexHandle);  // Unlock mutex
                } else {
                    printf("Failed to acquire mutex for Sensor[%d].\n\r", i);
                }
            } else {
                printf("Failed to read data from sensor %d.\n\r", i);
            }
        }

        /* Delay to maintain 10Hz frequency */
        vTaskDelay(pdMS_TO_TICKS(SENSOR_SCAN_DELAY_MS));
    }
}
