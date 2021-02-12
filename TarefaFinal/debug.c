#include "debug.h"

#include <stdio.h>

void print_full_character_info( character_info_t* character_info )
{
	printf("Nome: %s\n", character_info->name );
	printf("Sexo: %d\n", character_info->gender );
	printf("Cabelo: %d\n", character_info->hair );
	printf("Roupas: %d\n", character_info->clothes );
	printf("Pet: %d\n", character_info->pet );
	printf("Caracteristica marcante: %d\n", character_info->remarkable_characteristic);
}

void print_full_question_info( question_t* question )
{
	printf("Texto: %s\n", question->text );
	printf("Tipo: %d\n", question->type );
	printf("Subtipo: %d\n", question->subtype );
	printf("Valor de resposta: %d\n", question->answer_value );	
}

void print_full_rmkble_characteristics( remarkable_characteristic_t* rmkble_characteristic )
{
	printf("Id: %d\n", rmkble_characteristic->id );
	printf("Texto: %s\n", rmkble_characteristic->text );
}
