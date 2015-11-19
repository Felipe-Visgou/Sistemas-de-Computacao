/* Exercício 1 - LAB 4

Dupla: Fernando Homem da Costa
		Felipe Vieira Côrtes
*/

/* 1) Elabore um programa que seja capaz de
mandar executar dois outros programas
conhecidos (da Shell, por exemplo:ls,grep,cat, ou outros). 
Execute o programa e relate oque aconteceu.
*/

#include<stdio.h>
#include<stdlib.h>

int main (void){
int pid;

	if((pid = fork() < 0)){
		printf("Ocorreu um erro durante o fork!\n");
		
	}

	else if(pid == 0){
	
	printf("Filho!\n");
	
	char *const arg2[]={"ls","-l","-a",NULL};
	execve("/bin/ls", arg2, NULL);

	char *const arg[]={"/bin/echo","Execve: Programa 2",NULL};
	execve("/bin/echo",arg,0);

	}

	else{
		printf("Pai!\n");	
	}

	exit(1);
}

/*Resultado Terminal:

drwxrwxr-x 2 fernando fernando 4096 Sep 12 12:41 .
drwxr-xr-x 3 fernando fernando 4096 Sep 12 11:20 ..
-rwxrwxr-x 1 fernando fernando 8712 Sep 12 12:41 Lab1
-rw-rw-r-- 1 fernando fernando  402 Sep 12 12:41 LabExec1.c
-rw-rw-r-- 1 fernando fernando  402 Sep 12 12:41 LabExec1.c~

conclusão: Podemos observar que o primeiro comando Execve é executado normalmente, fazendo uma busca no diretorio "ls" e informando na tela o que foi encontrado. Entretanto, após o primeiro Execve ter sido executado, o segundo não consegue ser executado, assim não consigo informar na tela a mensagem devida.
*/

