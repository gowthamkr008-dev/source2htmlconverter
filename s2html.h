#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include <stdlib.h>


#define SUCCESS 0
#define FAILURE -1



typedef unsigned int uint;

int file_validation(int argc,char *argv[],FILE **src,FILE **dest);
char * read_file_line(FILE *src, uint *len);
void write_header(FILE * dest);
void start_line(FILE * dest);
void end_line(FILE * dest);
void source_to_html(FILE * dest,uint len,char *data);
void insert(FILE *dest,char *data,int s_len,int e_len,const char * class);
