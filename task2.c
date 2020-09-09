#include "trafficlight.c"
int main(void) {
  LED_init();
  while (1) {
    LED_on();
    pause();
    LED_off();
    pause();
  }
}