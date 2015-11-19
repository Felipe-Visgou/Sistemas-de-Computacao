/* Exercício 2) Mensagem do Dia! */
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main (void){
	int segmento1, id, pid, status;
	char msg[8], *p; 
	int i;

	segmento1 = shmget(8757, sizeof(char) * 8, IPC_CREAT | IPC_EXCL| S_IRUSR | S_IWUSR);

	p = (char *) shmat(segmento1, 0, 0);
	
	printf("Digite a mensagem do dia\n");

	scanf("%[^\n]", &msg);

	for(i = 0; i< 8; i++){
		p[i] = msg[i];
	}

	printf("%s", p);

	return 0;
}
/* Conclusão : Quando o programa "exec_recebe" possui a mesma chave de identificação da memória
				compartilhada ele tem a possibilidade de ler o seu conteúdo ou até mesmo altera-lo
				*/
				
