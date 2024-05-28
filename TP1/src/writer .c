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
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


//Execute on Terminal ./writer

#define FIFO_NAME "myfifo"

int main(void)
{
    mkfifo(FIFO_NAME, 0666);

    printf("waiting for readers...\n");
    int fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader--type some stuff\n");

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
