/*
    Useful things to know
    Base Addresses:
      * GPIO A          0x4005.8000
      * GPIO B          0x4005.9000
      * GPIO C          0x4005.A000
      * GPIO D                 B
                               C
                               D
                               E
                               F
        GPIO J            4006.0
                            

    Offsets:
      * GPIODATA        0x000
      * GPIODIR         0x400
      * GPIOAFSEL       0x420
      * GPIOAMSEL       0x528
      * GPIOPUR         0x510
      * GPIOPDR         0x514
      * GPIOLOCK        0x520

*/

#include <stdint.h>

#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

#define SYSCTL_RCGPIO_R2        0x00000004  // GPIO Port C Run Mode Clock
                                            // Gating Control
#define GPIO_PORTC_DATA_R       (*((volatile uint32_t *)0x4005A3FC))
#define GPIO_PORTC_DIR_R        (*((volatile uint32_t *)0x4005A400))
#define GPIO_PORTC_AFSEL_R      (*((volatile uint32_t *)0x4005A420))
#define GPIO_PORTC_DEN_R        (*((volatile uint32_t *)0x4005A51C))
#define GPIO_PORTC_AMSEL_R      (*((volatile uint32_t *)0x4005A528))

#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
                                            // Gating Control
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x4005D3FC))
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x4005D400))
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4005D51C))

#define SYSCTL_RCGCGPIO_R8      0x00000100  // GPIO Port J Run Mode Clock
                                            // Gating Control
#define GPIO_PORTJ_DATA_R       (*((volatile uint32_t *)0x400603FC))
#define GPIO_PORTJ_DIR_R        (*((volatile uint32_t *)0x40060400))
#define GPIO_PORTJ_PUR_R        (*((volatile uint32_t *)0x40060510))
#define GPIO_PORTJ_DEN_R        (*((volatile uint32_t *)0x4006051C))

#define SYSCTL_RCGCGPIO_R10     0x00000400  // GPIO Port L Run Mode Clock
                                            // Gating Control
#define GPIO_PORTL_DATA_R       (*((volatile uint32_t *)0x400623FC))
#define GPIO_PORTL_DIR_R        (*((volatile uint32_t *)0x40062400))
#define GPIO_PORTL_DEN_R        (*((volatile uint32_t *)0x4006251C))
#define GPIO_PORTL_AFSEL_R      (*((volatile uint32_t *)0x40062420))
#define GPIO_PORTL_AMSEL_R      (*((volatile uint32_t *)0x40062528))

#define SYSCTL_RCGCGPIO_R12     0x00001000  // GPIO Port N Run Mode Clock
                                            // Gating Control
#define GPIO_PORTN_DATA_R       (*((volatile uint32_t *)0x400643FC))
#define GPIO_PORTN_DIR_R        (*((volatile uint32_t *)0x40064400))
#define GPIO_PORTN_DEN_R        (*((volatile uint32_t *)0x4006451C))
#define GPIO_PORTN_AFSEL_R      (*((volatile uint32_t *)0x40064420))
#define GPIO_PORTN_AMSEL_R      (*((volatile uint32_t *)0x40064528))



