#ifndef FINAL_TASK_CUSTOM_TYPES_H
#define FINAL_TASK_CUSTOM_TYPES_H

typedef int question_id_t;

typedef int user_answer_t;

typedef struct question
{
	int type;
	int subtype;
	int answer_value;
	int answer_possibilities;
	char text[50];
} question_t;

typedef struct remarkable_characteristic
{
	int id;
	char text[50];
} remarkable_characteristic_t;

typedef struct character_info {
	char name[32];
	int gender;
	int hair;
	int clothes;
	int pet;
	int remarkable_characteristic;
} character_info_t;

typedef struct character_info_node {
	character_info_t * data;
	struct character_info_node *next;
} character_info_node_t;

typedef struct question_node
{
	question_t *data;
	struct question_node *next;	
} question_node_t;

typedef struct questions_linked_list {
	question_node_t *head;
} questions_linked_list_t;

typedef struct character_info_linked_list {
	character_info_node_t *head;
} character_info_linked_list_t;


#endif //FINAL_TASK_CUSTOM_TYPES_H