#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

/* definição do arquivo procurado */
const char *arq = "teste.x";

/* declaração do SIGUSR1 */
void sigusr1();

int main(void){
	pid_t pid;
	
	/* utilizando fork para ter o arquivo filho */
	if ((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}

	
	/* filho: loop gerado com signal para buscar o arquivo */
	if (pid == 0){
		signal(SIGUSR1, sigusr1);
		for(;;);
	} /* pai: condição do arquivo existente ou inexistente */
	else{
		while(1){
			if(access(arq,F_OK) == 0){
				printf("O arquivo existe!\n");
				kill(0,SIGUSR1);
			} else{
				printf("O arquivo não existe!\n");
			}
		}
	}
	
}

/* Alerta de OK para o arquivo existente */
void sigusr1(){
	signal(SIGUSR1, sigusr1);
	printf("OK\n");
}
