#include "main.h"

int j = 0;

status file_validation(LexAnalyzer *lex_file)
{
    printf("INFO: Opening file\n");

    lex_file->fd_lex = fopen(lex_file->src_fname, "r");
    if(!lex_file->fd_lex)
    {
	perror("Invalid File");
	return e_failure;
    }
    return e_success;
}

uint file_size(FILE *fptr)
{
    uint f_size;
    fseek(fptr, 0L, SEEK_END);
    f_size = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);

    return f_size;
}

status is_header(FILE *fptr)
{
    int i = 0;
    char ch;
    char header[20];


    while((ch = fgetc(fptr)) != EOF)
    {
	if(ch == '#')
	{
	    header[i] = ch;
	    if((ch = fgetc(fptr)) == 'i')
	    {
		header[++i] = ch;
		while(ch != '>')
		{
		    ch = fgetc(fptr);
		    header[++i] = ch;
		}
		header[++i] = '\0';
		i = 0;
		printf("Header		: %s\n", header);
	    }
	}
    }
    return e_success;
}

status tokenizer(FILE *fptr)
{
    int i;
    char ch, str[35], op;
    char oper[] = "+-*/!`~%^&=.<>?";
    char sep[] = "\n ,;(){}[]#\"<>";
    char sep2[] = ";(){}";
    int op_size = strlen(oper);
    int sp_size = strlen(sep);
    int sep2_size = strlen(sep2);
    //printf("opr_size  %d\n", op_size);

    fseek(fptr, 0L, SEEK_SET);

    while((ch = fgetc(fptr)) != EOF)
    {
	for(i = 0; i < op_size; i++)
	{
	    if(ch == oper[i])
	    {
		//op = ch;

		if(ch == '/')
		{
		    if(fgetc(fptr) == '*')
			while(fgetc(fptr) != '/');
		    else if(ch == '/')
			while(fgetc(fptr) != '\n');
		    ch = fgetc(fptr);
		}
		else
		{
		    printf("Operator	: %c\n", ch);
		    str[j] = '\0';
		    keyword(str);
		}
	    }
	}
	for(i = 0; i < sp_size; i++)
	{
	    if(j == -1)
		break;
	    if(ch == sep[i])
	    {
		op = ch;
		if(ch == '#')
		{
		    if((ch = fgetc(fptr)) == 'i')
		    {
			while(ch != '>')
			{
			    //printf("%c", ch);
			    ch = fgetc(fptr);
			}
		    }
		    else
		    {
			printf("Header		: %c\n", ch);
		    }
		    j = -1;
		    break;
		}
		else if(ch == '"')						//change 1
		{
		    printf("Literal		: %c", ch);
		    do
		    {
			ch = fgetc(fptr);
			printf("%c", ch);
		    } while(ch != '"');
		    printf("\n");
		    j = -1;
		    break;
		}
		/*else
		{
		    for(int l = 0; l < sep2_size; l++)
		    {
			if(op == sep2[l])
			    printf("Operator	: %c\n", op);
		    }
		}*/
		str[j] = '\0';
		keyword(str);
		    for(int l = 0; l < sep2_size; l++)
		    {
			if(op == sep2[l])
			    printf("Operator	: %c\n", op);
		    }
	    }
	}

	if(j != -1)
	{
	    str[j] = ch;
	    j++;
	}
	else
	    j = 0;
    }
}

void keyword(char *str)
{
    int k, flag = 0;
    char key[32][10] = {"auto", "break", "case", "char", "const", "continue", 
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long", "return",
	"register", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned",
	"void", "volatile", "while"};

    for(k = 0; k < 32; k++)
    {
	if(strcmp(key[k],str) == 0)
	{
	    printf("Keyword		: %s\n", str);
	    flag = 1;
	    break;
	}
    }
    if(!flag)
    {
	if(isdigit(str[0]))
	{
	    printf("Literal		: %s\n", str);
	}
	else
	{
	    if(str[0] != '\0')
	    {
		printf("Identifier	: %s\n", str);
	    }
	}
    }
    j = -1;
}












