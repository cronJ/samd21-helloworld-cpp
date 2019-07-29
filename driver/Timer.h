#ifndef TIMER_H_
#define TIMER_H_

#include <samd21.h>

typedef enum{
	OVF = 1 << 0,
	ERR = 1 << 1,
	MC0 = 1 << 4,
	MC1 = 1 << 5
}timer_interrupt_t;

typedef enum{
	None = 0,
	Div2 = 1,
	Div4 = 2,
	Div8 = 3,
	Div16 = 4,
	Div64 = 5,
	Div256 = 6,
	Div1024 = 7
}timer_prescaler_t;

extern void timer_init(TcCount8 *tc, timer_prescaler_t prescaler, uint8_t periode);
extern void timer_enable(TcCount8 *tc);
extern void timer_disable(TcCount8 *tc);
extern void timer_start(TcCount8 *tc);
extern void timer_stop(TcCount8 *tc);
extern void timer_setPeriode(TcCount8 *tc, uint8_t newVal);
extern void timer_setCount(TcCount8 *tc, uint8_t newVal);
extern void timer_setOneshot(TcCount8 *tc);
extern void timer_setRepeating(TcCount8 *tc);
extern void timer_enableInterrupts(TcCount8 *tc, IRQn_Type irqn, uint8_t prio, timer_interrupt_t type);
extern void timer_interruptTriggeredBy(TcCount8 *tc, timer_interrupt_t type);


#endif