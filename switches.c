#include "project1.h"

#define LED2 0x01
#define LED1 0x02
#define NONE 0x00
#define SW1  0x01
#define SW2  0x02

int main(void){
    volatile unsigned short delay = 0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;   // Enable PortN GPIO
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8;    // Enable PortJ GPIO
    delay++;            // Delay 2 more cycles before access Timer registers
    delay++;            // Refer to Page. 756 of Datasheet for info
    
    GPIO_PORTN_DIR_R = (LED2 | LED1);           // SET PN0 and PN1 to output
    GPIO_PORTJ_DIR_R = NONE;                    // SET PJ0 and PJ1 to input
    GPIO_PORTJ_PUR_R = (SW1 | SW2);      // Enable PJ0 and PJ1 Pullup Resistor
    GPIO_PORTN_DEN_R = (LED2 | LED1);    // Set PN0 and PN1 to digital port
    GPIO_PORTJ_DEN_R = (SW1 | SW2);      // Set PJ0 and PJ1 to digital port
    
    while(1) {
      GPIO_PORTN_DATA_R = ~((GPIO_PORTJ_DATA_R << 1 & 0x02) | (GPIO_PORTJ_DATA_R >> 1));
    }
    
    return 0;
}