#include "pp/Export.h"
#include "pp/expr/Breed.h"
#include "pp/expr/Eval.h"
#include "pp/expr/Generate.h"
#include "pp/fun/Registry.h"
#include "pp/serialize/FunctionParser.h"
#include "pp/serialize/FunctionSerializer.h"

#include <boost/optional.hpp>
#include <getopt.h>
#include <iostream>
#include <vector>

struct Options {
    size_t Width{640};
    size_t Height{480};
    boost::optional<std::string> Expr;
    boost::optional<std::string> BreedExpr;
    bool Render{false};
    std::string Png;
    std::string Bmp;
    pp::Range Depth{1, 5};
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
    while ((c = getopt(argc, argv, "B:P:w:h:d:e:b:")) != -1)
    {
        switch (c)
        {
        case 'B':
            opts.Render = true;
            opts.Bmp = optarg;
            break;

        case 'P':
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
            opts.Depth.Max = ScanSize(optarg);
            break;

        case 'e':
            opts.Expr = optarg;
            break;

        case 'b':
            opts.BreedExpr = optarg;
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
        : RandomExpression(registry, opts.Depth);

    if (opts.BreedExpr)
    {
        auto b = pp::Parse(std::string(opts.BreedExpr.get()), registry);
        e = pp::Breed(e, b, registry);
    }

    std::cout << *e << "\n";

    if (opts.Render)
    {
        auto image = Eval(*e, opts.Width, opts.Height);

        if (!opts.Bmp.empty())
        {
            pp::WriteBmp(opts.Bmp, image);
        }

        if (!opts.Png.empty())
        {
            pp::WritePng(opts.Png, image);
        }
    }

	return 0;
}
