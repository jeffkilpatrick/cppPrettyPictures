#include "pp/Export.h"
#include "pp/Image.h"

#include "libbmp.h"
#include "lodepng.h"
#include "png.h"

void pp::WriteBmp(const std::string& path, const pp::Image& img)
{
    BmpImg bmp(img.GetWidth(), img.GetHeight());

    for (size_t x = 0; x < img.GetWidth(); x++)
    {
        for (size_t y = 0; y < img.GetHeight(); y++)
        {
            auto r = img.GetR(x, y);
            auto g = img.GetG(x, y);
            auto b = img.GetB(x, y);

            bmp.set_pixel(x, y, r, g, b);
        }
    }

    bmp.write(path);
}

#if 1
namespace
{
    struct png_ptrs
    {
        png_structp png{nullptr};
        png_infop info{nullptr};

        ~png_ptrs()
        {
            png_destroy_write_struct(&png, &info);
        }
    };

    void write_row_callback(png_structp png_ptr, png_uint_32 row, int pass)
    {
        /* do nothing */
    }
}
#endif

void pp::WritePng(const std::string& path, const pp::Image& img, const std::string& description)
{
#if 0
    auto error = lodepng::encode(path, img.ToRGBA(), img.GetWidth(), img.GetHeight());
    if (error)
    {
        std::string msg = std::string("Failed to encode: ") + lodepng_error_text(error);
        throw std::runtime_error(msg);
    }
#else
    std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(path.c_str(), "wb"), &fclose);
    if (!fp)
    {
        std::string msg = std::string("Failed to open: ") + strerror(errno);
        throw std::runtime_error(msg);
    }

    png_ptrs ptrs;

    ptrs.png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!ptrs.png)
    {
        throw std::runtime_error("Could not create png_struct");
    }

    ptrs.info = png_create_info_struct(ptrs.png);
    if (!ptrs.info)
    {
        throw std::runtime_error("Could not create png_info");
    }


    if (setjmp(png_jmpbuf(ptrs.png)))
    {
        throw std::runtime_error("Failed to setjmp for libpng");
    }

    png_init_io(ptrs.png, fp.get());
    png_set_write_status_fn(ptrs.png, write_row_callback);

    png_set_IHDR(
        ptrs.png,
        ptrs.info,
        img.GetWidth(), img.GetHeight(),
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_text ts[1];
    ts[0].compression = PNG_TEXT_COMPRESSION_NONE;
    ts[0].key = const_cast<png_charp>("Description");
    ts[0].text = const_cast<png_charp>(description.c_str());
    ts[0].text_length = description.size();
    png_set_text(ptrs.png, ptrs.info, ts, 1);

    png_write_info(ptrs.png, ptrs.info);

    // Convert the image to 8-bit RGBA
    auto rgba = img.ToRGBA();
    std::vector<png_bytep> row_pointers(img.GetHeight());
    for (size_t y = 0; y < img.GetHeight(); y++)
    {
        auto offset = y * img.GetWidth() * 4;
        row_pointers[y] = &rgba[offset];
    }

    // png_write_image calls png_write_row(), which takes png_const_bytep.
    // This const_cast does not appear to result in any data mutation.
    png_write_image(ptrs.png, const_cast<png_bytepp>(row_pointers.data()));

    png_write_end(ptrs.png, ptrs.info);
#endif
}

std::vector<uint8_t> pp::WritePng(const pp::Image& img)
{
    std::vector<uint8_t> encodedData;

    auto error = lodepng::encode(encodedData, img.ToRGBA(), img.GetWidth(), img.GetHeight());
    if (error)
    {
        std::string msg = std::string("Failed to encode: ") + lodepng_error_text(error);
        throw std::runtime_error(msg);
    }

    return encodedData;
}
