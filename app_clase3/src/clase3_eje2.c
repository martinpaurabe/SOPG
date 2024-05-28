//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux
//se compila por linea de comando con $ gcc -Wall -pedantic ./src/clase3_eje2.c -o ./build/clase3_eje2 
//se ejecuta con $ .\a.out
//para ver los procesos en otro terminal correr 
//& watch -n 1 "ps -elf | grep a.out"
//la "S" se ve en general porque gran parte del tiempo esta en sleep()
//cuando lo paramos se pone con una "T"
//-----------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



#define PARENT_SLEEP_TIME 20
#define CHILD_SLEEP_TIME 5


void sigchld_handler(int sig) {
    pid_t pidchild;
    int wstatus;
 	pidchild = wait(&wstatus);
    printf(" PARENT: I'm on handler %d\n", wstatus);
    return;
}

int main(void) {

    pid_t pid;
	struct sigaction sa;
	sa.sa_handler = sigchld_handler;
	sa.sa_flags = 0; //SA_RESTART;
	sigemptyset(&sa.sa_mask);

    switch (pid = fork()) {
        case -1:
            perror("fork"); /* something went wrong */
            exit(1);

        /* parent exits */
        case 0:
            printf(" CHILD: This is the child process!\n");
            printf(" CHILD: My PID is %d\n", getpid());
            printf(" CHILD: My parent's PID is %d\n", getppid());
            sleep(CHILD_SLEEP_TIME);
            printf(" CHILD: I'm outta here!\n");
            exit(0);

        default:
            printf("PARENT: This is the parent process!\n");
            if (sigaction(SIGCHLD, &sa, NULL) == -1){
                perror("sigaction");
                exit(1);
            }
            printf("PARENT: My PID is %d\n", getpid());
            printf("PARENT: My child's PID is %d\n", pid);
            sleep(PARENT_SLEEP_TIME);
            printf("PARENT: I'm outta here!\n");
            exit(0);
    }
    return 0;
}