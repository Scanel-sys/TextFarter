#include "text_farter.h"

#ifdef BUILD_DYNAMIC
int open_dll()
{
    libz = dlopen("../deps/shared/libzip.so", RTLD_LAZY);
    if (!libz)
    {
        printf("libz.so не была загружена\n");
        return 0;
    }
    freetype = dlopen("../deps/shared/libfreetype.so", RTLD_LAZY);
    if (!freetype)
    {
        printf("libfreetype.so не была загружена\n");
        return 0;
    }
    libpng = dlopen("../deps/shared/libpng.so", RTLD_LAZY);
    if (!libpng)
    {
        printf("libpng.so не была загружена\n");
        return 0;
    }

    New_Face = dlsym(freetype, "FT_New_Face");
    Get_Glyph = dlsym(freetype, "FT_Get_Glyph");
    Load_Char = dlsym(freetype, "FT_Load_Char");
    Done_Glyph = dlsym(freetype, "FT_Done_Glyph");
    Init_FreeType = dlsym(freetype, "FT_Init_FreeType");
    Get_Char_Index = dlsym(freetype, "FT_Get_Char_Index");
    Set_Pixel_Sizes = dlsym(freetype, "FT_Set_Pixel_Sizes");
    Get_Kerning = dlsym(freetype, "FT_Get_Kerning");
    Done_Face = dlsym(freetype, "FT_Done_Face");
    Done_FreeType = dlsym(freetype, "FT_Done_FreeType");


    create_info_struct = dlsym(libpng, "png_create_info_struct");
    create_write_struct = dlsym(libpng, "png_create_write_struct");
    init_io = dlsym(libpng, "png_init_io");
    set_IHDR = dlsym(libpng, "png_set_IHDR");
    write_end = dlsym(libpng, "png_write_end");
    destroy_write_struct = dlsym(libpng, "png_destroy_write_struct");
    write_row = dlsym(libpng, "png_write_row");
    write_info = dlsym(libpng, "png_write_info");
    free_data = dlsym(libpng, "png_free_data");

    return 1;
}

int close_dll()
{
    dlclose(libz);
    dlclose(libpng);
    dlclose(freetype);
}
#endif

#ifdef BUILD_BLOB
int main(int argc, char* argv[], void** functions)
{
   glob_functions = functions;
#else
int main(int argc, char* argv[])
{
    clock_t start = clock();
#endif
    FILE* ttf_file = fopen(argv[1], "rb");
    if (!ttf_file)
    {
        printf("TTF файл не был открыт\n");
        return 1;
    }
    fclose(ttf_file);  
#ifdef BUILD_DYNAMIC
    if (!open_dll())
    {
        printf("Ошибка открытия библиотек\n");
        return 1;
    }
    printf("Общее время загрузки программы: %ld\n", (clock() - start));
#endif
    FT_Library ftLibrary = 0;
    FT_Init_FreeType(&ftLibrary);
    FT_Face ftFace = 0;
    FT_New_Face(ftLibrary, argv[1], 0, &ftFace);
    FT_Set_Pixel_Sizes(ftFace, 256, 256);
    const char* String = argv[2]; 
    const size_t StringLen = strlen(String);
    struct Symbol symbols[MAX_SYMBOLS_COUNT];
    size_t numSymbols = 0;
    int32_t left = INT_MAX;
    int32_t top = INT_MAX;
    int32_t bottom = INT_MIN;
    uint32_t prevCharcode = 0;
    size_t i = 0;
    int32_t posX = 0;
    for (i = 0; i < StringLen; ++i)
    {
        const uint32_t charcode = String[i];
        FT_Glyph glyph = getGlyph(ftFace, charcode);
        if (!glyph)
        {
            continue;
        }
        if (prevCharcode)
        {
            posX += getKerning(ftFace, prevCharcode, charcode);
        }
        prevCharcode = charcode;

        struct Symbol* symb = &(symbols[numSymbols++]);

        FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;
        symb->posX = (posX >> 6) + bitmapGlyph->left;      
        symb->posY = -bitmapGlyph->top;          
        symb->width = bitmapGlyph->bitmap.width;     
        symb->height = bitmapGlyph->bitmap.rows;   
        symb->glyph = glyph;                            
        posX += glyph->advance.x >> 10;   
        left = MIN(left, symb->posX);                      
        top = MIN(top, symb->posY);                           
        bottom = MAX(bottom, symb->posY + symb->height);     
    }
    for (i = 0; i < numSymbols; ++i)
    {
        symbols[i].posX -= left;
    }

    const struct Symbol* lastSymbol = &(symbols[numSymbols - 1]);

    const int32_t imageW = lastSymbol->posX + lastSymbol->width;
    const int32_t imageH = bottom - top;
    uint8_t* image = (uint8_t*)malloc(imageW * imageH);
    for (i = 0; i < numSymbols; ++i)
    {
        const struct Symbol* symb = symbols + i;

        FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)symb->glyph;
        FT_Bitmap bitmap = bitmapGlyph->bitmap;

        for (int32_t srcY = 0; srcY < symb->height; ++srcY)
        {
            const int32_t dstY = symb->posY + srcY - top;
            for (int32_t srcX = 0; srcX < symb->width; ++srcX)
            {
                const uint8_t c = bitmap.buffer[srcX + srcY * bitmap.pitch];
                if (0 == c)
                {
                    continue;
                }
                const float a = c / 255.0f;
                const int32_t dstX = symb->posX + srcX;  
                uint8_t* dst = image + dstX + dstY * imageW;
                dst[0] = (uint8_t)(a * 255 + (1 - a) * dst[0]);
            }
        }
    }
    savePNG(image, imageW, imageH, argv[3]);
    free(image);
    for (i = 0; i < numSymbols; ++i)
    {
        FT_Done_Glyph(symbols[i].glyph);
    }
    FT_Done_Face(ftFace);
    ftFace = 0;
    FT_Done_FreeType(ftLibrary);
    ftLibrary = 0;
    #ifdef BUILD_DYNAMIC
    close_dll();
    #endif
    #ifndef BUILD_BLOB
    printf("Общее время работы программы: %ld\n", (clock() - start));
    #endif
    return 0;
}

FT_Glyph getGlyph(FT_Face face, uint32_t charcode)
{
    FT_Load_Char(face, charcode, FT_LOAD_RENDER);
    FT_Glyph glyph = 0;
    FT_Get_Glyph(face->glyph, &glyph);
    return glyph;
}

FT_Pos getKerning(FT_Face face, uint32_t leftCharcode, uint32_t rightCharcode)
{
    FT_UInt leftIndex = FT_Get_Char_Index(face, leftCharcode);
    FT_UInt rightIndex = FT_Get_Char_Index(face, rightCharcode);
    FT_Vector delta;
    FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
    return delta.x;
}


void savePNG(uint8_t* image, int32_t width, int32_t height, char* image_file)
{
    FILE* f = fopen(image_file, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, f);
    png_set_IHDR(
        png_ptr,
        info_ptr,
        width,
        height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    uint8_t* row = malloc(width * 4);
    for (int32_t y = 0; y < height; ++y)
    {
        for (int32_t x = 0; x < width; ++x)
        {
            row[x * 4 + 0] = 0x00;
            row[x * 4 + 1] = 0x00;
            row[x * 4 + 2] = 0x00;
            row[x * 4 + 3] = image[y * width + x];
        }
        png_write_row(png_ptr, row);
    }
    free(row);
    png_write_end(png_ptr, 0);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, 0);
    fclose(f);
}
