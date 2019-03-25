#include "main.h"

int main(int argc, char *argv[])
{
    LexAnalyzer lex_file;
    uint f_size;

    /* Error handling */
    if(argc != 2)
    {
	fprintf(stderr, "Usage: ./lexicalAnalyzer <.c file>\n");
	return 1;
    }

    /* File validation */
    if(argc == 2)
    {
	lex_file.src_fname = argv[1];

	if(file_validation(&lex_file) == e_failure)
	    return 1;
	printf("File validation success\n");
    }

    /* Get file size */
    f_size = file_size(lex_file.fd_lex);

    //printf("File size: %d\n", f_size);

    /* Check header files */
    if(is_header(lex_file.fd_lex) == e_success)
    {
	//printf("Header found\n");
    }

    /* Tokenizer */
    if(tokenizer(lex_file.fd_lex) == e_success)
    {
	printf("End of file\n");
    }

}
