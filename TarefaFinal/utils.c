#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

void scan_int( int* pInteger )
{
    int shouldReadAgain;
    do
    {
        int integerWasRead = scanf("%d", pInteger);

        /* Se um dos delimitadores não for primeiro caractere lido, identifica que existia lixo apos os valores inteiros lidos */
        int hasTrash = stdin_flush() > 1;

        shouldReadAgain = !( integerWasRead && !hasTrash ); // Equivalente à: um inteiro não foi lido, ou foi lido mas possuia lixo.

        if( shouldReadAgain )
        {
            printf("Valor invalido. Tente novamente\n");
        }
    }
    while ( shouldReadAgain );
}

unsigned int stdin_flush()
{
    char c;
    unsigned int charsRead = 0;
    do{
        c = getchar();
        charsRead++;
    }
    while ( c != '\n' && c != ' ');

    return charsRead;
}

int in_range( int min_value, int max_value, int value )
{
    return min_value <= value && value <= max_value;
}

void log_user_interaction( const char* user_interaction )
{
    FILE* file = fopen( LOG_FILENAME, "a");

    if( file == NULL ) return;

    // printf("%s\n", user_interaction );
    fprintf(file, "%s\n", user_interaction );


    fclose( file );
}

void wait_for_press_any_key()
{
    printf("Pressione qualquer tecla para continuar\n");
    getchar();
}