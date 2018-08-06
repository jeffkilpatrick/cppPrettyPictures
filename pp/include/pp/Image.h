#pragma once

#include "pp/Color.h"
#include "pp/utility/Exports.h"

#include <vector>

namespace pp {
    class PP_EXPORT Image {
    public:
        Image(size_t width, size_t height);

        size_t GetWidth() const;
        size_t GetHeight() const;

        const Color& GetPixel(size_t x, size_t y) const;
        Color& GetPixel(size_t x, size_t y);

        const Color* GetRow(size_t y) const;
        Color* GetRow(size_t y);

        const Color& operator()(size_t x, size_t y) const;
        Color& operator()(size_t x, size_t y);

        uint8_t GetR(size_t x, size_t y) const;
        uint8_t GetG(size_t x, size_t y) const;
        uint8_t GetB(size_t x, size_t y) const;

        std::vector<uint8_t> ToRGBA() const;

    private:
        size_t m_width;
        size_t m_height;
        std::vector<Color> m_pixels;
    };
}