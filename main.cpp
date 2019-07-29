#include <samd21.h>

#include "driver/Pin.h"
#include "driver/Serial.h"
#include "driver/System.h"
#include "driver/Timer.h"

Pin userled(Pin::Port::A, 27, Pin::Function::GPIO_Output | Pin::Function::Low);

void TCC0_Handler(){
	((TcCount8 *) TCC0)->INTFLAG.bit.OVF = 1; // clear interrupt
	userled.toggle();
}

void SysTick_Handler(){
	// doin' nothing in here
}

int main() {

	SystemCoreClockUpdate();
	SystemInit();

	serial.line_received_cb = [](char* line){
		serial.print(line);
	};

	// SysTick_Config(SystemCoreClock / 1000); // 1ms

	// enable peripheral clock for timer0
	gclk_enable_clock(TCC0_GCLK_ID, GCLK_CLKCTRL_ID_TCC0_TCC1_Val);

	TcCount8 *timer = (TcCount8*) TCC0;
	timer_init(timer, timer_prescaler_t::Div1024, 125); // 1s (from gclk1@48MHz/375)
	timer_enableInterrupts(timer, TCC0_IRQn, 2, timer_interrupt_t::OVF);
	timer_setRepeating(timer);
	timer_enable(timer); // enables and starts timer

	while(true){
	}

	return 0;
}