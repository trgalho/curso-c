#ifndef FINAL_TASK_GAME_WORKER_H
#define FINAL_TASK_GAME_WORKER_H

#include "custom_types.h"

int load_info();

void initialize_all();

void configure_response_confirmation();

void initialize_possible_characters_list();
void initialize_available_questions_list();

void remove_invalid_characters( question_t* question, int is_ultimate_question, int match_type );
void remove_invalid_questions( int question_type, int question_subtype );

int has_available_questions();

int know_which_character_is();

question_t* pick_a_question();

int get_user_answer( question_t* question );

void process_user_answer( question_t*, int user_answer);

void do_the_ultimate_question();

void ask_user_character_confirmation();

void show_user_won_message();

#endif	//FINAL_TASK_GAME_WORKER_H