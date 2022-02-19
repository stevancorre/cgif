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
    const int stride_in_bytes;

    const size_t frame_size;
    const int frame_count;
    const int16_t frame_delay;

    uint8_t *buffer;
} gif_t;

gif_t gif_load_from_file(const char *file_path);

uint8_t *gif_extract_frame(const gif_t gif, int frame_index);

void gif_export_frames(const char *file_path, const gif_t gif);

#endif // GIF_DATA_H_