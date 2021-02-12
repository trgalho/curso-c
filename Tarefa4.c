#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <locale.h>

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
void transpose_matrix( int matrix_order, int square_matrix[matrix_order][matrix_order], int transposed_matrix[matrix_order][matrix_order]);

/** realiza a soma de duas matrizes quadradas de mesma ordem */
void add_matrices( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order] );

/** realiza a multiplicaçao de duas matrizes quadradas de mesma ordem */
void multiply_matrices( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order] );

/** multiplica a linha pela coluna de duas matrizes */
double multiply_row_col( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order], int row, int col );

/** Verifica so o numero informado esta no intervalo desejado */
int in_range( int min_value, int max_value, int value );

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
    setlocale(LC_ALL,"");

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
        const int num_of_matrices = 2;

        int square_matrices[num_of_matrices][square_matrix_order][square_matrix_order];

        for( int i = 0; i < num_of_matrices; i++ )
        {
            #ifdef USE_MEMORY_TRASH
                printf("Sera utilizado lixo de memoria para os valores da matriz.\n");
            #else
                printf("Preencha a matriz quadrada %d (apenas inteiros):\n", i+1);
                fill_matrix( square_matrix_order, square_matrix_order, square_matrices[i]);
            #endif
        }


        int is_valid_option = 0;
        int user_choice=-1;

        do {
            printf("Escolha a matrix que será transposta para a realização da soma (1-%d):\n",num_of_matrices);
            scan_int(&user_choice);
            is_valid_option = in_range( 1, num_of_matrices, user_choice);

            if( !is_valid_option )
            {
                printf("A opção escolhida é inválida. Opção: %d\n", user_choice);
            }

        } while( !is_valid_option );

        int choosen_index = user_choice-1;

        int transposed_matrix[square_matrix_order][square_matrix_order];

        transpose_matrix(square_matrix_order, square_matrices[choosen_index], transposed_matrix );

        multiply_matrices(square_matrix_order, square_matrices[0], square_matrices[1]);

        int original_matrix_index = choosen_index == 1 ? 0 : 1;

        add_matrices(square_matrix_order, square_matrices[original_matrix_index], transposed_matrix );
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

void transpose_matrix( int matrix_order, int square_matrix[matrix_order][matrix_order], int transposed_matrix[matrix_order][matrix_order])
{
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

void add_matrices( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order] )
{
    printf("Realizando a soma da matrix A com a matrix B:\n");

    printf("Matrix A:\n");
    print_matrix( matrix_order, matrix_order, mtx_1);
    printf("\n");

    printf("Matrix B:\n");
    print_matrix( matrix_order, matrix_order, mtx_2);
    printf("\n");

    double result_matrix[matrix_order][matrix_order];

    for( int i=0; i< matrix_order; i++ )
    {
        for( int j=0; j< matrix_order; j++ )
        {
            result_matrix[i][j]= mtx_1[i][j] + mtx_2[i][j];
        }
    }

    printf("Matriz com o resultado da soma:\n");
    print_matrix_double( matrix_order, matrix_order, result_matrix);
    printf("\n");
}


void multiply_matrices( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order] )
{
    printf("Realizando a multiplicação da matrix A com a matrix B:\n");

    printf("Matrix A:\n");
    print_matrix( matrix_order, matrix_order, mtx_1);
    printf("\n");

    printf("Matrix B:\n");
    print_matrix( matrix_order, matrix_order, mtx_2);
    printf("\n");

    double result_matrix[matrix_order][matrix_order];

    for( int i=0; i< matrix_order; i++ )
    {
        for( int j=0; j< matrix_order; j++ )
        {
            result_matrix[i][j] = multiply_row_col(
                matrix_order,
                mtx_1,
                mtx_2,
                i,j
            );
        }
    }

    printf("Matriz com o resultado da multiplicação:\n");
    print_matrix_double( matrix_order, matrix_order, result_matrix);
    printf("\n");
}

double multiply_row_col( int matrix_order, int mtx_1[matrix_order][matrix_order], int mtx_2[matrix_order][matrix_order], int row, int col )
{
    double result=0;


    for( int i=0; i < matrix_order; i++ )
    {
        //printf("%d %d", )
        result += mtx_1[row][i]*mtx_2[i][col];
    }

    return result;
}

int in_range( int min_value, int max_value, int value )
{
    return min_value <= value && value <= max_value;
}
