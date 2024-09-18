#include "../include/lower_filter.h"
#include "../include/null_filter.h"
#include "../include/process_file.h"
#include "../include/upper_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int         opt;
    const char *inputFile  = NULL;
    const char *outputFile = NULL;
    const char *filter     = NULL;
    void (*filter_func)(char *);

    if(argc == 1)
    {
        fprintf(stderr, "No options provided. Usage: %s -i inputfile -o outputfile -f filter\n", argv[0]);
        return EXIT_FAILURE;
    }

    while((opt = getopt(argc, argv, "i:o:f:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                inputFile = optarg;    // Option '-i' expects a file name as an argument
                                       //                printf("Input file: %s\n", inputFile);
                break;
            case 'o':
                outputFile = optarg;    // Option '-o' expects a file name as an argument
                                        //                printf("Output file: %s\n", outputFile);
                break;
            case 'f':
                filter = optarg;
                //                printf("Filter: %s\n", filter);
                break;
            case '?':
                if(optopt == 'i' || optopt == 'o')
                {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                }
                else
                {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }
    if(inputFile == NULL || outputFile == NULL || filter == NULL)
    {
        fprintf(stderr, "Usage: %s -i inputfile -o outputfile -f filter\n", argv[0]);
        return EXIT_FAILURE;
    }
    if(strcmp(filter, "upper") == 0)
    {
        filter_func = upper_filter;
    }
    else if(strcmp(filter, "lower") == 0)
    {
        filter_func = lower_filter;
    }
    else if(strcmp(filter, "null") == 0)
    {
        filter_func = null_filter_wrapper;
    }
    else
    {
        fprintf(stderr, "Unknown filter: %s. Use 'upper', 'lower', or 'null'.\n", filter);
        return EXIT_FAILURE;
    }
    process_file(inputFile, outputFile, filter_func);
    return EXIT_SUCCESS;
}
