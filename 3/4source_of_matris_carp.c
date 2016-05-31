#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv) {
  char text[] = "2345 56 234 576 54 2423423 56547 234324 4645 75 23 4523432 54 36 457 2 34234 56 658 3 46 67 34";
  int world_size=3;
  int textSize=(int)sizeof(text)/sizeof(char);
  int ort = textSize/world_size;
  int i=0;
	
  
  do{
      i++;
     }while(text[i] =! ' ' || i<ort);
  
  printf("%d\n",i);
  
  char subText[i];
  memcpy( subText, text, i );
  subText[i-1] = '\0';
  
  printf("%s\n",subText);

    return 0;
}