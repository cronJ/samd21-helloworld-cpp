/*
 * LED	PA17
 * SW	PA19
 */

#include "samd21.h"

#define LED0	PORT_PA17
#define SW0		PORT_PA19

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	// Set LED0 to output
	REG_PORT_DIRSET0 = LED0;
	
	// Set INEN on PA19
	PORT->Group[0].PINCFG[19].reg = PORT_PINCFG_INEN;
		
    while (1) 
    {
		if ((REG_PORT_IN0 & SW0) != 0)
		{
			REG_PORT_OUTSET0 = LED0;
		} 
		else
		{
			REG_PORT_OUTCLR0 = LED0;
		}
    }
}