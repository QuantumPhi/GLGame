#include "loader.h"

static GLuint loadTexture(const char* file_name, int* width, int* height)
{
    png_byte header[8];
    FILE* fp = fopen(file_name, "rb");
    if(!fp)
    {
        return 0;
    }

    fread(header, 0, sizeof(header) / sizeof(png_byte), fp);

    if(!png_sig_cmp(header, 0, sizeof(header) / sizeof(png_byte)))
    {
        cout << "File specified not a proper .PNG" << endl;
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
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        png_destroy_read_struct
        (
            &png_ptr,
            NULL,
            NULL
        );
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if(!end_info)
    {
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            &end_info
        );
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int bit_depth, color_type;
    png_uint_32 twidth, theight;

    png_get_IHDR
    (
        png_ptr,
        info_ptr,
        &twidth,
        &theight,
        &bit_depth,
        &color_type,
        NULL,
        NULL,
        NULL
    );

    *width = twidth;
    *height = theight;

    png_read_update_info(png_ptr, info_ptr);

    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    png_byte* image_data = new png_byte[rowbytes * (*height)];
    if(!image_data)
    {
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            &end_info
        );
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    png_bytep* row_pointers = new png_bytep[*height];
    if(!row_pointers)
    {
        png_destroy_read_struct
        (
            &png_ptr,
            &info_ptr,
            &end_info
        );
        delete [] image_data;
        fclose(fp);
        return TEXTURE_LOAD_ERROR;
    }

    for(int i = 0; i < *height; i++)
    {
        row_pointers[*height - 1 - i] = image_data + i * rowbytes;
    }
    png_read_image(png_ptr, row_pointers);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D
    (
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        (GLsizei) *width,
        (GLsizei) *height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        (GLvoid*) image_data
    );
    glTexParameteri
    (
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );

    png_destroy_read_struct
    (
        &png_ptr,
        &info_ptr,
        &end_info
    );
    delete [] image_data;
    delete [] row_pointers;
    fclose(fp);

    return texture;
}
