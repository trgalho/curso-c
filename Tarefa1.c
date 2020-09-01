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
int checkSquareMatrixOrder( const int pOrdemMatrizQuadrada );

int main (void)
{
    int squareMatrixOrder;

    printf("Informe a ordem da matriz quadrada a ser lida ( O valor deve ser entre %d e %d, inclusive): ", SQUARE_MATRIZ_MIN_ORDER, SQUARE_MATRIX_MAX_ORDER);
    scanf("%d", &squareMatrixOrder);

    int exitCode = EXIT_SUCCESS;

    if( !checkSquareMatrixOrder( squareMatrixOrder ) )
    {
        printf("Foi informada uma ordem de matriz quadrada não suportada.\n");
        printf("Ordem de matriz quadrada informada: %d\n", squareMatrixOrder );
        exitCode = EXIT_FAILURE;
    }
    else
    {
        int lowerNumberFound = INT_MAX;
        int lowerNumberLineIndex = 0;

        int squareMatrix[squareMatrixOrder][squareMatrixOrder];

        #ifdef USE_MEMORY_TRASH
            printf("Sera utilizado lixo de memórioa para os valores da matriz.\n");
        #else
            printf("Preencha a matriz quadrada:\n");
        #endif

        for( int i=0; i < squareMatrixOrder; i++ )
        {
            for( int j=0;j < squareMatrixOrder; j++)
            {
                #ifndef USE_MEMORY_TRASH
                    printf("Insira o número para a posição [%d][%d]: ", i,j);
                    scanf("%d", &squareMatrix[i][j]);
                #endif // USE_MEMORY_TRASH

                if( squareMatrix[i][j] <= lowerNumberFound )
                {
                    lowerNumberFound = squareMatrix[i][j];
                    lowerNumberLineIndex = i;
                }
            }
        }

        #ifdef PRINT_MATRIX
            for( int i=0; i < squareMatrixOrder; i++ )
            {
                for( int j=0;j < squareMatrixOrder; j++)
                {
                    printf("%12d ", squareMatrix[i][j]);
                }
                printf("\n");
            }
        #endif // PRINT_MATRIX

        printf("Linha contendo o menor número da matriz: %d\n", lowerNumberLineIndex+1);
        printf("Menor número encontrado na matriz: %d\n", lowerNumberFound);
    }

    return exitCode;
}

int checkSquareMatrixOrder( const int pOrdemMatrizQuadrada )
{
    return pOrdemMatrizQuadrada >= SQUARE_MATRIZ_MIN_ORDER  && pOrdemMatrizQuadrada <= SQUARE_MATRIX_MAX_ORDER;
}
