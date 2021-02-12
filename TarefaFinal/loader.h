#ifndef FINAL_TASK_LOADER_H
#define FINAL_TASK_LOADER_H

#include "helper.h"
#include "custom_types.h"

#ifdef FINAL_TASK_LOADER_C
	question_t questions_list[MAX_QUESTIONS_LIST_SIZE];
	character_info_t characters_list[MAX_CHARACTERES_LIST_SIZE];
	remarkable_characteristic_t remarkable_characteristics_list[MAX_REMARKABLE_CHARACTERISTICS_LIST_SIZE];

	int questions_count = 0;
	int rmkble_characteristics_count = 0;
	int characters_count = 0;
#else
	extern question_t questions_list[MAX_QUESTIONS_LIST_SIZE];
	extern character_info_t characters_list[MAX_CHARACTERES_LIST_SIZE];
	extern remarkable_characteristic_t remarkable_characteristics_list[MAX_REMARKABLE_CHARACTERISTICS_LIST_SIZE];

	extern int questions_count;
	extern int rmkble_characteristics_count;
	extern int characters_count;
#endif



int load_info();

int load_characters_info();
int load_questions_list();
int load_remarkable_characteristics_list();

#endif //FINAL_TASK_LOADER_H