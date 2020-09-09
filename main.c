#include "project1.h"

#define LED4 0x01
#define LED3 0x10
#define LED2 0x01
#define LED1 0x02
#define LEDNONE 0x0

void pause();

int main(void)
{
    volatile unsigned short delay = 0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;    // Enable PortF GPIO
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;   // Enable PortN GPIO
    delay++;            // Delay 2 more cycles before access Timer registers
    delay++;            // Refer to Page. 756 of Datasheet for info
    
    GPIO_PORTF_DIR_R = LED4;            // Set PF0 to output
    GPIO_PORTF_DIR_R |= LED3;           // Set PF4 to output
    
    GPIO_PORTN_DIR_R = LED2;            // Set PN0 to output
    GPIO_PORTN_DIR_R |= LED1;           // Set PN1 to output
    
    GPIO_PORTF_DEN_R = LED4;            // Set PF0 to digital port
    GPIO_PORTF_DEN_R |= LED3;           // Set PF4 to digital port
    
    GPIO_PORTN_DEN_R = LED2;            // Set PN0 to digital port
    GPIO_PORTN_DEN_R |= LED1;           // Set PN1 to digital port
    
    GPIO_PORTF_DATA_R = LED4;           // Set PF0 to 1
    GPIO_PORTF_DATA_R |= LED3;          // Set PF4 to 1
    
    GPIO_PORTN_DATA_R = LED2;           // Set PN0 and PN1 to 1
    GPIO_PORTN_DATA_R |= LED1;          // 

    
    while (1) {
      GPIO_PORTN_DATA_R = LEDNONE;
      GPIO_PORTF_DATA_R = LED4;
      pause();
      GPIO_PORTF_DATA_R = LED3;
      pause();
      GPIO_PORTF_DATA_R = LEDNONE;
      GPIO_PORTN_DATA_R = LED2;
      pause();
      GPIO_PORTN_DATA_R = LED1;
      pause();
    }
    
    return 0;
}

void pause() {
  for (int j = 0; j < 1000000; j++) {}
}