#include<stdio.h>
void hello()
{
    printf("hello world!\n");
 }
void bye(){
    printf ("Good bye!\n");
}

int main()
{
    printf ("Enter your choice H for Hello and G for Good Bye: \n");
 char h;
  scanf("%c",& h);
  if( h == 'H'|| h == 'h')
{
    hello();
}
 else
 bye();
 
return 0;
}

