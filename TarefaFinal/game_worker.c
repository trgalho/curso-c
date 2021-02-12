#include "game_worker.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "loader.h"
#include "utils.h"

static questions_linked_list_t available_questions = { NULL };
static character_info_linked_list_t possible_characters_list = { NULL };

static int active_response_confirmation = 0;

int load_info()
{
	if( load_questions_list() == FAILURE )
		return FAILURE;

	if( load_remarkable_characteristics_list() == FAILURE )
		return FAILURE;

	if( load_characters_info() == FAILURE )
		return FAILURE;

	initialize_available_questions_list();
	initialize_possible_characters_list();

	return SUCCESS;
}

void clean_possible_characters_list()
{
	while( possible_characters_list.head != NULL )
	{
		character_info_node_t* next = possible_characters_list.head->next;

		free( possible_characters_list.head );

		possible_characters_list.head = next;
	}
}

void clean_available_questions_list()
{
	while( available_questions.head != NULL )
	{
		question_node_t* next = available_questions.head->next;

		free( available_questions.head );

		available_questions.head = next;
	}
}

void initialize_possible_characters_list()
{
	clean_possible_characters_list();

	for( int i = 0; i < characters_count; i++ )
	{
		character_info_t* current = &(characters_list[i]);

		character_info_node_t* current_node = (character_info_node_t*) malloc( sizeof( character_info_node_t) );

		current_node->data = current;
		current_node->next = possible_characters_list.head;

		possible_characters_list.head = current_node;
	}
}

void initialize_available_questions_list()
{
	clean_available_questions_list();

	for( int i = 0; i < questions_count; i++ )
	{
		question_t* current = &(questions_list[i]);

		question_node_t* current_node = (question_node_t*) malloc( sizeof( question_node_t) );

		current_node->data = current;
		current_node->next = available_questions.head;

		available_questions.head = current_node;
	}
}

void initialize_all()
{

	initialize_possible_characters_list();
	initialize_available_questions_list();
}



int has_available_questions()
{
	log_user_interaction("Verificando se existem pergunta disponíveis...");
	return available_questions.head != NULL;
}

int know_which_character_is()
{
	log_user_interaction("Verificando se já descobrimos o personagem...");
	return possible_characters_list.head != NULL &&
	possible_characters_list.head->next == NULL;
}

int question_type_matched( question_t* question, int question_type, int question_subtype )
{
	return (
		( question->type == question_type )
		&&
		( question->subtype & question_subtype )
	);
}

int character_question_matched( character_info_t* character_info, question_t* question, int is_ultimate_question, int match_type )
{
	int characteristic_value = 0;

	int result;

	if( is_ultimate_question )
	{
		result = character_info->remarkable_characteristic == question->answer_value;
	}
	else {
		switch( question->type )
		{
			case GENDER:
				characteristic_value = character_info->gender;
				break;
			case HAIR:
				characteristic_value = character_info->hair;
				break;
			case CLOTHES:
				characteristic_value = character_info->clothes;
				break;
			case PET:
				characteristic_value = character_info->pet;
				break;
		}

		result = question->answer_value & characteristic_value;
	}

	// printf("Nome: %s\n", character_info->name);
	// printf("question->type: %d ", question->type);
	// printf("question->answer_value: %d\n", question->answer_value);
	// printf("characteristic_value: %d\n", characteristic_value);
	// printf("result: %d ", result);
	// printf("match_type == YES %d\n\n", match_type == YES);

	return match_type == YES ? result : !result;
}

void remove_question( question_t* question )
{
	log_user_interaction("Removendo a pergunta realizada");

	if( available_questions.head == NULL ) return;

	if( available_questions.head->data == question )
	{
		question_node_t* to_be_removed = available_questions.head;
		available_questions.head = to_be_removed->next;

		free( to_be_removed );
	}
	else
	{
		question_node_t* previous_node = available_questions.head;

		while( previous_node->next != NULL )
		{
			question_node_t* current_node = previous_node->next;

			if( current_node->data == question )
			{
				previous_node->next = current_node->next;

				free( current_node );

				break;
			}
			else
			{
				previous_node = current_node;
			}
		}
	}
}

void remove_invalid_questions( int question_type, int question_subtype )
{
	log_user_interaction("Removendo as perguntas invalidadas pela última resposta");

	if( available_questions.head == NULL ) return;

	question_node_t* previous_question = available_questions.head;

	while( previous_question->next != NULL )
	{
		question_node_t* current_question  = previous_question->next;
		if( question_type_matched( current_question->data, question_type, question_subtype ) )
		{
			previous_question->next = current_question->next;

			free( current_question );
		}
		else
		{
			previous_question = current_question;
		}
	}

	if( question_type_matched( available_questions.head->data, question_type, question_subtype ) )
	{
		question_node_t* to_be_removed = available_questions.head;
		available_questions.head = to_be_removed->next;

		free( to_be_removed );
	}
}

question_t* pick_a_question()
{
	log_user_interaction("Obtendo uma pergunta para o usuário...");

	if( available_questions.head == NULL ){
		log_user_interaction("Nao ha perguntas disponíveis...");
		return NULL;
	}

	srand(time(NULL));   // Initialization, should only be called once.
	int target_question = rand() % MAX_QUESTIONS_LIST_SIZE;

	question_node_t* current_question = available_questions.head;

	// printf("target_question %d\n", target_question);

	for( int i = 0; i <= target_question; i++ )
	{
		if( current_question->next == NULL )
		{
			current_question = available_questions.head;
		}
		else
		{
			current_question = current_question->next;
		}
	}

	// printf("current_question->data->text %s\n", current_question->data->text);

	return current_question->data;
}

