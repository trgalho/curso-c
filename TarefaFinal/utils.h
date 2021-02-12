#ifndef FINAL_TASK_UTILS_H
#define FINAL_TASK_UTILS_H

/** Realiza a leitura de inteiros da entrada padrão. */
void scan_int( int* pInteger );

/**
 * Consome todos os valores do buffer de entrada anteriores ao caractere '\n' ou o caractere ' '.
 * Retorna o número de caracteres lidos até encontrar um dos delimitadores.
 */
unsigned int stdin_flush();

/** Verifica so o numero informado esta no intervalo desejado */
int in_range( int min_value, int max_value, int value );

void log_user_interaction( const char* user_interaction );

void wait_for_press_any_key();

#endif //FINAL_TASK_UTILS_H