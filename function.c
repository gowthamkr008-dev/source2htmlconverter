#include "s2html.h"

int line = 0;

int file_validation(int argc,char *argv[],FILE **src,FILE **dest)
{
  *src = fopen(argv[1],"r");
  
  if(*src == NULL)
  {
    printf("return src\n");
    return FAILURE;
  }
  
  if(argc == 2)
  {
    *dest = fopen("output.html","w");
  }else{
    
    char *ext = strrchr(argv[2],'.');
    
    if(strcmp(ext,".html") == 0)
    {
      
      *dest = fopen(argv[2],"w");
    }else{
      
      char *src_d = malloc( (strlen(ext) + 6) * sizeof(char)  );
      
      if(src_d == NULL){
        printf("allocation failure\n");
        return FAILURE;
      }
      
      strcpy(src_d,argv[2]);
      strcat(src_d,".html");
      
      *dest = fopen(src_d,"w");      
      
      free(src_d);
    }
  }
  printf("\n"); 
  return SUCCESS;
}

char * read_file_line(FILE *src, uint *len ){
  fseek(src,0,SEEK_END);
  size_t f_len = ftell(src);
  if(f_len < 1){
    printf("file empty\n");
    return NULL;
  } 

  rewind(src);
  char *data = malloc( (f_len+1) * sizeof(char) );
  if(data == NULL){
    return NULL;
  }

   *len = fread(data,1,f_len,src);

   data[f_len]='\0';
   
   return data;
   


  // *len = 0;
  // size_t oldpos = ftell(src);
  // int ch;
  // int c_len = 0;
  // while ((ch = fgetc(src)) != EOF && ch != '\n'){
  //   c_len++;
  // }
  // *len = c_len;
  // // printf("%u\n",*len);
  // fseek(src,oldpos,SEEK_SET);
  // char *data;
  // data = malloc( (*len + 1) * sizeof(char) );
  // if(data == NULL){
  //   printf("allocation failure\n");
  //   return NULL;
  // }
  // fread(data,1,*len,src);
  // data[*len] ='\0';
  // fgetc(src);
  return data;
}


void write_header(FILE * dest_fp){


	fprintf(dest_fp, "<!DOCTYPE html>\n");
	fprintf(dest_fp, "<html lang=\"en-US\">\n");
	fprintf(dest_fp, "<head>\n");
	fprintf(dest_fp, "<title>%s</title>\n", "sode2html");
	fprintf(dest_fp, "<meta charset=\"UTF-8\">\n");
	fprintf(dest_fp, "</head>\n");
	fprintf(dest_fp, "<body style=\"background-color:lightgrey;\">\n");
	fprintf(dest_fp, "<pre>\n");
}


void start_line(FILE *dest)
{
  fprintf(dest, "<div class=\"l\"><span class=\"n\">%d</span>", ++line);
}

void end_line(FILE *dest){
  fprintf(dest,"</div>");
}

static void entities(FILE *dest,char c){
  switch (c)
  {
  case '<':
  fprintf(dest,"&lt;");
  break;
  case '>':
  fprintf(dest,"&gt;");
    break;

  case '&':
  fprintf(dest,"&amp;");
    break;

  case '"':
  fprintf(dest,"&quot;");
    break;

   case '\'':
   fprintf(dest,"&apos;");
    break;
  
  default:
  fprintf(dest,"%c",c);
    break;
  }
}


void insert(FILE *dest,char *data,int s_len,int e_len,const char * class){
  if(class != NULL){
  fprintf(dest,"<span class =\"%s\">",class);
  }
  for(int i =s_len;i<e_len;i++){
    if(strchr("><&\"'",data[i])){
      entities(dest,data[i]);
    }else{
    fputc(data[i],dest);
    }
  }

}
