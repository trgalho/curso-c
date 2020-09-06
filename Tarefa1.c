#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define SQUARE_MATRIX_MAX_ORDER 6
#define SQUARE_MATRIZ_MIN_ORDER 1

// Ao habilitar este define os valores da matriz não serão lidos e será utilizado apenas lixo de memoria.
//#define USE_MEMORY_TRASH

// Habilitar este define faz com que a matriz seja impressa após seu preenchimento
//#define PRINT_MATRIX

/** Verifica se a ordem informada para a matriz quadrada é válida. */
int check_square_matrix_order( const int square_matrix_order );

/** Realiza a leitura de inteiros da entrada padrão. */
void scan_int( int* pInteger );

/** Consome todos os valores do buffer de entrada anteriores ao caractere '\n' */
void stdin_flush();

int main (void)
{
    int square_matrix_order;

    printf("Informe a ordem da matriz quadrada a ser lida ( O valor deve ser entre %d e %d, inclusive): ", SQUARE_MATRIZ_MIN_ORDER, SQUARE_MATRIX_MAX_ORDER);
    scan_int(&square_matrix_order);

    int exitCode = EXIT_SUCCESS;

    if( !check_square_matrix_order( square_matrix_order ) )
    {
        printf("Foi informada uma ordem de matriz quadrada nao suportada.\n");
        printf("Ordem de matriz quadrada informada: %d\n", square_matrix_order );
        exitCode = EXIT_FAILURE;
    }
    else
    {
        int lowest_number_found = INT_MAX;
        int lines_containing_the_lowest_number[square_matrix_order];
        int number_of_ocurrencies = 0;

        int square_matrix[square_matrix_order][square_matrix_order];

        #ifdef USE_MEMORY_TRASH
            printf("Sera utilizado lixo de memoria para os valores da matriz.\n");
        #else
            printf("Preencha a matriz quadrada:\n");
        #endif

        for( int i=0; i < square_matrix_order; i++ )
        {
            for( int j=0;j < square_matrix_order; j++)
            {
                #ifndef USE_MEMORY_TRASH
                    printf("Insira o numero para a posicao [%d][%d]: ", i,j);
                    scan_int(&square_matrix[i][j]);
                #endif // USE_MEMORY_TRASH

                if( number_of_ocurrencies == 0 || square_matrix[i][j] < lowest_number_found )
                {
                    number_of_ocurrencies = 1;

                    lines_containing_the_lowest_number[0] = i;

                    lowest_number_found = square_matrix[i][j];
                }
                else if( square_matrix[i][j] == lowest_number_found )
                {
                    int last_line_index_found = lines_containing_the_lowest_number[number_of_ocurrencies - 1];

                    if( last_line_index_found != i)
                    {
                        lines_containing_the_lowest_number[number_of_ocurrencies] = i;
                        number_of_ocurrencies++;
                    }
                }
            }
        }

        #ifdef PRINT_MATRIX
            for( int i=0; i < square_matrix_order; i++ )
            {
                for( int j=0;j < square_matrix_order; j++)
                {
                    printf("%12d ", square_matrix[i][j]);
                }
                printf("\n");
            }
        #endif // PRINT_MATRIX

        printf("Menor numero encontrado na matriz: %d\n", lowest_number_found);

        printf("Linha(s) contendo o menor número da matriz:\n");
        for( int i=0; i < number_of_ocurrencies; i++)
        {
            printf("%d\n", lines_containing_the_lowest_number[i]);
        }
    }

    return exitCode;
}

int check_square_matrix_order( const int square_matrix_order )
{
    return square_matrix_order >= SQUARE_MATRIZ_MIN_ORDER  && square_matrix_order <= SQUARE_MATRIX_MAX_ORDER;
}

void stdin_flush()
{
    while ((getchar()) != '\n');
}

void scan_int( int* pInteger )
{
    while ( ! scanf("%d", pInteger) ) {
        stdin_flush();
        printf("Valor invalido. Tente novamente\n");
    };

    stdin_flush();
}
