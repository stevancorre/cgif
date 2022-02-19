#include "gif.h"

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

    gif_t gif = gif_load_from_file(input_file_path);
    printf("w: %d\n", gif.width);
    printf("h: %d\n", gif.height);

    free(gif.buffer);

    return 0;
}