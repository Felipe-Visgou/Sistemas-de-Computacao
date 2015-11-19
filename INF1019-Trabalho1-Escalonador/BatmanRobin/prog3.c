#include <stdio.h>
#define EVER ;;
int main (void)
{
	int i, a;
	printf("Prog3: iobound \n");
	for(EVER)
	{
		sleep(2);
		for(i = 0; i < 16384; i++) a = 999;
	}
	return 0;
}
