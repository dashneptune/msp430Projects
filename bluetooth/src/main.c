#include <msp430.h>
#include <stdint.h>
#include "pins.h"
#include "watchdog.h"
#include "usci.h"
#include "board.h"
#include "timer.h"


uint16_t time = 0;
//uint16_t time_ov = 0;
struct cap {
  uint16_t firsttime;
  uint16_t lasttime;
  uint16_t difftime;
};


#define TIMER_FLAG 0x01

volatile uint16_t isr_flag = 0;

void fill_redundant_array (uint8_t *array, uint8_t length, uint8_t value){
  uint16_t ctr;
  for (ctr = 0; ctr < length; ctr++){
    array[ctr] = value;
  }
}

struct cap left_motor_cap = {0,0,0};
struct cap right_motor_cap = {0,0,0};


int main (void){
  uint8_t rx_val;
  struct timer_struct left_wheel;
  struct timer_struct right_wheel;
  timer_init (&left_wheel, 0x3F, 0,1, &P2OUT,0);
  timer_init (&right_wheel, 0x3F, 0,1,&P2OUT,4);
  stop_watchdog ();
	device_init ();     // initialize the msp430 modules
  __enable_interrupt();
	IE2 |= UCA0RXIE;    // initialize the receive interrupt
	TA0CTL |= MC_1;
  while (1){
	  LPM0;             // we get out of this by the rx interrupt service routi
	  if (has_rx_value()){
      rx_val = get_rx_value ();
      if (rx_val & 0x80){
        if (rx_val & 0x40){
          timer_set_direction (&left_wheel, -1);
        }else {
          timer_set_direction (&left_wheel, 1);
        }
        timer_set_duty (&left_wheel,rx_val&0x3F); 
      } else {
        if (rx_val & 0x40){
          timer_set_direction (&right_wheel, -1); 
        }else {
          timer_set_direction (&right_wheel,1);
        }
        timer_set_duty (&right_wheel, rx_val & 0x3F);
      }
    }
    if (isr_flag & TIMER_FLAG){
      timer_eval (&left_wheel);
      timer_eval (&right_wheel);
      isr_flag &= ~TIMER_FLAG;
    }
	}
	return (1);
}

__attribute__ ((interrupt(TIMER1_A0_VECTOR)))
void isr_cc0_TA1 (void){
  if (time >=0xFFFF){
    time = 0;
  }else {
    time++;
  }
}



__attribute__((interrupt(TIMER0_A0_VECTOR)))
void isr_cc0_TA0 (void){
  P1OUT ^= LED;
  isr_flag |= TIMER_FLAG;
  LPM4_EXIT;
}

__attribute__ ((interrupt(PORT1_VECTOR)))
void p1_isr (void){
  if (P1IFG & LEFT_MOTOR_PIN){
    if (left_motor_cap.lasttime > time){
      left_motor_cap.difftime = 0xFFFF-left_motor_cap.lasttime;
      left_motor_cap.difftime += time;
    }else {
      left_motor_cap.difftime = time - left_motor_cap.lasttime;
    }
    left_motor_cap.lasttime = time;
    P1IFG &= ~LEFT_MOTOR_PIN;
  }
  if (P1IFG & RIGHT_MOTOR_PIN){    
    if (right_motor_cap.lasttime > time){
      right_motor_cap.difftime = 0xFFFF-right_motor_cap.lasttime;
      right_motor_cap.difftime += time;
    }else {
      right_motor_cap.difftime = time - right_motor_cap.lasttime;
    }
    right_motor_cap.lasttime = time; 
    P1IFG &= ~RIGHT_MOTOR_PIN;
  }
}


