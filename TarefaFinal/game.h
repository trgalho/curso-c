#ifndef FINAL_TASK_GAME_H
#define FINAL_TASK_GAME_H

int run();

/** Imprime o menu com as opções disponiveis para o usuário. */
void print_menu();

void print_help_text();

/** Aguarda o usuário informar a opção desejado. Caso escolha uma opção inválida a leitura será realizada novamente. */
int read_menu_option();

void print_characters_list();

void reset_game();

void start_game();

#endif //FINAL_TASK_GAME_H