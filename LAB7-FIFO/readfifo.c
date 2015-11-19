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
#define OPENMODE (O_RDONLY)
#define FIFO "minhaFifo"
int main (void)
{
	int
	fpFIFO;
	char ch;
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
	puts ("Começando a ler...");
	while(1)
	{
	    read (fpFIFO, &ch, sizeof(ch));
        putchar (ch);
    }
	puts ("Fim da leitura");
	close (fpFIFO);
	return 0;
}


/* Observação
    Fazendo o procedimento de abertura da fifo, usamos como openmoode somente a flag
    O_RDONLY. Dessa maneira, a fifo fica esperando alguem escrever nela, e, logo apos
    a escrita de algo no arquivo, ela vai ler e escrever na tela.
    Primeiramente deve-se executar o programa readfifo, antes do writefifo, assim o 
    programa imprimi "Abrindo FIFO" e aguarda o programa writefifo, depois que este é
    aberto a readfifo imprime "Começando a ler" e espera alguem escrever na fifo.

 -Saida no terminal

[pirai.grad.inf.puc-rio.br:~/inf1019/LAB7] ./readfifo
Abrindo FIFO
Começando a ler...
o
l
a

m
u
n
d
o
*/



