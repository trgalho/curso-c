#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define SQUARE_MATRIX_MAX_ORDER 6
#define SQUARE_MATRIZ_MIN_ORDER 1

// Ao habilitar este define os valores da matriz não serão lidos e será utilizado apenas lixo de memoria.
//#define USE_MEMORY_TRASH

// Habilitar este define faz com que a matriz seja impressa após seu preenchimento
#define PRINT_MATRIX

/** Se definido para um valor 'verdadeiro'. Não é realizado o processo para o calculo do cofator de um elemento de valor 0.*/
static const int optimize_resolution = 1;

/** Verifica se a ordem informada para a matriz quadrada é válida. */
int check_square_matrix_order( const int square_matrix_order );

/** Realiza a leitura de inteiros da entrada padrão. */
void scan_int( int* pInteger );

/** Imprime uma matriz de inteiros de tamanho rows*columns */
void print_matrix( int rows, int columns, int matrix[rows][columns] );

/**
 * Calcula o determinante de uma matriz utilizando o Teorema de Laplace.
 * O calculo é realizado via recursão, gerando submatrizes para o calculo dos cofatores
 * dos elementos da primeira coluna.
 */
double determinant_laplace_expansion( int matrix_order, int square_matrix[matrix_order][matrix_order] );

/** Consome todos os valores do buffer de entrada anteriores ao caractere '\n' ou o caractere ' ' */
void stdin_flush();

int main (void)
{
    int square_matrix_order;

    printf("Informe a ordem da matriz quadrada a ser lida ( O valor deve ser entre %d e %d, inclusive): ", SQUARE_MATRIZ_MIN_ORDER, SQUARE_MATRIX_MAX_ORDER);
    scan_int(&square_matrix_order);
    printf("\n");

    int exitCode = EXIT_SUCCESS;

    if( !check_square_matrix_order( square_matrix_order ) )
    {
        printf("Foi informada uma ordem de matriz quadrada nao suportada.\n");
        printf("Ordem de matriz quadrada informada: %d\n", square_matrix_order );
        exitCode = EXIT_FAILURE;
    }
    else
    {
        int square_matrix[square_matrix_order][square_matrix_order];

        #ifdef USE_MEMORY_TRASH
            printf("Sera utilizado lixo de memoria para os valores da matriz.\n");
        #else
            printf("Preencha a matriz quadrada (apenas inteiros):\n");
        #endif

        for( int i=0; i < square_matrix_order; i++ )
        {
            for( int j=0;j < square_matrix_order; j++)
            {
                #ifndef USE_MEMORY_TRASH
                    printf("Insira o numero para a posicao [%d][%d]: ", i,j);
                    scan_int(&square_matrix[i][j]);
                    printf("\n");
                #endif // USE_MEMORY_TRASH
            }
        }

        #ifdef PRINT_MATRIX
            print_matrix( square_matrix_order, square_matrix_order, square_matrix );
            printf("\n");
        #endif // PRINT_MATRIX

        double determinant = determinant_laplace_expansion(square_matrix_order, square_matrix );

        printf("Determinante: %0.f\n",determinant );

    }

    return exitCode;
}

void print_matrix( int rows, int columns, int matrix[rows][columns]  )
{
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            printf("%12d", matrix[i][j]);
        }
        printf("\n");
    }
}

int check_square_matrix_order( const int square_matrix_order )
{
    return square_matrix_order >= SQUARE_MATRIZ_MIN_ORDER  && square_matrix_order <= SQUARE_MATRIX_MAX_ORDER;
}

void stdin_flush()
{
    char c;
    do{
        c = getchar();
    }
    while ( c != '\n' && c != ' ');
}

void scan_int( int* pInteger )
{
    while ( ! scanf("%d", pInteger) ) {
        stdin_flush();
        printf("Valor invalido. Tente novamente\n");
    };

    stdin_flush();
}

double determinant_laplace_expansion( int matrix_order, int square_matrix[matrix_order][matrix_order] )
{
    // Numa matriz de ordem 1, o determinante é o valor do único elemento da matriz.
    if( matrix_order == 1 )
    {
        return square_matrix[0][0];
    }
    else
    {
        double determinant = 0;

        /** Coluna utilizada para o cálculo dos cofatores */
        const int tgt_column_idx = 0;

        /** Itera pelos elementos da coluna, calculando os cofatores */
        for( int tgt_row_idx = 0; tgt_row_idx < matrix_order; tgt_row_idx++ )
        {
            /** Elemento do qual será calculado o cofator */
            const int tgt_element = square_matrix[tgt_row_idx][tgt_column_idx];

            if( tgt_element  != 0 || !optimize_resolution )
            {
                int submatrix_order = matrix_order - 1;
                int submatrix[submatrix_order][submatrix_order];

                int submatrix_row_idx = 0;

                for( int mtx_row_idx = 0; mtx_row_idx <matrix_order; mtx_row_idx++)
                {
                    int submatrix_column_idx = 0;

                    /** Ignora a linha do elemento que será gerado o cofator*/
                    if( mtx_row_idx != tgt_row_idx )
                    {
                        for( int mtx_column_idx = 0; mtx_column_idx < matrix_order; mtx_column_idx++ )
                        {
                            /** Ignora a coluna do elemento que será gerado o cofator*/
                            if( mtx_column_idx != tgt_column_idx )
                            {
                                submatrix[submatrix_row_idx][submatrix_column_idx] = square_matrix[mtx_row_idx][mtx_column_idx];

                                submatrix_column_idx++;
                            }
                        }
                        submatrix_row_idx++;
                    }
                }

                /** Equivalente a expressão (-1)^(i+j) do Teorema de Laplace */
                const int cofactor_signal_modifier = tgt_row_idx  % 2 ? -1 : 1;

                const double cofactor = determinant_laplace_expansion( submatrix_order, submatrix );

                determinant += tgt_element * cofactor_signal_modifier * cofactor;
            }
        }

        return determinant;
    }
}
