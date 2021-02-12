#include "game.h"

#include <stdio.h>

#include "game_worker.h"

#include "helper.h"
#include "loader.h"
#include "utils.h"

#include "debug.h"

void print_characters_list()
{
	if( characters_count <= 0 )
	{
		printf("As informacões não foram carregadas corretamente \n");
		return;
	}

	printf("Personagens conhecidos:\n");

	for( int i=0; i < characters_count; i++ )
	{
		printf("%s\n", characters_list[i].name);
	}

	printf("------------------------------------\n");
}

void reset_game()
{
	log_user_interaction("Resetando o estado atual do jogo.");
	initialize_all();
}

void start_game()
{
	log_user_interaction("Iniciando a partida");
	initialize_all();

	configure_response_confirmation();

	while( has_available_questions() && !know_which_character_is() )
	{
		question_t* question = pick_a_question();

		int user_answer = get_user_answer( question );

		process_user_answer( question, user_answer );
	}

	if( !know_which_character_is() )
	{
		do_the_ultimate_question();
	}

	if( know_which_character_is() )
		ask_user_character_confirmation();
	else
		show_user_won_message(); 

	log_user_interaction("Partida finalizada");
}

int run()
{
	if( load_info() == FAILURE )
	{
		printf("Falha ao carregar as informações para o jogo\n");

		return FAILURE;
	}

	int quit_game = 0;

	while( !quit_game )
	{

		print_menu();
		
		switch( read_menu_option() )
		{
			case START_GAME:
				start_game();
				break;
			case SHOW_HELP:
				print_help_text();
				wait_for_press_any_key();
				break;
			case SHOW_CHARACTERS_LIST:
				print_characters_list();
				wait_for_press_any_key();
				break;
			case QUIT_GAME:
				log_user_interaction("Finalizando o jogo.");
				quit_game = 1;
				break;
		};
	}

	return SUCCESS;
}

void print_menu()
{
	printf("\n\n\t\tTURMA DA MONICANATOR\n\n");
	printf("-------------------------------------------------\n");
	printf("%d - Começar uma nova partida\n", START_GAME);
	printf("%d - Exibir ajuda sobre o jogo\n", SHOW_HELP);
	printf("%d - Exibir a lista de personagens\n", SHOW_CHARACTERS_LIST);
	printf("%d - Encerrar a aplicação\n", QUIT_GAME);
	printf("-------------------------------------------------\n");
}

void print_help_text()
{
	printf("\n\n\n");
	printf("Sobre o jogo:\n");
	printf("\tO jogo consiste em tentar adivinhar qual personagem da lista de personagens conhecidos o usuário esta pensando.\n");
	printf("\tO jogador ganha, caso o jogo não consiga adivinhar o personagem que ele está pensando.\n");
	printf("\n");
	printf("Sobre a partida:\n");
	printf("\tApós iniciada a pertida nao pode ser cancelada. Isto e, deve se jogar ate que tenhamos um vencedor.\n");
	printf("\tQualquer outro valor diferente do valor de SIM ou NAO, interpretasse como não sei.\n");
	printf("\tAs opções para a resposta da pergunta coringa serão de acordo com as possibilidades de personagens restantes.\n");
	printf("\n");
	printf("-------------------------------------------------\n");	
}

int read_menu_option()
{
	int option;

	scan_int( &option );

	if( in_range( START_GAME, QUIT_GAME, option) )
	{
		return option;
	}
	else
	{
		printf("Opção inválida (%d). Tente novamente.\n", option);

		return read_menu_option();
	}
}