#include <stdio.h>
#define EVER ;;
int main (void)
{
	int i;
	printf("prog6: cpubound \n");
	for(EVER)
		i = 3;
	return 0;
}
