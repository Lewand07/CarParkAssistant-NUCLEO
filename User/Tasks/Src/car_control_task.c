#include "car_control_task.h"

Car_Status CarControlTask(void) {
    Car_Instruction instruction;

    for (;;) {
        if (CAR_OK != Car_HandleInstruction(&car, instruction)) {
            Error_Handler();
        }
    }
}
