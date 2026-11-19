#include "s2html.h"
//single comment begin
int main(int argc , char *argv[]){
  if(argc < 2){
    printf("./a.out input.c <optionalfilename.html>outputfile \n"  );
  }

  FILE * src;
  FILE *dest;
  if( file_validation(argc,argv,&src,&dest) == FAILURE ){
    perror("ERROR ");
    return FAILURE;
  }else{
    printf("done validation\n");
  }

  /*                                                      
    
  multiline comment
  
  */
 
  write_header(dest);
  start_line(dest);
  
  uint len = 0 ;
  
  char *src_data = read_file_line(src,&len);
  
  if(src_data == NULL)
  {
    return FAILURE;
  }
              // printf("%s\n",src_data);
  // printf("send data\n");
  source_to_html(dest,len,src_data);
  free(src_data);



  // printf("size file : %lu\nreaded data : %u\n",fsize,len);
  // printf("%s",src_data);



  
  fprintf(dest,"</div>\n</body>\n</html>\n");
  fclose(src);
  fclose(dest);
  return 0;
}