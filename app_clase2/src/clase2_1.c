//cd C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>
//C:\Users\mpaur\OneDrive\Documentos\ITBA\MESE\SOPG\Practica\SOPG_Practica\app\src>start prueba.exe
//En Linux se ejecuta con .\prueba

#include <stdio.h>
#include <unistd.h>

void main(void)
{
    int i=10;
    while(1)
    {
        printf("numero %d\n\r",i++);
        sleep(1);
    }    
    return;
}