#include <stdio.h>

void hello_ceng140(int programming_lan, char fav, float cgpa)
{
    
    printf("I have learned %d programming languages. My favourite one is %c, and my CGPA is %.2f.", programming_lan, fav, cgpa);

    
}

int main()
{
    int programming_lan;
    char fav;
    float cgpa;
    scanf("%d %c %f", &programming_lan, &fav, &cgpa);
    hello_ceng140(programming_lan, fav, cgpa);
    return 0;
}