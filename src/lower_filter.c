//
// Created by kari on 9/15/24.
//
#include "../include/lower_filter.h"
#include <ctype.h>
#include <stdio.h>

void lower_filter(char *c)
{
    *c = (char)tolower(*c);
}
