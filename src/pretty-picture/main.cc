#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/IFunction.h"

#include "libbmp.h"
#include "lodepng.h"

#include <getopt.h>
#include <iostream>
#include <vector>

size_t RawIndex(size_t x, size_t y, size_t width)
{
    return (x + (y * width)) * 4;
}

std::vector<uint8_t> Eval(const pp::IFunction& f, size_t width, size_t height)
{
    std::vector<uint8_t> rgba(width * height * 4, 0xFF);

    for (int y = 0; y < height; ++y)
    {
        int half_height = height / 2;
        auto y_pos = (y - half_height) / static_cast<float>(half_height);

        for (int x = 0; x < width; ++x)
        {
            int half_width = width / 2;
            auto x_pos = (x - half_width) / static_cast<float>(half_width);

            auto c = f.Eval(x_pos, y_pos);
            uint8_t r = (c.C1 + 1.f) * 128.f;
            uint8_t g = (c.C2 + 1.f) * 128.f;
            uint8_t b = (c.C3 + 1.f) * 128.f;

            auto idx = RawIndex(x, y, width);
            rgba[idx + 0] = r;
            rgba[idx + 1] = g;
            rgba[idx + 2] = b;
            // rgba[idx + 3] = a;
        }
    }

    return rgba;
}

void WriteBmp(const std::string& path, const std::vector<uint8_t>& rgba, size_t width, size_t height)
{
    BmpImg bmp(width, height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            auto idx = RawIndex(x, y, width);
            auto r = rgba[idx + 0];
            auto g = rgba[idx + 1];
            auto b = rgba[idx + 2];

            bmp.set_pixel(x, y, r, g, b);
        }
    }

    bmp.write(path);
}

void WritePng(const std::string& path, const std::vector<uint8_t>& rgba, size_t width, size_t height)
{
    auto error = lodepng::encode(path, rgba, width, height);
    if (error)
    {
        std::string msg = std::string("Failed to encode: ") + lodepng_error_text(error);
        throw std::runtime_error(msg);
    }
}

struct Options {
    size_t Width{640};
    size_t Height{480};
    bool Render{false};
    std::string Png;
    std::string Bmp;
    size_t MaxDepth{5};
};

size_t ScanSize(const std::string& str)
{
    auto s = std::strtoul(str.c_str(), nullptr, 10);
    if (errno == ERANGE)
    {
        throw std::range_error("size out of range");
    }

    return s;
}

Options GetOptions(int argc, char* argv[])
{
    Options opts;
    int c;
    while ((c = getopt(argc, argv, "b:p:w:h:d:")) != -1)
    {
        switch (c)
        {
        case 'b':
            opts.Render = true;
            opts.Bmp = optarg;
            break;

        case 'p':
            opts.Render = true;
            opts.Png = optarg;
            break;

        case 'w':
            opts.Width = ScanSize(optarg);
            break;

        case 'h':
            opts.Height = ScanSize(optarg);
            break;

        case 'd':
            opts.MaxDepth = ScanSize(optarg);
            break;
        }
    }

    return opts;
}

int main(int argc, char* argv[])
{
    auto opts = GetOptions(argc, argv);

    pp::Registry r;
    auto e = RandomExpression(r, opts.MaxDepth);
    std::cout << *e << "\n";

    if (opts.Render)
    {
        auto rgba = Eval(*e, opts.Width, opts.Height);

        if (!opts.Bmp.empty())
        {
            WriteBmp(opts.Bmp, rgba, opts.Width, opts.Height);
        }

        if (!opts.Png.empty())
        {
            WritePng(opts.Png, rgba, opts.Width, opts.Height);
        }
    }

	return 0;
}
