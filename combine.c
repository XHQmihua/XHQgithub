#include<stdio.h>

 int main()
 {
  int len=0;
  int len2=0;
  FILE* stream;
  FILE* stream1;
 
  char buf[50];
  char buf1[50];
  
  char text[1];

printf("input an file path to open:");

  scanf("%s",buf);
  stream=fopen(buf,"r+");

fseek(stream,0,SEEK_END);

printf("intput another file name: \n");
   scanf("%s",buf1);
   
         stream1=fopen(buf1,"r+");
   fseek(stream1,0,SEEK_END);
         len=ftell(stream1);
   fseek(stream1,0,SEEK_SET);

while(fread(text,1,1,stream1)){
        fwrite(text,1,1,stream);
  }
   
   fclose(stream);
   fclose(stream1);
    remove(buf1);//remove the another file

return 0;
 }
