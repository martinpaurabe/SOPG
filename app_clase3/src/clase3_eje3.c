//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux
//se compila por linea de comando con $ gcc ./src/clase2_eje1.c 
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



#define PARENT_SLEEP_TIME   20
#define CHILD_SLEEP_TIME    5
#define STDIN_FD            0
#define STDOUT_FD           1

int main(void) {

    pid_t pid;
    pid_t pfds[2];
    pipe(pfds);

    switch (pid = fork()) {
        case -1:
            perror("fork"); /* something went wrong */
            exit(1);

        /* parent exits */
        case 0:
            write(STDOUT_FD,"CHILD: This is the child process\n",33);
            close(pfds[0]);              // cerramos read
            sleep(CHILD_SLEEP_TIME);
            write(pfds[1],"CHILD: first msg\n",17);
            sleep(CHILD_SLEEP_TIME*2);
            printf(" CHILD: I'm outta here!\n");
            exit(0);

        default:
            write(STDOUT_FD,"PARENT: This is the parent process!\n",36);
            close(pfds[1]);          // cerramos el FD para write
            char s[200];
            if (read(pfds[0],s, sizeof s) < 0)
                perror("fgets");
            else
                printf("ingresaste: %s\n", s);
           printf(" PARENT: I'm outta here!\n");
           exit(0);
     }
    return 0;
}