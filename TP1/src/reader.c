//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux
//se compila por linea de comando con $ gcc -Wall -pedantic ./src/reader.c -o ./build/reader 
//Execute on Terminal ./build/reader
//para ver los procesos en otro terminal correr 
//& watch -n 1 "ps -elf | grep a.out"
//la "S" se ve en general porque gran parte del tiempo esta en sleep()
//cuando lo paramos se pone con una "T"
//-----------------------------------------------------------------------------------------------------------

/********************** inclusions *******************************************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
   
/* Project includes. */

/* Demo includes. */


/* Application & Tasks includes. */


/********************** macros and definitions *******************************/
#define FIFO_NAME       "myfifo"
#define STDIN_FD            0
#define STDOUT_FD           1

/********************** internal data declaration ****************************/
 

/********************* internal functions declaration ***********************/

/********************** internal data definition *****************************/


/********************** external data declaration *****************************/


/********************** external functions definition ************************/

int main(void)
{

    if(mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("FIFO doesn't exist");
        exit(1);
    }    
    printf("waiting for writers...\n");
    int fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1)
    {
        perror("FIFO couldn't be open");
        exit(1);
    }    
    printf("got a writer\n");

    char s[300];
    int num;
    do {
        if ((num = read(fd, s, 300)) == -1)
            perror("read");
        else 
        {
            s[num] = '\0';
            printf("reader: read %d bytes: \"%s\"\n", num, s);
            s[num+1] = '\n';
            
            if(0==strncmp(s,"DATA:",5))
            {
                int fddata = open("Log.txt",O_CREAT|O_RDWR|O_APPEND);
                if(fddata == -1)
                {
                    perror("Log.txt couldn't be open");
                }    
                if(write(fddata,s,num+2) == -1)
                    perror("DATA MSG couldn't be written on Log.txt");
                close(fddata);
            }
            else if(0==strncmp(s,"SIGN:1",6))
            {
                int fdsign = open("Sign.txt",O_CREAT|O_RDWR|O_APPEND);
                if(fdsign == -1)
                {
                    perror("Sign.txt couldn't be open");
                }    
                if(write(fdsign,s,num+2) == -1)
                    perror("SIGN:1 MSG couldn't be written on Sign.txt");
                close(fdsign);
            }
            else if(0==strncmp(s,"SIGN:2",6))
            {
               int fdsign = open("Sign.txt",O_CREAT|O_RDWR|O_APPEND);
                if(fdsign == -1)
                {
                    perror("Sign.txt couldn't be open");
                }    
                if(write(fdsign,s,num+2) == -1)
                    perror("SIGN:2 MSG couldn't be written on Sign.txt");
                close(fdsign);
            }   
            else
                perror("Error de Datos");
        }
    }
    while (num > 0);
}
