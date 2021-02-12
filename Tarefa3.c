#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define SQUARE_MATRIX_MAX_ORDER 6
#define SQUARE_MATRIZ_MIN_ORDER 1

// Ao habilitar este define os valores da matriz não serão lidos e será utilizado apenas lixo de memoria.
//#define USE_MEMORY_TRASH

// Habilitar este define faz com que a matriz seja impressa após seu preenchimento
#define PRINT_MATRIX

/** Verifica se a ordem informada para a matriz quadrada é válida. */
int check_square_matrix_order( const int square_matrix_order );

/** Realiza a leitura de inteiros da entrada padrão. */
void scan_int( int* pInteger );

/** Imprime uma matriz de inteiros de tamanho rows*columns */
void print_matrix( int rows, int columns, int matrix[rows][columns] );

/** Imprime uma matriz de numeros em ponto-flutuante com precisao dupla de tamanho rows*columns */
void print_matrix_double( int rows, int columns, double matrix[rows][columns] );

/** Realiza a transposição de uma matriz quadrada de inteiros */
void transpose_matrix( int matrix_order, int square_matrix[matrix_order][matrix_order]);

/**
 * Calcula a matriz inversa de uma matriz quadrada.
 *
 * A implementação utiliza o algoritmo proposto por Farooq Ahmad ( Albaha University - Saudi Arabia ) e Hamid Khan ( National University of Computer And Emerging Sciences - Pakistan ).
 *
 * O calculo é baseado no uso dos valores da diagonal principal, e de forma iterativa gerando o determinante e os valores da matriz inversa.
 *
 * Complexidade computacional O(n³)
 *
 * Publicação: Ahmad, Farooq & Khan, Hamid. (2010). An Efficient and Simple Algorithm for Matrix Inversion. IJTD. 1. 20-27. 10.4018/jtd.2010010102.
 */
void inverse_matrix_ahmad_khan_algorithm( int matrix_order, int square_matrix[matrix_order][matrix_order] );

/**
 * Atualiza os valores de uma matriz inversa sendo gerada pelo algoritmo Ahmd-Khan.
 */
void update_inverse_matrix_values( int matrix_order, double inverse_matrix[matrix_order][matrix_order], int pivot, double* determinant );


/**
 * Consome todos os valores do buffer de entrada anteriores ao caractere '\n' ou o caractere ' '.
 * Retorna o número de caracteres lidos até encontrar um dos delimitadores.
 */
unsigned int stdin_flush();

/**
 * Preenche uma matrix de inteiros a partir de entrada padrão.
 */
void fill_matrix( int rows, int columns, int matrix[rows][columns] );

int main (void)
{
    int square_matrix_order;

    printf("Informe a ordem da matriz quadrada a ser lida ( O valor deve ser entre %d e %d, inclusive): ", SQUARE_MATRIZ_MIN_ORDER, SQUARE_MATRIX_MAX_ORDER);
    scan_int(&square_matrix_order);
    printf("\n");

    int exitCode = EXIT_SUCCESS;

    if( !check_square_matrix_order( square_matrix_order ) )
    {
        printf("Foi informada uma ordem de matriz quadrada não suportada.\n");
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
            fill_matrix( square_matrix_order, square_matrix_order, square_matrix);
        #endif

        transpose_matrix(square_matrix_order, square_matrix);

        inverse_matrix_ahmad_khan_algorithm(square_matrix_order, square_matrix);
    }

    return exitCode;
}

void fill_matrix( int rows, int columns, int matrix[rows][columns] )
{
    for( int i=0; i < rows; i++ )
    {
        for( int j=0;j < columns; j++)
        {
            printf("Insira o numero para a posicao [%d][%d]: ", i,j);
            scan_int(&matrix[i][j]);
            printf("\n");
        }
    }

    printf("Matriz informada:\n");
    print_matrix(rows, columns, matrix);
    printf("\n");
}

