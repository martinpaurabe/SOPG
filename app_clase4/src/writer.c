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
