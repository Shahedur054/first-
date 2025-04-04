#include<stdio.h>
int main()
{
int a[100], sum = 0 , i , n;
int product = 1;
 printf(" how many numbers : ");
   scanf("%d",&n);
 printf("enter your intiger : ");
  for(i=0; i<n; i++)
{
  scanf("%d",&a[i]);

}
for(i=0;i<n;i++)
{
    sum += a[i];
}
printf("the sum is: %d\n", sum );
printf("the average is: %.2f\n", (float)sum/n);

for(i=0;i<n;i++)
{
     product *= a[i];
}

printf("the product is: %d\n", product );
return 0;
}
