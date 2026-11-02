#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <string.h>


typedef enum
{
    e_failure,
    e_success
}Status;


Status write_html_header(FILE * fp_html);
Status copy_source(FILE *fp_source, FILE* fp_html);
Status write_html_footer(FILE* fp_html);
Status format_html(FILE* fp_source, FILE *fp_html);
Status write_keyword(FILE* fp_html, char* buf);
Status print_line_number(FILE* fp_html, int* line_count);
Status parse_source(FILE *fp_source , FILE* fp_html);

//globals controlling line number printing
extern int add_line_number;
extern int line_number;
extern int pending_line_number;

#endif