#include <stdint.h>
#include "excep.h"
#include "uart.h"

void halt() 
{
    while(1);
}


/*
    Note:
    Will need a serious overall for an actual
    exception handler.
*/
void excep_handler(uint64_t esr, uint64_t far) 
{

    int code = esr >> 26;

    switch (code) {
        case 0b100000:
        case 0b100001:
            UART("ERROR: Instruction Abort\n");
            break;
        case 0b100010:
            UART("ERROR: Program Counter Alignment Fault\n");
            break;
        case 0b100100:
        case 0b100101:
            UART("ERROR: Data Abort\n");
            break;
        case 0b100110:
            UART("ERROR: Stack Alignment Fault\n");
            break;
        case 0b101100:
            UART("ERROR: Floating Point Exception");
            break;
        case 0b000001:
            UART("ERROR: illegal use of the WFI/WFE instruction\n");
            break;
        case 0b001110:
            UART("ERROR: illegal execution state\n");
            break;
        default:
            UART("ERROR: Unknown\n");
            break;
    }

    halt();
}

