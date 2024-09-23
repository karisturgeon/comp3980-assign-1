
#include "../include/process_file.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void process_file(const char *i, const char *o, void (*filter)(char *))
{
    int     input_fd;
    int     output_fd;
    char    ch;
    ssize_t bytes_read;

    input_fd = open(i, O_RDONLY | O_CLOEXEC);
    if(input_fd == -1)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    output_fd = open(o, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR);

    if(output_fd == -1)
    {
        perror("Error opening/creating output file");
        exit(EXIT_FAILURE);
    }

    while((bytes_read = read(input_fd, &ch, sizeof(char))) > 0)
    {
        filter(&ch);
        if(write(output_fd, &ch, sizeof(char)) == -1)
        {
            perror("Error writing to output file");
            close(input_fd);
            close(output_fd);
            exit(EXIT_FAILURE);
        }
    }
    if(bytes_read == -1)
    {
        perror("Error reading input file");
    }

    if(close(input_fd) == -1)
    {
        perror("Error closing input file");
    }
    if(close(output_fd) == -1)
    {
        perror("Error closing output file");
    }
}
