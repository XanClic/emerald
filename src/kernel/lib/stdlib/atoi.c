#include <stdlib.h>


int atoi(const char *string)
{
    return (int)strtol(string, NULL, 10);
}
