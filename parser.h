#ifndef PARSER_H
#define PARSER_H

#include "main.h"


#define TEXT_COLOUR NULL
#define STRING_COLOUR "green"
#define CHARACTER_COLOUR "green"
#define KEYWORD_COLOUR "blue"
#define PREPROCCESSOR_COLOUR "purple"
#define COMMENT_COLOUR "grey"
#define NUMBER_COLOUR "orange"

#define MAX_BUF 500




typedef enum
{
    s_idle,
    s_word,
    s_preproccessor,
    s_character,
    s_string,
    s_single_comment,
    s_multi_comment, 
    s_number
}State;



typedef enum
{
    t_keyword
}Token;



State check_state(char ch,char *buf);
Status check_if_keyword(char * buf);
Status check_if_identifier(char ch);
Status check_if_word_start(char ch);
Status check_if_number(char ch);




Status write_word(FILE* fp_html, char* buf, char * colour);
Status flush_word(FILE *fp_html, char *buf);
Status flush_character(FILE* fp_html,char ch);


#endif