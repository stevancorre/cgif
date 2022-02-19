#include "gif.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#define STBI_ONLY_GIF

#include "stb_image.h"
#include "stb_image_write.h"

#define PATH_CAPACITY 512

uint8_t *gif_extract_frame(const gif_t gif, int frame_index)
{
    int offset = frame_index * (gif.frame_size + 2);
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

    int stride_in_bytes = width * channel_count;
    int frame_size = (width * height) * channel_count;
    int16_t frame_delay = *(int16_t *)(&data[frame_size]);

    return (gif_t){
        .width = width,
        .height = height,

        .channel_count = channel_count,
        .stride_in_bytes = stride_in_bytes,

        .frame_size = frame_size,
        .frame_count = frame_count,
        .frame_delay = frame_delay,

        .buffer = data};
}

bool build_path(char *dest, size_t size, char *subdir, int frame_index)
{
    if (dest == NULL || size < 1)
    {
        return false;
    }

    if (subdir == NULL)
    {
        subdir = "";
    }

    size_t stored = snprintf(dest, size, "%s/frame-%d.png", subdir, frame_index);
    return stored + 1 <= size;
}

void gif_export_frames(char *dir_path, const gif_t gif)
{
    for (int frame_index = 0; frame_index < gif.frame_count; frame_index++)
    {
        uint8_t *frame_data = gif_extract_frame(gif, frame_index);

        char output_file_path[PATH_CAPACITY];
        if (!build_path(output_file_path, sizeof(output_file_path), dir_path, frame_index))
        {
            fprintf(stderr, "ERROR: can't write to %s: %s\n", output_file_path, strerror(errno));
            exit(1);
        }

        if (stbi_write_png(output_file_path, gif.width, gif.height, gif.channel_count, frame_data, gif.stride_in_bytes) == 0)
        {
            fprintf(stderr, "ERROR: can't write to %s: %s\n", output_file_path, strerror(errno));
            exit(1);
        }
    }
}