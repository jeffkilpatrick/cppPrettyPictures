#include "pp/Export.h"
#include "pp/Image.h"

#include "libbmp.h"
#include "lodepng.h"

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

void pp::WritePng(const std::string& path, const pp::Image& img)
{
    auto error = lodepng::encode(path, img.ToRGBA(), img.GetWidth(), img.GetHeight());
    if (error)
    {
        std::string msg = std::string("Failed to encode: ") + lodepng_error_text(error);
        throw std::runtime_error(msg);
    }
}
