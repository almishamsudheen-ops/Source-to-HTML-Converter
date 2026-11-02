#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 100
#define SWAP(type,a,b) \
type temp = a;         \
a = b;                 \
b = temp

/* Multi-line comment
   containing symbols:
   < > & " '
*/

struct Student
{
    char name[50];
    int age;
};

int add(int a, int b)
{
    return a + b;
}

int main1()
{
    // Single line comment
    char ch = 'A';
    int count = 10;
    float average = 12.5;
    double value = 123.456;

    char grade = 'A';

    const char *message =
        "Hello <World> & Everyone!";

    if(count > 0)
    {
        printf("%s\n", message);
    }
    else
    {
        printf("Count is zero\n");
    }

    for(int i = 0; i < count; i++)
    {
        printf("i = %d\n", i);
    }

    while(count > 0)
    {
        count--;
    }

    do
    {
        count++;
    }
    while(count < 5);

    switch(grade)
    {
        case 'A':
            printf("Excellent\n");
            break;

        case 'B':
            printf("Good\n");
            break;

        default:
            printf("Unknown\n");
            break;
    }

    return 0;
}