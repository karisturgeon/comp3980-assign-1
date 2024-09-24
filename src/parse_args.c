
#include "../include/parse_args.h"
#include "../include/lower_filter.h"
#include "../include/null_filter.h"
#include "../include/upper_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int parse_args(int argc, char *argv[], const char **inputFile, const char **outputFile, const char **filter, void (**filter_func)(char *))
{
    int opt;
    if(argc == 1)
    {
        usage(argv[0], EXIT_FAILURE, "No options provided.");
    }

    while((opt = getopt(argc, argv, ":i:o:f:h")) != -1)
    {
        switch(opt)
        {
            case 'i':
                *inputFile = optarg;    // Option '-i' expects a file name as an argument
                //                printf("Input file: %s\n", inputFile);
                break;
            case 'o':
                *outputFile = optarg;    // Option '-o' expects a file name as an argument
                //                printf("Output file: %s\n", outputFile);
                break;
            case 'f':
                *filter = optarg;
                //                printf("Filter: %s\n", filter);
                break;
            case 'h':
                usage(argv[0], EXIT_SUCCESS, NULL);
            case ':':    // Handle missing argument case (for options -i, -o, -f)
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                return EXIT_FAILURE;
            case '?':
                if(optopt == 'i' || optopt == 'o' || optopt == 'f')
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
    if(strcmp(*inputFile, *outputFile) == 0)
    {
        fprintf(stderr, "Error: Input file and output file cannot be the same.\n");
        return EXIT_FAILURE;
    }
    handle_arguments(argv[0], *inputFile, *outputFile, *filter);

    if(strcmp(*filter, "upper") == 0)
    {
        *filter_func = upper_filter;
    }
    else if(strcmp(*filter, "lower") == 0)
    {
        *filter_func = lower_filter;
    }
    else if(strcmp(*filter, "null") == 0)
    {
        *filter_func = null_filter_wrapper;
    }
    else
    {
        fprintf(stderr, "Unknown filter: %s. Use 'upper', 'lower', or 'null'.\n", *filter);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void handle_arguments(const char *binary_name, const char *inputFile, const char *outputFile, const char *filter)
{
    // Check if any required argument is missing
    if(inputFile == NULL)
    {
        usage(binary_name, EXIT_FAILURE, "Missing required argument: -i inputfile.");
    }
    if(outputFile == NULL)
    {
        usage(binary_name, EXIT_FAILURE, "Missing required argument: -o outputfile.");
    }
    if(filter == NULL)
    {
        usage(binary_name, EXIT_FAILURE, "Missing required argument: -f filter.");
    }
}

_Noreturn void usage(const char *program_name, int exit_code, const char *message)
{
    if(message)
    {
        fprintf(stderr, "%s\n", message);
    }

    // Print the usage message
    fprintf(stderr, "Usage: %s -i inputfile -o outputfile -f filter\n", program_name);
    fputs("Options:\n", stderr);
    fputs("  -h          Display this help message\n", stderr);
    fputs("  -i <file>   Input file (required)\n", stderr);
    fputs("  -o <file>   Output file (required)\n", stderr);
    fputs("  -f <filter> Filter type (required: 'upper', 'lower', 'null')\n", stderr);
    exit(exit_code);
}
