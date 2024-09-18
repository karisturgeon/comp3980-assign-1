#include "../include/upper_filter.h"
#include <ctype.h>
#include <stdio.h>

void upper_filter(char *c)
{
    *c = (char)toupper(*c);
}
