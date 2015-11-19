#include <stdio.h>
#define EVER ;;
int main (void)
{
	int i, a;
	printf("Prog5: iobound \n");
	for(EVER)
	{
		sleep(2);
		for(i = 0; i < 16384; i++) a = 999;
	}
	return 0;
}
