#ifndef __TIMER_H_
#define __TIMER_H_

#include <stdint.h>

struct timer_struct {
  uint16_t ontime;
  uint16_t period;
  int16_t direction;
  volatile unsigned char *port;
  uint16_t pinshift;
  uint16_t enable;
  uint16_t ctr;
  uint16_t cachedontime;
  uint16_t ontimehaschanged;
  uint16_t cacheddirection;
  uint16_t directionhaschanged;
};

void timer_set_duty (struct timer_struct *timer, uint16_t ontime);
void timer_init (struct timer_struct *timer, uint16_t period, uint16_t ontime, int16_t direction, volatile unsigned char *port, uint16_t pinshift);
void timer_set_direction (struct timer_struct *timer, int16_t direction);
void timer_eval (struct timer_struct *timer);

#endif
