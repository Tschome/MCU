#include "led.h"

int main(void)
{
	int i = 0;//—≠ª∑±‰¡ø
	int n = 0;
	
	led_init();
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		led_on(i);
		for(n = 0; n < 10000000; n++);
		led_off(i);
		for(n = 0; n < 10000000; n++);
	}
}





