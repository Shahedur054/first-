#include<stdio.h>
int main()
{
int i,n, a[100], max,min;
// ask for the numbers user wants
printf("how many numbers: ");
scanf("%d",&n);

//input numbers for the user
for ( i = 0; i < n; i++)
{
    scanf("%d", & a[i]);
}
// for maximum value
max = a[0];
for ( i = 1; i < n; i++)
{
    if(max< a[i])
    max = a[i];
}
// for minimum value
min = a[0];
for ( i = 1; i < n; i++)
{
    if(min > a[i])
    min = a[i];
}
printf("maximum : %d\n", max );
printf("minimum : %d\n", min );

return 0;
}