//
// Created by kari on 9/23/24.
//

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H
int parse_args(int argc, char *argv[], const char **inputFile, const char **outputFile, const char **filter, void (**filter_func)(char *));
#endif    // PARSE_ARGS_H
