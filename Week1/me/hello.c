#include <cs50.h>
#include <stdio.h>

// main function
int main()
{

    // prompt user for input
    string name = get_string("What's your name?\t");

    // print message for user
    printf("hello, %s\n", name);

    return 0;
}
