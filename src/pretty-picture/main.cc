#include "pp/Generate.h"
#include "pp/Image.h"
#include "pp/Registry.h"
#include "pp/fun/IFunction.h"
#include "pp/serialize/FunctionParser.h"
#include "pp/serialize/FunctionSerializer.h"

#include "libbmp.h"
#include "lodepng.h"

#include <boost/optional.hpp>
#include <getopt.h>
#include <iostream>
#include <vector>


pp::Image Eval(const pp::IFunction& f, size_t width, size_t height)
{
    pp::Image img(width, height);

    for (int y = 0; y < height; ++y)
    {
        int half_height = height / 2;
        auto y_pos = (y - half_height) / static_cast<float>(half_height);

        for (int x = 0; x < width; ++x)
        {
            int half_width = width / 2;
            auto x_pos = (x - half_width) / static_cast<float>(half_width);

            img(x, y) = f.Eval(x_pos, y_pos);
        }
    }

    return img;
}

void WriteBmp(const std::string& path, const pp::Image& img)
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

void WritePng(const std::string& path, const pp::Image& img)
{
    auto error = lodepng::encode(path, img.ToRGBA(), img.GetWidth(), img.GetHeight());
    if (error)
    {
        std::string msg = std::string("Failed to encode: ") + lodepng_error_text(error);
        throw std::runtime_error(msg);
    }
}

struct Options {
    size_t Width{640};
    size_t Height{480};
    boost::optional<std::string> Expr;
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
    while ((c = getopt(argc, argv, "b:p:w:h:d:e:")) != -1)
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

        case 'e':
            opts.Expr = optarg;
            break;
        }
    }

    return opts;
}

int main(int argc, char* argv[])
{
    auto opts = GetOptions(argc, argv);

    pp::Registry registry;

    auto e = opts.Expr
        ? pp::Parse(std::string(opts.Expr.get()), registry)
        : RandomExpression(registry, opts.MaxDepth);
    std::cout << *e << "\n";

    if (opts.Render)
    {
        auto image = Eval(*e, opts.Width, opts.Height);

        if (!opts.Bmp.empty())
        {
            WriteBmp(opts.Bmp, image);
        }

        if (!opts.Png.empty())
        {
            WritePng(opts.Png, image);
        }
    }

	return 0;
}
