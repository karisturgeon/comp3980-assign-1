#include "../include/lower_filter.h"
#include "../include/null_filter.h"
#include "../include/parse_args.h"
#include "../include/process_file.h"
#include "../include/upper_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const char *inputFile  = NULL;
    const char *outputFile = NULL;
    const char *filter     = NULL;
    void (*filter_func)(char *);

    if(parse_args(argc, argv, &inputFile, &outputFile, &filter, &filter_func) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    process_file(inputFile, outputFile, filter_func);

    return EXIT_SUCCESS;
}
