#include "pp/Eval.h"
#include "pp/fun/IFunction.h"

// TODO-jrk: it'd be cool if we supported arbitrary evaluation-space bounds so we could pan and zoom
pp::Image pp::Eval(const pp::IFunction& f, size_t width, size_t height)
{
    pp::Image img(width, height);

    std::vector<float> xs;
    xs.reserve(width);
    for (int x = 0; x < width; ++x)
    {
        int half_width = width / 2;
        auto x_pos = (x - half_width) / static_cast<float>(half_width);
        xs.push_back(x_pos);
    }

    for (int y = 0; y < height; ++y)
    {
        int half_height = height / 2;
        auto y_pos = (y - half_height) / static_cast<float>(half_height);

        f.EvalRow(xs, y_pos, img.GetRow(y));
    }

    return img;
}