#include <stdio.h>
#include <string.h>

int main ()
{
   // int len;
   // const char str1[] = " keep-alive";
   // const char str2[] = " \t";

   // len = strspn(str1, str2);

   // printf("初始段匹配长度 %d\n", len );
   char* m_url = "/index.html HTTP/1.1";
   char* m_version = strpbrk(m_url, " \t");
   printf("%s\n", m_version);
   
   return(0);
}