int get_user_answer( question_t* question )
{
	char message[255];

	sprintf(message, "O personagem %s", question->text);
	log_user_interaction(message);

	printf("%s\n", message);
	printf("%d - SIM | %d - NAO | Qualquer outro valor - NAO SEI\n", YES, NO );

	int user_typed_answer;

	scan_int( &user_typed_answer );

	int result;

	if ( user_typed_answer < DONT_KNOW ||  user_typed_answer > NO )
		result = DONT_KNOW;
	else
		result = user_typed_answer;

	char *response = ( user_typed_answer == YES ) ? "SIM" : ( (  user_typed_answer == NO ) ? "NAO" : "NAO SEI" );

	printf("A sua resposta é %s\n", response);

	if( active_response_confirmation )
	{

		printf("%d - Confirmar. | Qualquer outro valor para tentar novamente.\n", YES );
		scan_int( &user_typed_answer );
	}
	else
	{
		user_typed_answer = YES;
	}

	printf("\n");

	if( user_typed_answer == YES )
	{
		sprintf(message, "A resposta foi %s", response);
		log_user_interaction(message);

		return result;
	}
	else
	{
		log_user_interaction("Usuario ira tentar novamente...");
		return get_user_answer( question );
	}

}

void process_user_answer( question_t* question, int user_answer)
{
	log_user_interaction("Realizando limpeza nos dados...");

	int process_binary_answer = ( user_answer == NO ) && ( question->answer_possibilities == 2 );

	if( user_answer == DONT_KNOW )
	{
		remove_question( question );
	}
	else
	{
		if( ( user_answer == YES ) || ( question->answer_possibilities == 2 ) )
		{
			remove_invalid_questions( question->type, question->subtype );
		}
		else
		{
			remove_question( question );
		}

		remove_invalid_characters( question, 0, user_answer );
	}
}

void remove_invalid_characters( question_t* question, int is_ultimate_question, int match_type )
{
	log_user_interaction("Remover personagens a partir da resposta da ultima pergunta");

	if( possible_characters_list.head == NULL ) return;

	character_info_node_t* previous_node = possible_characters_list.head;

	while( previous_node->next != NULL )
	{
		character_info_node_t* current_node = previous_node->next;

		if( !character_question_matched( current_node->data, question, is_ultimate_question, match_type ) )
		{
			char message[255];

			sprintf(message, "Removendo personagem %s", current_node->data->name );

			//printf("%s\n\n", message);

			log_user_interaction( message );

			previous_node->next = current_node->next;

			free( current_node );
		}
		else
		{
			previous_node = current_node;
		}
	}

	if( !character_question_matched( possible_characters_list.head->data, question, is_ultimate_question, match_type ) )
	{
		character_info_node_t* to_be_removed = possible_characters_list.head;
		possible_characters_list.head = to_be_removed->next;

		free( to_be_removed );
	}
}

int validate_remarkable_characteristics( int remarkable_characteristic_id )
{
	for( character_info_node_t* current_node = possible_characters_list.head; current_node != NULL; current_node = current_node->next )
	{
		character_info_t* character_info = current_node->data;

		if( character_info->remarkable_characteristic == remarkable_characteristic_id )
			return 1;
	}

	return 0;
}

void do_the_ultimate_question()
{
	int option = 0;
	int is_valid_option = 0;

	log_user_interaction("Realizando a pergunta coringa");

	do{
		printf("Acabaram as perguntas e ainda não sei seu personagem\n");
		printf("Informe uma das caracteristicas a seguir que seu personagem possui?\n");

		for( character_info_node_t* current_node = possible_characters_list.head; current_node != NULL; current_node = current_node->next )
		{
			character_info_t* character_info = current_node->data;

			//printf("Personagem %s ", character_info->name);

			remarkable_characteristic_t rmkble_characteristics = remarkable_characteristics_list[character_info->remarkable_characteristic-1];

			printf("%s - %d\n", rmkble_characteristics.text, rmkble_characteristics.id);
		}

		scan_int( &option );

		is_valid_option = validate_remarkable_characteristics( option );

		char message[255];

		sprintf(message, "O id da caracteristica escolhida: %d", option );

		log_user_interaction( message );

		if( !is_valid_option )
		{
			log_user_interaction("O valor informado estava fora do intervalo válido");
			printf("O valor informado estava fora do intervalo válido\n");
			printf("Tente novamente\n");
		}
	}
	while( !is_valid_option );

	question_t question;
	question.answer_value = option;

	remove_invalid_characters( &question, 1, YES );
}

void ask_user_character_confirmation()
{
	log_user_interaction("Confirmando o personagem que adivinhamos...");

	character_info_t* guess = possible_characters_list.head->data;

	printf("O personagem que voce pensou foi %s?\n", guess->name);

	printf("1 - SIM | Qualquer outra valor - NAO \n");

	int user_answer = 0;


	scan_int(&user_answer);

	char message[255];

	sprintf(message, "O palpite foi %s. A respota do usuario foi %d", guess->name, user_answer);

	log_user_interaction( message );

	if( user_answer == 1 )
	{
		printf("Ja sabia! Conheco tudo sobre turma da monica\n");
	}
	else
	{
		show_user_won_message();
	}
}

void show_user_won_message()
{
	log_user_interaction("O usuario venceu");
	printf("Parabens, voce venceu. Preciso melhorar minhas habilidades\n");
}

void configure_response_confirmation()
{
	printf("Deseja habilitar a confirmacao para as respostas?\n");
	printf("%d - SIM | Qualquer outro valor numerico - NAO\n", YES );

	int user_answer;

	scan_int( &user_answer );

	active_response_confirmation = user_answer == YES;
}
