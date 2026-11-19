#include "s2html.h"
static void  print_data(char * data,int s_len,int e_len){
  for(int i = s_len;i < e_len;i++){
    printf("%c", data[i]);
  }
  printf("\n");
}



void source_to_html(FILE * dest,uint len,char *data){
  int i = 0,j,line_start = 0;
  while(data[i] != '\0')
  {
    // start_line(dest);

    /*pre processor directive */
    if(data[i] == '#'){
      start_line(dest);
      line_start = 1;
       j = i + 1;
      while(j < len &&  (data[j] != ' ' && data[j] != '<' && data[j] != '"' ) ) j++;
      // printf("%d %d ",i,j);
      insert(dest,data,i,j,"pp");
      
      i = j;
      while (data[j]== ' ' ) j++;

      /*header files */
      if(data[j] == '<' || data[j] == '\"'){
        j++;
        while(j < len && (isalnum(data[j]) != 0 || data[j] == '.' ) && (data[j] !='>' || data[j] =='\"' ) ) j++;
        insert(dest,data,i,j+1,"st");
        
      }
      i = j+1;
       end_line(dest);  
      continue;
    }

    //single line comment
    if(data[i] =='/' && data[i+1] == '/' ){
        start_line(dest);
      j = i;
      while(j < len && data[j] != '\n' ) j++;
      // print_data(data,i,j);
     
      insert(dest,data,i,j,"com");
     
      i = j;
     end_line(dest);
      continue;
    }


    // multiline comment
    /*
    
    */
    if(data[i]=='/' && data[i+1] == '*'){
        if(line_start == 0){
        line_start = 1;
        start_line(dest);
      }
      j = i;
      j += 2;
      while(j < len && (data[j] != '*' && data[j+1] != '/')){
        j++;
        if(data[j] == '\n'){
          insert(dest,data,i,j+=1,"com");
          i =j;
        } 
      }
          insert(dest,data,i,j+2,"com");
         
     
       end_line(dest);
       i = j+2;    
      continue;
       

    }


    //string literal

    if(data[i] == '\"' || data[i] == '\''){
      j =i+1;
      while(j <len && (data[j] != '"' && data[j] != '\'') )j++;
      //  print_data(data,i,j);
    
      insert(dest,data,i,j+=1,"str");
      i = j;     
      continue;
    }

    if(data[i]== ' '){
      j =i;
      while( (isspace(data[j]) != 0) && data[j] != '\n')j++;
      insert(dest,data,i,j+=1,NULL);
      i = j;
      continue;
    }
    
    i++;
  }
}



/*


    // for sapces
    if(data[i] == ' '){
      j = i;
      while(j < len && (data[i] !=' '))j++;
      start_line(dest);
      insert(dest,data,i,j,NULL);
      end_line(dest);
      i = j;
    }

*/