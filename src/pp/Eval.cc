#include "pp/Eval.h"
#include "pp/fun/IFunction.h"

pp::Image pp::Eval(const pp::IFunction& f, size_t width, size_t height)
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