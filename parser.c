#include "parser.h"
char *keywords[] =
{
    "int","char","float","double","void",
    "if","else","switch","case","default",
    "for","while","do","break","continue",
    "return",
    "struct","typedef","enum","union",
    "const","static","extern", "signed","unsigned",
    "short","long",
    "sizeof",
    NULL
};





Status parse_source(FILE *fp_source , FILE* fp_html)
{
    State state = s_idle;
    int ch,i=0;
    char buf[MAX_BUF];
    while((ch=fgetc(fp_source))!=EOF)
    {
        
        if(state == s_string)
        {
            if(ch == '"')
            {
                buf[i++]= '"';
                buf[i]='\0';
                if((write_word(fp_html,buf,STRING_COLOUR))== e_failure)
                {
                    printf("ERROR: String state, word writing\n");
                    return e_failure;
                }
                state = s_idle;
                i=0;
                continue;
            }
            buf[i++]= ch;
            continue;
            
        }
        if(state == s_preproccessor)
        {
            if(ch == ' ')
            {
                buf[i++]=ch;
                buf[i]='\0';
                if(write_word(fp_html,buf,PREPROCCESSOR_COLOUR)==e_failure)
                {
                    printf("ERROR: Pre-processor state, word writing\n");
                    return e_failure;
                }
                i=0;
                state = s_idle;
                continue;
            }
            
            else
            {
                buf[i++] = ch;
                continue;
            }
        }
        if(state == s_single_comment)
        {
            if(ch == '\n')
            {
                buf[i++]= ch;
                buf[i]='\0';
                i=0;
                state = s_idle;
                if((write_word(fp_html,buf,COMMENT_COLOUR))== e_failure)
                {
                    printf("ERROR: Single comment state, word writing\n");
                    return e_failure;
                }
                continue;
            }
            else
            {
                buf[i++]=ch;
                continue;
            }

        }

        
        if(state == s_multi_comment)
        {
            if(ch == '*')
            {
                buf[i++]=ch;
                char next = fgetc(fp_source);
                {
                    if(next == '/')
                    {
                        buf[i++] = next;
                        buf[i] = '\0';
                        i=0;
                        state = s_idle;
                        if((write_word(fp_html,buf,COMMENT_COLOUR))==e_failure)
                        {
                            printf("ERROR: Multi comment state, word writing\n");
                            return e_failure;
                        }
                        continue;
                    }
                    else
                    {
                        if(ungetc(next,fp_source)<0)
                        {
                            return e_failure;
                        }
                        continue;
                    }
                }
            

            }
            else
            {
                buf[i++] = ch;
                continue;
            }
            

        }
        
        if(ch == '/')
        {
            char next = fgetc(fp_source);
            if(next == '/' || next == '*')
            {
                if(state == s_word)
                {
                    buf[i]= '\0';
                    if((flush_word(fp_html,buf))== e_failure)
                    {
                        printf("ERROR: Comment handling, word flushing\n");
                        return e_failure;
                    }
                    state = s_idle;
                }
                i=0;
                buf[i++]= '/';
                if(next == '/')
                {
                    state = s_single_comment;
                    buf[i++]= next;
                }
                else
                {
                    buf[i++]= next;
                    state = s_multi_comment;
                }
                continue;
            }
            else
            {
                if(ungetc(next,fp_source)<0) //this will putback next to the input stream
                {
                    return e_failure;
                }
            }
        }
        if(ch == '#' && state == s_idle)
        {
            i=0;
            buf[i++]=ch;
            state = s_preproccessor;
            continue;

        }
        
        if(ch == '"')
        {
            if(state == s_word)
            {
                buf[i]= '\0';
                if((flush_word(fp_html,buf))== e_failure)
                {
                    printf("ERROR: String handling, word flushing\n");
                    return e_failure;
                }
            }
            state = s_string;
            i=0;
            buf[i++] = '"';
            continue;
        }
       
        if(state == s_word)
        {
            if((check_if_identifier(ch)) == e_failure)
            {
                buf[i]='\0';
                if((flush_word(fp_html,buf)) == e_failure)
                {
                    printf("ERROR : Word state, word flushing\n");
                    return e_failure;
                }
                if((flush_character(fp_html,ch)) == e_failure)
                {
                    printf("ERROR : Word state, character flushing\n");
                    return e_failure;
                }
                state = s_idle;
                i=0;
                continue;

            }
            buf[i++]=ch;
            continue;
        }
        if(state == s_character)
        {
            if(ch == '\'')
            {
                buf[i++]=ch;
                buf[i] = '\0';
                state = s_idle;
                i=0;
                if((write_word(fp_html,buf,CHARACTER_COLOUR)) == e_failure)
                {
                    printf("ERROR : Character state, word writing\n");
                    return e_failure;
                }
                continue;
            }
            buf[i++]= ch;
            continue;
        }

        if(state == s_number)
        {
            if(check_if_number(ch) == e_failure && ch != '.')
            {
                buf[i] = '\0';
                if((write_word(fp_html,buf,NUMBER_COLOUR)) == e_failure)
                {
                    printf("ERROR : number state, number writing\n");
                    return e_failure;
                }
                if(ungetc(ch,fp_source)<0)
                {
                    printf("ERROR : number state, ungetc\n");
                    return e_failure;
                }
                state = s_idle;
                i=0;
                continue;
                
            }
            buf[i++] = ch;
            continue;
        }
        if(ch == '\'')
        {
            state = s_character;
            i=0;
            buf[i++] = ch;
            continue;
        }

        if((check_if_number(ch)) == e_success)
        {
            state = s_number;
            i=0;
            buf[i++] = ch;
            continue;
            
        }

        if((check_if_word_start(ch)) == e_success)
        {
            state = s_word;
            i=0;
            buf[i++]= ch;
            continue;
        }

        /*Default character handling, ie if it is not handled by any one of the above*/
        if(flush_character(fp_html, ch) == e_failure)
        {
            printf("ERROR : Default character flushing\n");
            return e_failure;
        }
           
    }
    //end of file reached before newline
    if(state == s_word)
    {
        buf[i] = '\0';
        if(flush_word(fp_html, buf) == e_failure)
        {
            return e_failure;
        }
        
    }
    return e_success;
    
}

Status check_if_number(char ch)
{
    if(ch>= '0' && ch <= '9')
    {
        return e_success;
    }
    return e_failure;
}
Status check_if_word_start(char ch)
{
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z' || ch == '_'))
    {
        return e_success;
    }
    return e_failure;
    
}
Status check_if_identifier(char ch)
{
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
    {
        return e_success;       
    }
    return e_failure;
}


Status check_if_keyword(char * buf)
{
    int i=0;
    while(keywords[i]!=NULL)
    {
        if(strcmp(keywords[i],buf)==0)
        {
            return e_success;
        }
        ++i;
    }
    return e_failure;
}