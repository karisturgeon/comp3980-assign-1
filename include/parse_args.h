
#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H
int            parse_args(int argc, char *argv[], const char **inputFile, const char **outputFile, const char **filter, void (**filter_func)(char *));
void           handle_arguments(const char *binary_name, const char *inputFile, const char *outputFile, const char *filter);
_Noreturn void usage(const char *program_name, int exit_code, const char *message);
#endif    // PARSE_ARGS_H
