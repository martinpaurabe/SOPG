#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define STDIN_FD   0
#define STDOUT_FD   1

int main(void) {
    int pfds[2];
    pipe(pfds);

    if (!fork()) { // hijo
        dup2(pfds[1], STDOUT_FD); // reemplaza el stdout del hijo por el
                          // FD para write (y cierra el stdout)
        close(pfds[0]);           // cerramos read
        execlp("ls", "ls", NULL); // reemplaza proceso hijo
                                  // por "ls"
    } else {                      // padre
        dup2(pfds[0], STDIN_FD); // reemplaza el stdin del padre
                          // por el FD para read (y cierra el stdin)
        close(pfds[1]);   // cerramos el FD para write
        execlp("wc", "wc", "-l", NULL); // reemplaza proceso
                                        // padre por "wc -l"
    }
    return 0;
}