#include "park_assist_task.h"

void ParkAssistTask(void) {
    uint8_t i, row, col;

    for (;;) {
        /* Lock mutex to access shared sensors_data */
        if (osOK == osMutexAcquire(SensorsDataMutexHandle, osWaitForever)) {
            /* TODO: Process sensor data */
            osMutexRelease(SensorsDataMutexHandle);
        } else {
            printf("ParkAssistTask failed to acquire mutex.\n\r");
        }

        /* Delay between checks */
        vTaskDelay(pdMS_TO_TICKS(SENSOR_SCAN_DELAY_MS));
    }
}
