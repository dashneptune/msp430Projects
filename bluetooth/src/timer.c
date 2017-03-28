#include "timer.h"





uint16_t motor_mask[4] = {0x09,0x06,0x00,0x5};


#define MOTOR_MOVE_FORWARD  0
#define MOTOR_MOVE_BACKWARD 1
#define MOTOR_COAST         2
#define MOTOR_BRAKE         3


void timer_init (struct timer_struct *timer, uint16_t period, uint16_t ontime, int16_t direction,volatile unsigned char * port, uint16_t pinshift){
  timer->period = period;
  timer->ontime = ontime;
  timer->direction = direction;
  timer->port = port;
  timer->pinshift = pinshift;
  timer->enable = 0;
  timer->ctr = 0;
  timer->ontime = ontime;
  timer->cachedontime = 0;
  timer->ontimehaschanged = 0;
  timer->cacheddirection = 0;
  timer->directionhaschanged = 0;
}

void timer_set_duty (struct timer_struct *timer, uint16_t ontime){
  timer->cachedontime = ontime;
  timer->ontimehaschanged = 1; 
}

void timer_set_direction (struct timer_struct *timer, int16_t direction)
{
  timer->cacheddirection = direction;
  timer->directionhaschanged = 1;
}


void timer_eval (struct timer_struct *timer){
  uint16_t mask = *(timer->port);
  uint16_t temp;
  if (timer->enable){
    if (timer->ctr == timer->ontime){
      mask &= ~(0x0F << timer->pinshift);
      if (timer->direction > 0){
        temp = MOTOR_MOVE_FORWARD;
      } else {
        temp = MOTOR_MOVE_BACKWARD;
      } 
      mask |= (motor_mask[temp] << timer->pinshift);
      *timer->port = mask;
    }
    if (timer->ctr == 0){
      timer->ctr = timer->period;
      mask  &= ~(0x0F << timer->pinshift);
      mask |= (motor_mask[MOTOR_COAST] << timer->pinshift);
      *timer->port = mask;
      if (timer->ontimehaschanged){
        timer->ontime = timer->cachedontime;
        timer->ontimehaschanged = 0;
      }
      if (timer->directionhaschanged){
        timer->direction = timer->cacheddirection;
        timer->directionhaschanged = 0;
      }
    } else {
      timer->ctr--;
    }
  }
}

