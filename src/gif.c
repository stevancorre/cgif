#include "gif.h"

#define STB_IMAGE_IMPLEMENTATION

#define STBI_ONLY_GIF
#include "stb_image.h"

uint8_t *gif_extract_frame(const gif_t gif)
{
    int offset = gif.frame_index * (gif.frame_size + 2);
    return gif.buffer + offset;
}

gif_t gif_load_from_file(const char *file_path)
{
    int frame_count;
    int width, height;
    int channel_count = 4;

    stbi_uc *data = stbi_xload(file_path, &width, &height, &channel_count, STBI_rgb_alpha, &frame_count);
    if (data == NULL)
    {
        char *err = errno == 0 ? "Input file is not a gif" : strerror(errno);
        fprintf(stderr, "ERROR: can't open %s: %s\n", file_path, err);
        exit(EXIT_FAILURE);
    }

    int pixel_count = width * height;
    int frame_size = pixel_count * channel_count;
    int16_t frame_delay = *(int16_t *)(&data[frame_size]);;

    return (gif_t)
    {
        .width = width,
        .height = height,
        .channel_count = channel_count,
        .pixel_count = pixel_count,
        .frame_size = frame_size,
        .frame_count = frame_count,
        .frame_delay = frame_delay,

        .frame_index = 0,
        .buffer = data
    };
}
