
//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux (el "$" lo coloca automáticamente el terminal)
//se compila por linea de comando con $ gcc ./src/clase2_eje1.c 
//se ejecuta con $ .\a.out
//para ver los procesos en otro terminal correr 
//& watch -n 1 "ps -elf | grep a.out"
//-----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PARENT_SLEEP_TIME 20
#define CHILD_SLEEP_TIME 40

void main(void)
{

    pid_t pid;
    int rv;

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
            printf("PARENT: My PID is %d\n", getpid());
            printf("PARENT: My child's PID is %d\n", pid);
            sleep(PARENT_SLEEP_TIME);
            printf("PARENT: I'm outta here!\n");
            exit(0);
    }
    return;
}