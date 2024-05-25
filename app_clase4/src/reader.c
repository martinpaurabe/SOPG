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
        else {
            s[num] = '\0';
            printf("reader: read %d bytes: \"%s\"\n", num, s);
        }
    }
    while (num > 0);
}
