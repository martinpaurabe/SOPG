//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux
//se compila por linea de comando con $ gcc -Wall -pedantic ./src/writer.c -o ./build/writer
//se ejecuta con $ .\a.out
//para ver los procesos en otro terminal correr 
//& watch -n 1 "ps -elf | grep a.out"
//la "S" se ve en general porque gran parte del tiempo esta en sleep()
//cuando lo paramos se pone con una "T"
//-----------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigcuser_handler(int sig) {
    pid_t pidchild;
    int wstatus;
 	pidchild = wait(&wstatus);
    printf(" PARENT: I'm on handler %d\n", wstatus);
    return;
}


//Execute on Terminal ./writer

#define FIFO_NAME "myfifo"
#define STDIN_FD            0
#define STDOUT_FD           1

int main(void)
{
    printf("PROCESO WRITER PID = %d\n", getpid());
    mkfifo(FIFO_NAME, 0666);
    int fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader--type some stuff\n");

    pid_t pid;
	struct sigaction sa;
	sa.sa_handler = sigcuser_handler;
	sa.sa_flags = 0; //SA_RESTART;
	sigemptyset(&sa.sa_mask);

    char s[300];
    int num;
    while (1) {
        gets(s);
        if ((num = write(fd, s, strlen(s))) == -1)
            perror("write");
        else
            printf("writer: wrote %d bytes\n", num);
    }
}
