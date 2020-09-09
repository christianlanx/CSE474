#include "project1.h"

#define SWITCH_PED      0x01
#define SWITCH_SS       0x02
#define SWITCH_ALL      0x03

#define LED_RED         0x04
#define LED_YEL         0x08
#define LED_GRN         0x10
#define LED_ALL         0x1C

void intial_init(void)
{
  volatile unsigned short delay = 0;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10; // Enable Port L Gating Clock
  delay++;
  delay++;
}

void LED_init(void)
{
  GPIO_PORTL_AMSEL_R &= ~LED_ALL;          // disable analog function of PL[2-4]
  GPIO_PORTL_DIR_R |= LED_ALL;             // Set PL[2-4] to output
  GPIO_PORTL_AFSEL_R &= ~LED_ALL;          // Regular port function
  GPIO_PORTL_DEN_R |= LED_ALL;             // enable digital output on PL[2-4]
}

void exter_switch_init(void)
{
  GPIO_PORTL_AMSEL_R &= ~SWITCH_ALL;           // Disable PL[0-1] analog function
  GPIO_PORTL_AFSEL_R &= ~SWITCH_ALL;           // Select PL[0-1] regular port function
  GPIO_PORTL_DIR_R &= ~SWITCH_ALL;             // Set PL[0-1] to input direction
  GPIO_PORTL_DEN_R |= SWITCH_ALL;              // Enable PL[0-1] digital function
}

// turn on the specified LED connected to Port L
void LED_on(unsigned char led) 
{
  GPIO_PORTL_DATA_R |= led;
}  

// turn off the specified LED, connected to Port L
void LED_off(unsigned char led)
{
  GPIO_PORTL_DATA_R &= ~led;
}

// returns a true value if the specified switch is being pressed
// actually returns the bit value associated with that port
unsigned long switch_input(unsigned char sw)
{
  return (GPIO_PORTL_DATA_R & sw);     // sw (pressed) or 0 (not pressed)
}

// pause for a few seconds...
void pause() {
  for (int j = 0; j < 3000000; j++) {}
}

enum LA_States { LA_SMStart, LA_Off, LA_Go, LA_Warn, LA_Stop } LA_State;

void StopLight_Latch()
{
  switch(LA_State) {    // Transitions
    case LA_SMStart:      // Initial Transition
      LA_State = LA_Off;
      break;
      
    case LA_Off:
      if (switch_input(SWITCH_SS)) {
        LA_State = LA_Go;
      }
      break;
      
    case LA_Go:
      if (switch_input(SWITCH_SS)) {
        LA_State = LA_Off;
      }
      else if (switch_input(SWITCH_PED)) {
        LA_State = LA_Warn;
      }
      else {
        LA_State = LA_Stop;
      }
      break;
      
    case LA_Warn:
      if (switch_input(SWITCH_SS)) {
        LA_State = LA_Off;
      }
      else {
        LA_State = LA_Stop;
      }
      break;
      
    case LA_Stop:
      if (switch_input(SWITCH_SS)) {
        LA_State = LA_Off;
      }
      else {
        LA_State = LA_Go;
      }
      break;
    
    default:
      LA_State = LA_SMStart;
      break;
  } // Transitions
  
  switch(LA_State) {    // State actions
    case LA_Off:
      LED_off(LED_ALL);
      pause();
      break;
    
    case LA_Go:
      LED_off(LED_ALL);
      LED_on(LED_GRN);
      pause();
      break;
      
    case LA_Warn:
      LED_off(LED_ALL);
      LED_on(LED_YEL);
      pause();
      break;
      
    case LA_Stop:
      LED_off(LED_ALL);
      LED_on(LED_RED);
      pause();
      break;
      
    default:
      break;
  }     // State Actions
}    

int main(void) {
  intial_init();
  LED_init();
  exter_switch_init();
  
  LA_State = LA_SMStart;
  
  while (1) {
    StopLight_Latch();
  }
  
  return 0;
}