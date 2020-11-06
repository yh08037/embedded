#include <stdio.h>
#include <unistd.h>

int main() 
{
    for (;;)
    {
        printf("hello\n");
        sleep(1);
    }

    return 0;
}
