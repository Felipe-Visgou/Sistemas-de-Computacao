/* Exercício 3) Busca em Paralelo */
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (void){
	int segmento1, seg2, id;
	int i, limitesup, limiteinf;
	int *v, *key;

	segmento1 = shmget(IPC_PRIVATE, sizeof(int)*30, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	seg2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	v = (int *) shmat(segmento1, 0, 0);
	key = (int *)shmat(seg2, 0, 0);
	printf("Digite a chave procurada \n");
	scanf("%d", key);
	
	v[0] = 43;	v[10] = 74;	v[20] = 4567;
	v[1] = 3;	v[11] = 39;	v[21] = 2345;
	v[2] = 672;	v[12] = 67;	v[22] = 345;
	v[3] = 72;	v[13] = 2;	v[23] = 346;
	v[4] = 23;	v[14] = 88;	v[24] = 7342;
	v[5] = 26;	v[15] = 6;	v[25] = 235;
	v[6] = 82;	v[16] = 872; v[26] = 526;
	v[7] = 4;	v[17] = 42;	v[27] = 7623;
	v[8] = 33;	v[18] = 90;	v[28] = 842;
	v[9] = 999;	v[19] = 999; v[29] = 999;
	
	
	
	if(id = fork() > 0)
	{
		limitesup = 10;
		limiteinf = 0;
		for(i = limiteinf; i < limitesup; i++)
		{
			if(v[i] == *key)
			{
				printf("Chave encontrada na posicao %d do vetor \n", i);
				exit(1);
			}
		}
	printf("Chave nao encontrada \n");
	}
	else if(id == 0)
		 {
			 if(id = fork() > 0)
			 {
				 limiteinf = 10;
				 limitesup = 20;
				 for(i = limiteinf; i < limitesup; i++)
				 {
					 if(v[i] == *key)
					 {
						 printf("Chave encontrada na posicao %d do vetor \n", i);
						 exit(1);
					 }
				 }
			 printf("Chave nao encontrada \n");
			 }
			 else if(id == 0)
				  {
					  limiteinf = 20;
					  limitesup = 30;
					  for(i = limiteinf; i < limitesup; i++)
				 		{
					 		if(v[i] == *key)
					 		{
						 		printf("Chave encontrada na posicao %d do vetor \n", i);
						 		exit(1);
					 		}
				 		}
				  printf("Chave nao encontrada \n");
				  }

		 }
		 else {
			printf("Erro na criacao do processo \n");
			exit(-2);
		 }
	shmdt(v);
	shmdt(key);
	shmctl(segmento1, IPC_RMID, 0);
	shmctl(seg2, IPC_RMID, 0);
	
	return 0;
}

/* Conclusao :
	Cada processo pesquisa a chave no vetor da memoria compartilhada,
	se a chave eh encontrada em mais de uma ocorrencia do vetor e em 	
	areas de pesquisa de processos diferetes, serah mostrado na tela
	duas mensagens de que a chave foi achada e em posicoes diferentes.
	O mesmo se aplica quando a chave nao se encontra no vetor,
	tres mensagens de que a chave nao foi encotrada serah exibida.
*/
	








	