void print_matrix( int rows, int columns, int matrix[rows][columns] )
{
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            printf("%12d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_double( int rows, int columns, double matrix[rows][columns] )
{
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            printf("%12f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int check_square_matrix_order( const int square_matrix_order )
{
    return square_matrix_order >= SQUARE_MATRIZ_MIN_ORDER  && square_matrix_order <= SQUARE_MATRIX_MAX_ORDER;
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

void transpose_matrix( int matrix_order, int square_matrix[matrix_order][matrix_order])
{
    int transposed_matrix[matrix_order][matrix_order];

    for( int mtx_row_idx = 0; mtx_row_idx < matrix_order; mtx_row_idx++ )
    {
        for( int mtx_col_idx = 0; mtx_col_idx < matrix_order; mtx_col_idx++ )
        {
            transposed_matrix[mtx_col_idx][mtx_row_idx] = square_matrix[mtx_row_idx][mtx_col_idx];
        }
    }

    printf("Matriz transposta gerada:\n");
    print_matrix( matrix_order, matrix_order, transposed_matrix);
    printf("\n");
}

void update_inverse_matrix_values( int matrix_order, double inverse_matrix[matrix_order][matrix_order], int pivot, double* determinant )
{
    const double pivotValue = inverse_matrix[pivot][pivot];

    *determinant = (*determinant) * pivotValue;

    //printf("pivotValue %lf ", pivotValue);
    //printf("determinant %lf\n", *determinant);

    if( *determinant == 0.0f) return;

    for( int i = 0; i < matrix_order; i++ )
    {
        if( i != pivot )
        {
            inverse_matrix[i][pivot] =  (inverse_matrix[i][pivot]/pivotValue) * -1;
        }
    }

    for( int i = 0; i < matrix_order; i++ )
    {
        if( i != pivot )
        {
            for( int j = 0; j < matrix_order; j++)
            {
                if( j != pivot )
                {
                    double aux_pivot_value = ( inverse_matrix[pivot][j] * inverse_matrix[i][pivot]);
                    //printf("aux_pivot_vaue %d %d = %lf\n", i, j, aux_pivot_value);
                    inverse_matrix[i][j] = inverse_matrix[i][j] + aux_pivot_value;
                }
            }
        }
    }

    for( int j = 0; j < matrix_order; j++ )
    {
        if( j != pivot )
        {
            inverse_matrix[pivot][j] = inverse_matrix[pivot][j]/pivotValue;
        }
    }


    inverse_matrix[pivot][pivot] = ( 1.0f / pivotValue );

    //print_matrix_double(matrix_order, matrix_order, inverse_matrix);
    //printf("\n");
}

void inverse_matrix_ahmad_khan_algorithm( int matrix_order, int square_matrix[matrix_order][matrix_order])
{
    double inverse_matrix[matrix_order][matrix_order];

    for( int mtx_row_idx = 0; mtx_row_idx < matrix_order; mtx_row_idx++ )
    {
        for( int mtx_col_idx = 0; mtx_col_idx < matrix_order; mtx_col_idx++ )
        {
            inverse_matrix[mtx_row_idx][mtx_col_idx] = square_matrix[mtx_row_idx][mtx_col_idx];
        }
    }

    double determinant = 1;

    /** Vetor de indices pivo a serem revisitados */
    int revisitIndexArray[matrix_order];
    /** Numero de indices a serem revisitados */
    int revisitCount=0;

    for( int pivot = 0; pivot < matrix_order; pivot ++ )
    {
        const double pivotValue = inverse_matrix[pivot][pivot];

        /** Caso o valor pivo seja zero, o indice deve ser revisitado. Ao final da iteração */
        if( pivotValue == 0.0f)
        {
            revisitIndexArray[revisitCount]=pivot;
            revisitCount++;
            continue;
        }

        update_inverse_matrix_values(matrix_order, inverse_matrix, pivot, &determinant );
    }

    for( int revisitIndex = 0; revisitIndex < revisitCount; revisitIndex ++ )
    {
        const int pivot = revisitIndexArray[revisitIndex];

        update_inverse_matrix_values(matrix_order, inverse_matrix, pivot, &determinant );

        if( determinant == 0.0f) break;
    }

    if( determinant )
    {
        printf("Matriz inversa gerada\n");
        print_matrix_double(matrix_order, matrix_order, inverse_matrix);
        printf("\n");
    }
    else
    {
        printf("Impossivel gerar a matriz inversa.\n");
    }
}
