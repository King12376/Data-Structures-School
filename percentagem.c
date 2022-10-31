#include<stdio.h>

int main(){

int testmark,totalmark;
float percentage;

printf("Enter student test mark: ");
scanf("%d",&testmark);

printf("Enter student total mark: ");
scanf("%d",&totalmark);

 percentage = (float)testmark /totalmark * 100.0;

   printf("Percentage = %.2f%%", percentage);

  return 0;
}