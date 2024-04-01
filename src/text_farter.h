#ifndef APP_H
#define APP_H

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include "png.h"
#include <stdint.h>

FT_Glyph getGlyph(FT_Face face, uint32_t charcode);
FT_Pos getKerning(FT_Face face, uint32_t leftCharcode, uint32_t rightCharcode);
void savePNG(uint8_t* image, int32_t width, int32_t height, char* image_file);

#ifdef BUILD_STATIC
#include <stdlib.h>
#endif

#ifdef BUILD_DYNAMIC
#include <stdlib.h>
#include <dlfcn.h>
int (*Init_FreeType)(FT_Library*);
int (*New_Face)(FT_Library, const char*, FT_Long, FT_Face*);
int (*Set_Pixel_Sizes)(FT_Face, FT_UInt, FT_UInt);
int (*Done_Glyph)(FT_Glyph);
int (*Load_Char)(FT_Face, FT_ULong, FT_Int32);
int (*Get_Glyph)(FT_GlyphSlot, FT_Glyph*);
int (*Get_Char_Index)(FT_Face, FT_ULong);
int (*Get_Kerning)(FT_Face, FT_UInt, FT_UInt, FT_UInt, FT_Vector*);
int (*Done_Face)(FT_Face);
int (*Done_FreeType)(FT_Library);

void (*init_io)(png_structrp, png_FILE_p);
void (*write_end)(png_structrp, png_inforp);
void (*write_row)(png_structrp, png_const_bytep);
void (*write_info)(png_structrp, png_const_inforp);
void* (*create_info_struct)(png_const_structrp);
void (*destroy_write_struct)(png_structpp, png_infopp);
void* (*create_write_struct)(png_const_charp, png_voidp, png_error_ptr, png_error_ptr);
void (*set_IHDR)(png_const_structrp, png_inforp, png_uint_32, png_uint_32, int, int, int, int, int);
void (*free_data)(png_const_structrp, png_inforp, png_uint_32, int);


#define FT_New_Face New_Face
#define FT_Load_Char Load_Char
#define FT_Get_Glyph Get_Glyph
#define FT_Done_Glyph Done_Glyph
#define FT_Init_FreeType Init_FreeType
#define FT_Get_Char_Index Get_Char_Index
#define FT_Set_Pixel_Sizes Set_Pixel_Sizes
#define FT_Get_Kerning Get_Kerning
#define FT_Done_Face Done_Face
#define FT_Done_FreeType Done_FreeType

#define png_init_io init_io
#define png_set_IHDR set_IHDR
#define png_write_end write_end
#define png_write_row write_row
#define png_write_info write_info
#define png_create_info_struct create_info_struct
#define png_create_write_struct create_write_struct
#define png_destroy_write_struct destroy_write_struct
#define png_free_data free_data

void* freetype;
void* libpng;
void* libz;

int open_dll();

int close_dll();
#endif

struct Symbol
{ 
    int32_t posX;        
    int32_t posY;            
    int32_t width;        
    int32_t height;    

    FT_Glyph glyph;
};

const size_t MAX_SYMBOLS_COUNT = 128;

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#ifdef BUILD_BLOB

void** glob_functions;

clock_t clock(void)
{
    return ((clock_t(*)(void))glob_functions[0])();
}

FILE* fopen(const char* fname, const char* mode)
{
    return ((FILE * (*)(const char*, const char*))glob_functions[1])(fname, mode);
}

int fclose( FILE * filestream )
{
    return ((int (*)(FILE*))glob_functions[2])(filestream);
}

void* malloc(size_t size)
{
    return ((void* (*)(size_t))glob_functions[3])(size);
}

void free(void* ptr)
{
    return ((void (*)(void*))glob_functions[4])(ptr);
}

size_t strlen(const char* str)
{
    return ((size_t(*)(const char*))glob_functions[5])(str);
}


#endif
#endif

