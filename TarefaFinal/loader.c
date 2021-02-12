#define FINAL_TASK_LOADER_C
#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"



int is_delimiter( char current_char )
{
	return  current_char == ',' || current_char == '\n' || current_char == EOF;
}

int get_character_info( FILE *file, character_info_t* current )
{
	int max_size = 100;
	char buffer[max_size];

	int count = 0;
	char current_char = 0;

	int comma_counter = 0;

	int max_char_size = max_size - 1;
	do {
		current_char = fgetc( file );		

		if( is_delimiter(current_char) )
		{
			buffer[count] = '\0';

			if( comma_counter == 0 )
			{
				strcpy( current->name, buffer);
			}
			else
			{

				int value = atoi( buffer );

				// Zero nunca é um valor válido.
				if( value == 0 ) return FAILURE;

				if( comma_counter == 1)
					current->gender = value;
				else if( comma_counter == 2)
					current->hair = value;
				else if( comma_counter == 3)
					current->clothes = value;
				else if( comma_counter == 4)
					current->pet = value;
				else if( comma_counter == 5)
					current->remarkable_characteristic = value;
			}

			buffer[0]='\0';
			count = 0;

			comma_counter++;
		}
		else
		{
			buffer[count] = current_char;
			count++;
		}
	}
	while( ! ( count >= max_char_size || current_char == '\n' || current_char == EOF ) );

	if( comma_counter < 6 ) return FAILURE;

	return 0;
}

int get_question( FILE *file, question_t* question )
{
	int max_size = 100;
	char buffer[max_size];

	int count = 0;
	char current_char = 0;

	int comma_counter = 0;

	int max_char_size = max_size - 1;
	do {
		current_char = fgetc( file );		

		if( is_delimiter(current_char) )
		{
			buffer[count] = '\0';

			if( comma_counter == QUESTION_TEXT )
			{
				strcpy( question->text, buffer);
			}
			else
			{
				int value = atoi( buffer );

				// Zero nunca é um valor válido.
				if( value == 0 ) return FAILURE;

				if( comma_counter == QUESTION_TYPE )
					question->type = value;
				else if( comma_counter == QUESTION_SUBTYPE )
					question->subtype = value;
				else if( comma_counter == QUESTION_ANSWER_VALUE)
					question->answer_value = value;
				else if( comma_counter == QUESTION_ANSWER_POSSIBILITIES)
					question->answer_possibilities = value;
			}

			buffer[0]='\0';
			count = 0;

			comma_counter++;
		}
		else
		{
			buffer[count] = current_char;
			count++;
		}
	}
	while( ! ( count >= max_char_size || current_char == '\n' || current_char == EOF ) );

	if( comma_counter < 5 ) return FAILURE;

	return 0;
}

int get_remarkable_characteristic( FILE *file, remarkable_characteristic_t* characteristic )
{
	int max_size = 100;
	char buffer[max_size];

	int count = 0;
	char current_char = 0;

	int comma_counter = 0;

	int max_char_size = max_size - 1;
	do {
		current_char = fgetc( file );		

		if( is_delimiter(current_char) )
		{
			buffer[count] = '\0';

			if( comma_counter == REMARKABLE_CHARACTERISTIC_TEXT )
			{
				strcpy( characteristic->text, buffer);
			}
			else
			{
				int value = atoi( buffer );

				// Zero nunca é um valor válido.
				if( value == 0 ) return FAILURE;

				if( comma_counter == REMARKABLE_CHARACTERISTIC_ID )
					characteristic->id = value;
			}

			buffer[0]='\0';
			count = 0;

			comma_counter++;
		}
		else
		{
			buffer[count] = current_char;
			count++;
		}
	}
	while( ! ( count >= max_char_size || current_char == '\n' || current_char == EOF ) );

	if( comma_counter < 2 ) return FAILURE;

	return 0;
}

int load_characters_info()
{
	FILE *cFile;

	cFile = fopen(CHARACTERS_LIST_FILENAME, "r");

	// IMPOSSIVEL LER LISTA DE PERSONAGENS
	if( cFile == NULL ) return FAILURE;

	int characters_counter = 0;

	char dummy_string[100];
	fscanf( cFile, "%s\n", dummy_string); // descarta a primeira linha

	while( !feof( cFile ) )
	{
		if( characters_counter >= MAX_CHARACTERES_LIST_SIZE )
			return FAILURE;

		character_info_t* current = &(characters_list[characters_counter]);

		int result = get_character_info( cFile, current);

		if( result == FAILURE ) return FAILURE;

		characters_counter++;
	}

	fclose( cFile );

	characters_count = characters_counter;

	return SUCCESS;
}

int load_questions_list()
{
	FILE *file;

	file = fopen(QUESTIONS_LIST_FILENAME, "r");

	// IMPOSSIVEL LER LISTA DE PERGUNTAS
	if( file == NULL ) return FAILURE;

	int questions_counter = 0;

	char dummy_string[100];
	fscanf( file, "%s\n", dummy_string); // descarta a primeira linha

	while( !feof( file ) )
	{
		if( questions_counter >= MAX_QUESTIONS_LIST_SIZE )
			return FAILURE;

		question_t* current = &(questions_list[questions_counter]);

		int result = get_question( file, current);

		if( result == FAILURE ) return FAILURE;

		//print_full_question_info( current );

		questions_counter++;
	}

	fclose( file );

	questions_count = questions_counter;
}

int load_remarkable_characteristics_list()
{
	FILE *file;

	file = fopen(REMARKABLE_CHARACTERISTICS_LIST_FILENAME, "r");

	// IMPOSSIVEL LER LISTA DE PERGUNTAS
	if( file == NULL ) return FAILURE;

	int rmkble_characteristic_counter = 0;

	char dummy_string[100];
	fscanf( file, "%s\n", dummy_string); // descarta a primeira linha

	while( !feof( file ) )
	{
		if( rmkble_characteristic_counter >= MAX_REMARKABLE_CHARACTERISTICS_LIST_SIZE )
			return FAILURE;

		remarkable_characteristic_t* current = &(remarkable_characteristics_list[rmkble_characteristic_counter]);

		int result = get_remarkable_characteristic( file, current);

		if( result == FAILURE ) return FAILURE;

		rmkble_characteristic_counter++;

		if( rmkble_characteristic_counter != current->id ) return FAILURE;

		//print_full_rmkble_characteristics(current);
	}

	fclose( file );

	rmkble_characteristics_count = rmkble_characteristic_counter;
}