#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_GIF
#include "stb_image.h"

static char* program_name;

static void print_usage_and_exit(int code)
{
    fprintf(stderr, "Usage: %s <input gif>\n", program_name);
    exit(code);
}

int main(int argc, char **argv)
{
    program_name = argv[0];
    (void)argc;
    
    const char *input_file_path = argv[1];
    if (input_file_path == NULL)
    {
        fprintf(stderr, "ERROR: no input file provided\n");
        print_usage_and_exit(EXIT_FAILURE);
    }

    int width, height, comp;
    stbi_uc *data = stbi_load(input_file_path, &width, &height, &comp, 0);
    if (data == NULL)
    {
        char* err = errno == 0 ? "Input file is not a gif" : strerror(errno);
        fprintf(stderr, "ERROR: can't open %s: %s\n", input_file_path, err);
        print_usage_and_exit(EXIT_FAILURE);
    }

    STBI_FREE(data);

    return 0;
}