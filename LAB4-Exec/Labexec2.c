/* Exercício 2 - LAB 4

Dupla: Fernando Homem da Costa
		Felipe Vieira Côrtes
*/

/* 2) Elabore um programa CPU bound que não
termine (loop de cálculos e mensagens eventuais
no vídeo).
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

int main (int argc, char* argv[]){
	int i, j;
	pid_t pid1,pid2;
	pid1 = fork();
	if(pid1 == 0)
		execve(argv[1], 0, 0);
	else
	{
		if(pid1 > 0)
		{
			pid2 = fork();
			if(pid2 == 0)
				execve(argv[2], 0, 0);
			else
			{
				if(pid2 > 0)
				{
                    printf("PID 1 : %d \n PID 2 : %d \n", pid1, pid2);
					while(1){
					kill(pid1, SIGSTOP);
					wait(3);
					kill(pid2, SIGSTOP);
					kill(pid1, SIGCONT);
					wait(3);
					kill(pid2, SIGCONT);
					}
				}
			}
		}
	}
	return 0;
}

/* No terminal 

ubuntu@ubuntu:~/Documents/LAB4$ ./Labexec2 ./io ./cpu
PID 1 : 7929 
 PID 2 : 7930 
Digite um numero inteiro:
546
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
Variable: -1714763.588860
^C

/* Conclusao 
 Para termos os pid dos dois programas que estao sendo executados, foram criados
dois filhos e seus respectivos pid's nas variaveis pid1 e pid2, assim o processo pai
pode controlar os dois programas, alternando a execucao de cada um, porem por algum 
motivo somente o programa do segundo 'execve' esta sendo executado (cpubound) e 
os comandos de SIGSTOP e SIGCONT mandados para o seu pid estao sendo ignorados.
 */

						 
