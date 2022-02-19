#ifndef GIF_DATA_H_
#define GIF_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

typedef struct
{
    const int width;
    const int height;

    const int channel_count;
    const int pixel_count;

    const size_t frame_size;
    const uint32_t frame_count;
    const int16_t frame_delay;

    int frame_index;
    uint8_t *buffer;
} gif_t;

uint8_t *gif_extract_frame(const gif_t gif);

gif_t gif_load_from_file(const char *file_path);

#endif // GIF_DATA_H_