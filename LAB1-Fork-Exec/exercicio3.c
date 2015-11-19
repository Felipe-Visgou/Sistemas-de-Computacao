/* LABORATÓRIO INF1019
   Felipe Vieira Côrtes - 1321881	
   Daniel Siles - 1311291
*/
/* 3) Use o programa anterior para ler e ordenar um vetor de 10 posições. O filho 
ordena o vetor e o pai exibe os dados do vetor antes do fork() e depois do 
waitpid(). Eles usarão o mesmo vetor na memória? Justifique */
#include <stdio.h>
#include <stdlib.h>
static int v[10] = {5,3,6,8,4,3,2,7,3,2};
int main (void)
{
	int status;
	int p;
	int i;
if((p = fork())!=0)
{
	waitpid(-1, &status, 0);
	printf("PID PAI: %d \n PID FILHO : %d \n", getpid(), p);
	for( i = 0; i < 10; i++)
	{
		printf(" %d vetor - %d \n", i, v[i]);
	}	
}
else
{
	printf(" (else) PID FILHO: %d \n", getpid());
	bsort(v, 10);
	for( i = 0; i < 10; i++)
	{
		printf(" %d vetor - %d \n", i, v[i]);
	}
	exit(0);
}
exit(0);
}
void bsort(int list[], int n)
{
  int c, d, t;
 
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (list[d] > list[d+1])
      {
        /* Swapping */
 
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
  }
}
