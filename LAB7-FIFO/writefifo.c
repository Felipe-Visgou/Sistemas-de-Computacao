/* INF1019 Sistemas de Computação
    Laboratório 7 - FIFO
    Alunos: Felipe Vieira Cortes - 1321881
            Daniel Siles - 1311291
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define OPENMODE (O_WRONLY | O_NONBLOCK)
#define FIFO "minhaFifo"
int main (void)
{
	int fpFIFO;
	char mensagem[] = "Melancia sem carco";
	char w;
	if(access(FIFO, F_OK) == -1)
	{
		if(mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0)
		{
			fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
			return -1;
		}
	}
	puts ("Abrindo FIFO");
	if((fpFIFO = open (FIFO, OPENMODE)) < 0)
	{
		fprintf (stderr, "Erro ao abrir a FIFO %s\n", FIFO);
		return -2;
	}
	puts ("Começando a escrever...");
	while(1)
	{
		scanf("%c", &w);
		write(fpFIFO, &w, 1);
	}
	puts ("Fim da escrita");
	close (fpFIFO);
	return 0;
}
/* Observação
    Fazendo o procedimento de abertura da fifo, usamos como openmode as flags
    O_WRONLY | O_NONBLOCK. Desse jeito, a fifo fica em um loop infinito lendo do teclado
	e escrevendo na fifo.
	Depois que a readfifo já está aberta, quando se executa em outro terminal a writefifo
	esta é aberta com sucesso e pode-se começar a escrever, letra por letra a mensagem escrita
	em um terminal é lida e impressa pelo outro.

  -Saida no Terminal 
[pirai.grad.inf.puc-rio.br:~/inf1019/LAB7] ./writefifo
Abrindo FIFO
Começando a escrever...
 
o
l
a

m
u
n
d
o

*/

