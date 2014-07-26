#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/gl.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <png.h>

#define TEXTURE_LOAD_ERROR 0

using namespace std;

static GLuint loadTexture(const char* file_name, int* width, int* height)
{
    png_byte header[8];

    FILE* fp = fopen(file_name, "rb");

    if(fp == NULL)
    {
        perror(file_name);
        return 0;
    }

    fread(header, 1, 8, fp);

    if(png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", file_name);
        fclose(fp);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct
    (
        PNG_LIBPNG_VER_STRING,
        NULL,
        NULL,
        NULL
    );

    if(!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0. \n");
        png_destroy_read_struct
        (
            &png_ptr,
            (png_infopp) NULL,
            (png_infopp) NULL
        );
        fclose(fp);
        return 0;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if(!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            (png_infopp) NULL
        );
        fclose(fp);
        return 0;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    png_get_IHDR
    (
        png_ptr,
        info_ptr,
        &temp_width,
        &temp_height,
        &bit_depth,
        &color_type,
        NULL,
        NULL,
        NULL
    );

    if(width) { *width = temp_width; }
    if(height) { *height = temp_height; }

    if(bit_depth != 8)
    {
        fprintf
        (
            stderr,
            "%s: unsupported bit depth %d. Must be 8.\n",
            file_name,
            bit_depth
        );
        return 0;
    }

    GLint format;
    switch(color_type)
    {
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;
        default:
            fprintf
            (
                stderr,
                "%s: unknown libpng color type %d.\n",
                file_name,
                color_type
            );
            return 0;
    }

    png_read_update_info(png_ptr, info_ptr);

    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    rowbytes += 3 - ((rowbytes - 1) % 4);

    png_byte* image_data = (png_byte*)malloc
        (rowbytes * temp_height * sizeof(png_byte) + 15);
    if(image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data.\n");
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            &end_info
        );
        fclose(fp);
        return 0;
    }

    png_byte** row_pointers = (png_byte**)malloc(temp_height * sizeof(png_byte*));
    if(row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers.\n");
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            &end_info
        );
        free(image_data);
        fclose(fp);
        return 0;
    }

    for(unsigned int i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    png_read_image(png_ptr, row_pointers);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D
    (
        GL_TEXTURE_2D,
        0,
        format,
        temp_width,
        temp_height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        image_data
    );
    glTexParameterf
    (
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );
    glTexParameterf
    (
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
    );
    glTexParameteri
    (
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );
    glTexParameteri
    (
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    png_destroy_read_struct
    (
        &png_ptr,
        &info_ptr,
        &end_info
    );
    free(image_data);
    free(row_pointers);
    fclose(fp);

    return texture;
}
