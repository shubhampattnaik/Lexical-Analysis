#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef unsigned int uint;

typedef enum
{
    e_success,
    e_failure
} status;

typedef struct _LexAnalyzer
{
    char *src_fname;
    FILE *fd_lex;
} LexAnalyzer;

uint file_size(FILE *fptr);
status file_validation(LexAnalyzer *lex_file);
status is_header(FILE *fptr);
status tokenizer(FILE *fptr);
void keyword(char *str);

#endif
