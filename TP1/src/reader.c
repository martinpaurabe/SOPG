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

#define EXIT_ERROR          1

/********************** internal data declaration ****************************/
 

/********************* internal functions declaration ***********************/

/********************** internal data definition *****************************/


/********************** external data declaration *****************************/


/********************** external functions definition ************************/

int main(void)
{

    if(mkfifo(FIFO_NAME, 0666) == -1)
    {
        if(errno == EEXIST)
            printf("FIFO already exists\n"); 
        else
        {
            perror("FIFO doesn't exist");
            exit(EXIT_ERROR);
        }
    }    
    printf("waiting for writers...\n");
    int fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1)
    {
        perror("FIFO couldn't be open");
        exit(EXIT_ERROR);
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
            s[num+1] = '\n';
            
            if(num<5)
                printf("Error en la cantidad de Datos: %d\n",num);
            else if(0==strncmp(s,"DATA:",5))
            {
                printf("reader: read %d bytes: %s \n",  num, s);
                int fddata = open("Log.txt",O_CREAT|O_WRONLY|O_APPEND);
                if(fddata == -1)
                {
                    if(errno != EEXIST)
                    {
                        perror("Log.txt couldn't be open");
                        exit(EXIT_ERROR);
                    }
                }    
                if(write(fddata,s,num+2) == -1)
                {
                    perror("DATA MSG couldn't be written on Log.txt");
                    close(fddata);
                    exit(EXIT_ERROR);
                }
                while(close(fddata))
                    perror("Log.txt couldn't be open close");
            }
            else if(0==strncmp(s,"SIGN:1",6))
            {
                printf("reader: read %d bytes: %s \n",  num, s);
                int fdsign = open("Sign.txt",O_CREAT|O_WRONLY|O_APPEND);
                if(fdsign == -1)
                {
                    if(errno != EEXIST)
                    {
                        perror("Sign.txt couldn't be open");
                        exit(EXIT_ERROR);
                    }   
                }    
                if(write(fdsign,s,num+2) == -1)
                 {
                    perror("SIGN:1 MSG couldn't be written on Sign.txt");
                    close(fdsign);
                    exit(EXIT_ERROR);
                }
                while(close(fdsign))
                    perror("Sign.txt couldn't be open close");
            }
            else if(0==strncmp(s,"SIGN:2",6))
            {
                printf("reader: read %d bytes: %s \n",  num, s);
                int fdsign = open("Sign.txt",O_CREAT|O_WRONLY|O_APPEND);
                {
                   if(errno != EEXIST)
                    {
                        perror("Sign.txt couldn't be open");
                        exit(EXIT_ERROR);
                    }
                }    
                if(write(fdsign,s,num+2) == -1)
                {
                    perror("SIGN:1 MSG couldn't be written on Sign.txt");
                    close(fdsign);
                    exit(EXIT_ERROR);
                }
                while(close(fdsign))
                    perror("Sign.txt couldn't be open close");
            }   
            else
                printf("Error en formato de Datos\n");
        }
    }
    while (num > 0);
}
