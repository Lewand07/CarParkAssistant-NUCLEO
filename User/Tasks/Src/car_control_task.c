#include "car_control_task.h"

void CarControlTask(void) {
    Car_Instruction instruction;

    for (;;) {
        if (osOK ==
            osMessageQueueGet(CarInstructionQueueHandle, &instruction, NULL, osWaitForever)) {
            if (CAR_OK != Car_HandleInstruction(&car, instruction)) {
                Error_Handler();
            }
        }
    }
}
