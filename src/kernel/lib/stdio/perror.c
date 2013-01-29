#include <errno.h>
#include <stdio.h>
#include <string.h>

void perror(const char *s)
{
    fprintf(stderr, "%s: %s\n", s, strerror(errno));
}
