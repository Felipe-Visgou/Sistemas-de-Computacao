#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void){
	int segmento1, id, pid, status;
	char *p; 

	segmento1 = shmget(8757, sizeof(char) * 8, IPC_CREAT | S_IRUSR | S_IWUSR);

	p = (char *) shmat(segmento1, 0, 0);
	
	printf("%s", p);

	shmdt (p);
	// libera a memória compartilhada
	shmctl (segmento1, IPC_RMID, 0);
	
	return 0;
}
