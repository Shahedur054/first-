#include<stdio.h>

int main()
{ int len = 0;
char s1[100];
printf("Enter your Full name: ");
fgets(s1, sizeof(s1),stdin);
printf("your Full name: %s",s1);

for(int i = 0; s1[i] != '\0';i++)   
{
    printf("%c\n",s1[i]);
}

for(int i = 0; s1[i] != '\0';i++)   
{
  len++;  
}
printf("Length = %d\n",len);
return 0;
}