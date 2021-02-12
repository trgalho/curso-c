#ifndef FINAL_TASK_HELPER_H
#define FINAL_TASK_HELPER_H

#define SUCCESS 0
#define FAILURE 1

#define DONT_KNOW 0
#define YES       1
#define NO        2

#define NAME    0
#define GENDER  1
#define HAIR    2
#define CLOTHES 3
#define PET     4
#define REMARKABLE_CHARACTERISTIC 5

#define QUESTION_TYPE                 0
#define QUESTION_SUBTYPE              1
#define QUESTION_ANSWER_VALUE         2
#define QUESTION_ANSWER_POSSIBILITIES 3
#define QUESTION_TEXT                 4

#define REMARKABLE_CHARACTERISTIC_ID 0
#define REMARKABLE_CHARACTERISTIC_TEXT 1

#define MAX_CHARACTERES_LIST_SIZE 50
#define MAX_QUESTIONS_LIST_SIZE 25
#define MAX_REMARKABLE_CHARACTERISTICS_LIST_SIZE 25

#define CHARACTERS_LIST_FILENAME "characters_list.csv"
#define QUESTIONS_LIST_FILENAME "questions_list.csv"
#define REMARKABLE_CHARACTERISTICS_LIST_FILENAME "remarkable_characteristics_list.csv"
#define LOG_FILENAME "final_task.log"

#define START_GAME 1
#define SHOW_HELP 2
#define SHOW_CHARACTERS_LIST 3
#define QUIT_GAME 4

#endif //FINAL_TASK_HELPER_H