#include "main.h"
int add_line_number = 0;
int line_number = 1;
int pending_line_number = 1;


int main(int argc, char* argv[])
{

    if(argc<3)
    {
        printf("ERROR : INSUFFICIENT ARGUMENTS\n");
        return 0;
    }
    char *last_dot=NULL;

    last_dot=strrchr(argv[1],'.');

    if(last_dot == NULL)
    {
        printf("ERROR : INVALID SOURCE FILE\n");
        return 0;
    }
    if((strcmp(last_dot,".c"))!=0)
    {
        printf("ERROR : INVALID SOURCE FILE\n");
        return 0;

    }
    FILE *fp_source;
    fp_source = fopen(argv[1],"r");
    if(fp_source == NULL)
    {
        printf("ERROR : FAILED OPENING SOURCE FILE\n");
        return 0;
    }


    last_dot = NULL;
    last_dot= strrchr(argv[2],'.');
    if(last_dot == NULL)
    {
        printf("ERROR : INVALID HTML FILE\n");
        return 0;   
    }
    if((strcmp(last_dot,".html"))!=0)
    {
        printf("ERROR : INVALID HTML FILE\n");
        return 0;
    }
    FILE* fp_html;
    fp_html = fopen(argv[2],"w");
    if(fp_html == NULL)
    {
        printf("ERROR: FAILED OPENING HTML FILE\n");
        return 0;
    }
    if(argc == 4 && (strcmp(argv[3],"-n" ) == 0))
    {
        add_line_number = 1;
    }

    if(format_html(fp_source,fp_html)==e_success)
    {
        printf("HTML generated successfully\n");
        return 1;
    }
    else
    {
        printf("ERROR : FAILED GENERATING HTML\n");
        return 0;
    }




}