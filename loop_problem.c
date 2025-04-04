#include<stdio.h>
int main()
{
 int  sum = 0,n;
 int i=1;
   printf("Enter number:");
    scanf("%d",&n);
//   while(i<=n){
//     sum += i;
//         ++i;
// for (i = 1; i <= n; ++i)
// {
//      sum += i;
// }
// //   }
 
  do{
    sum += i;
        i++;

  }  

          while(i<=n);



          printf("Sum = %d", sum);
    
return 0;
} 

