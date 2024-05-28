//-----------------------------------------------------------------------------------------------------------
//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//En Linux
//se compila por linea de comando con $ gcc -Wall -pedantic ./src/reader.c -o ./build/reader 
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


//Execute on Terminal ./Reader

#define FIFO_NAME "myfifo"

int main(void)
{
    mkfifo(FIFO_NAME, 0666);
    printf("waiting for writers...\n");
    int fd = open(FIFO_NAME, O_RDONLY);
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
                write(fddata,s,num+2);
                close(fddata);
            }
            else if(0==strncmp(s,"SIGN:1",6))
            {
                int fdsign = open("Sign.txt",O_CREAT|O_RDWR|O_APPEND);
                write(fdsign,s,num+2);
                close(fdsign);
            }
            else if(0==strncmp(s,"SIGN:2",6))
            {
                int fdsign = open("Sign.txt",O_CREAT|O_RDWR|O_APPEND);
                write(fdsign,s,num+2);
                close(fdsign);
            }   
            else
                perror("Error de Datos");
        }
    }
    while (num > 0);
}
