#include "pp/Image.h"

using pp::Image;

static size_t RawIndex(size_t x, size_t y, size_t width)
{
    return (x + (y * width));
}

Image::Image(size_t width, size_t height)
    : m_width(width)
    , m_height(height)
    , m_pixels(width * height, Color{0.f})
{ }

size_t Image::GetWidth() const
{
    return m_width;
}

size_t Image::GetHeight() const
{
    return m_height;
}

const pp::Color& Image::GetPixel(size_t x, size_t y) const
{
    return m_pixels.at(RawIndex(x, y, m_width));
}

pp::Color& Image::GetPixel(size_t x, size_t y)
{
    return m_pixels.at(RawIndex(x, y, m_width));
}

const pp::Color* Image::GetRow(size_t y) const
{
    return &m_pixels.at(RawIndex(0, y, m_width));
}

pp::Color* Image::GetRow(size_t y)
{
    return &m_pixels.at(RawIndex(0, y, m_width));
}

const pp::Color& Image::operator()(size_t x, size_t y) const
{
    return GetPixel(x, y);
}

pp::Color& Image::operator()(size_t x, size_t y)
{
    return GetPixel(x, y);
}

uint8_t Image::GetR(size_t x, size_t y) const
{
    return (GetPixel(x, y).C1 + 1.f) * 128.f;
}

uint8_t Image::GetG(size_t x, size_t y) const
{
    return (GetPixel(x, y).C2 + 1.f) * 128.f;
}

uint8_t Image::GetB(size_t x, size_t y) const
{
    return (GetPixel(x, y).C3 + 1.f) * 128.f;
}

uint8_t Image::GetA(size_t x, size_t y) const
{
    return (GetPixel(x, y).A + 1.f) * 128.f;
}

std::vector<uint8_t> Image::ToRGB() const
{
    std::vector<uint8_t> rgba(GetWidth() * GetHeight());

    for (size_t x = 0; x < GetWidth(); x++)
    {
        for (size_t y = 0; y < GetHeight(); y++)
        {
            auto idx = (x + (y * GetWidth())) * 4;
            rgba[idx]     = GetR(x, y);
            rgba[idx + 1] = GetG(x, y);
            rgba[idx + 2] = GetB(x, y);
        }
    }

    return rgba;
}

std::vector<uint8_t> Image::ToRGBA() const
{
    std::vector<uint8_t> rgba(GetWidth() * GetHeight() * 4, 0xFF);

    for (size_t x = 0; x < GetWidth(); x++)
    {
        for (size_t y = 0; y < GetHeight(); y++)
        {
            auto idx = (x + (y * GetWidth())) * 4;
            rgba[idx]     = GetR(x, y);
            rgba[idx + 1] = GetG(x, y);
            rgba[idx + 2] = GetB(x, y);
            // rgba[idx + 3] = 0xFF;
        }
    }

    return rgba;
}
