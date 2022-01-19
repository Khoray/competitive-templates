#include<stdio.h>
#include<stdlib.h>
int main(void){
int p;
int i;
printf("%p\n",&p);
i=(int)&p;
printf("%d",i);
system(“pause”);
return 0;
}