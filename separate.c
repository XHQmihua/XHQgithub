#include<stdio.h>

 int main()
{
  int len=0;
  int len2=0;
  FILE* stream;
  FILE* stream1;
  FILE* stream2;
  char buf[50];
  char buf1[50];
  char buf2[50];
  char text[1024];

printf("input an file path to open:");

  scanf("%s",buf);
  stream=fopen(buf,"r+");

fseek(stream,0,SEEK_END);
   len=ftell(stream);
   printf("the file %s length is %d!\n",buf,len);
         len2 = len/2;
  
   printf("intput 2 file name: \n");
   scanf("%s%s",buf1,buf2);
   fseek(stream,0,SEEK_SET);
         stream1=fopen(buf1,"w+");
         stream2=fopen(buf2,"w+");
   fread(text,len2,1,stream);
   fwrite(text,len2,1,stream1);
   fread(text,len-len2,1,stream);
   fwrite(text,len-len2,1,stream2);
    
   fclose(stream);
   fclose(stream1);
   fclose(stream2);
  
  return 0;
 } 
