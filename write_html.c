#include "main.h"
#include "parser.h"

Status write_to_html(FILE* fp_html, char* str)
{
    int idx = 0;
    while(str[idx] != '\0')
    {
        if(add_line_number == 1 && pending_line_number == 1)
        {
            if((print_line_number(fp_html,&line_number)) == e_failure)
            {
                return e_failure;
            }
            pending_line_number = 0;
        }

        if(fputc(str[idx],fp_html) < 0)
        {
            return e_failure;
        }

        if(str[idx] == '\n')
        {
            pending_line_number = 1;
        }
        idx++;
    }
    return e_success;
}
Status write_html_header(FILE * fp_html)
{
    if(fprintf(fp_html,"<html>\n")<0)
    {
        return e_failure;
    }
    if(fprintf(fp_html, "<body>\n")<0)
    {
        return e_failure;
    }
    if(fprintf(fp_html,"<pre>\n")<0)
    {
        return e_failure;
    }

    return e_success;

}

Status copy_source(FILE *fp_source, FILE* fp_html)
{
    if(parse_source(fp_source, fp_html)==e_failure)
    {
        printf("ERROR : PARSER FAILED\n");
        return e_failure;
    }
    return e_success;
}


Status write_html_footer(FILE* fp_html)
{
    if(fprintf(fp_html,"</pre>")<0)
    {
        return e_failure;
    }
    if(fprintf(fp_html,"</body>\n")<0)
    {
        return e_failure;
    }
    if(fprintf(fp_html,"</html>")<0)
    {
        return e_failure;
    }
    return e_success;
}


Status format_html(FILE* fp_source, FILE *fp_html)
{
    if((write_html_header(fp_html))==e_failure)
    {
        printf("ERROR : FAILED WRITING HEADER TO HTML\n");
        return e_failure;
    }
    if((copy_source(fp_source,fp_html))==e_failure)
    {
        printf("ERROR : FAILED COPYING SOURCE TO HTML\n");
        return e_failure;
    }
    if((write_html_footer(fp_html))==e_failure)
    {
        printf("ERROR : FAILED WRITING FOOTER TO HTML\n");
        return e_failure;
    }

    return e_success;
}


Status write_word(FILE* fp_html, char* buf, char *colour)
{
    if(colour == TEXT_COLOUR)
    {
        if((write_to_html(fp_html,buf)) == e_failure)
        {
            return e_failure;
        }
        return e_success;
    }

    //if there is a colour
    if(fprintf(fp_html,"<span style=\"color:")<0)
    {
        return e_failure;
    }
    
    if(fprintf(fp_html,"%s\">",colour)<0)
    {
        return e_failure;
    }
    if((write_to_html(fp_html,buf)) == e_failure)   /* <-- changed from fprintf */
    {
        return e_failure;
    }
    if(fprintf(fp_html,"</span>")<0)
    {
        return e_failure;
    }
    return e_success;

}
    
   

Status print_line_number(FILE* fp_html, int* line_count)
{
    if(fprintf(fp_html,"%4d\t" , *line_count)<0)
    {
        return e_failure;
    }
    *line_count += 1 ;
    return e_success;
}

Status flush_word(FILE *fp_html, char *buf)
{
    
    if((check_if_keyword(buf)) == e_success)
    {
        if((write_word(fp_html,buf,KEYWORD_COLOUR))== e_failure)
        {
            return e_failure;
        }
    }
    else
    {
        if((write_word(fp_html,buf,TEXT_COLOUR))== e_failure)
        {
            return e_failure;
        }
    }
    return e_success;
}

Status flush_character(FILE* fp_html,char ch)
{
    if(ch == '>')
    {
        if((write_word(fp_html,"&gt;",TEXT_COLOUR)) == e_failure)
        {
            printf("ERROR : Character flushing, >\n");
            return e_failure;
        }
        
    }
    else if(ch == '<')
    {
        if((write_word(fp_html,"&lt;",TEXT_COLOUR)) == e_failure)
        {
            printf("ERROR : Character flushing, <\n");
            return e_failure;
        }
    }
    else if(ch == '&')
    {
        if((write_word(fp_html,"&amp;",TEXT_COLOUR)) == e_failure)
        {
            printf("ERROR : Character flushing, &\n");
            return e_failure;
        }
        
    }
    else
    {
        char temp[2];
        temp[0] = ch;
        temp[1] = '\0';
        if((write_to_html(fp_html,temp)) == e_failure)
        {
            printf("ERROR : Character flushing, fputc \n");
            return e_failure;
        }
    }
    return e_success;
}