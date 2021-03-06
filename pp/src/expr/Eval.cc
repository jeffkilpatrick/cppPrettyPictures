#include "pp/expr/Eval.h"
#include "pp/fun/IFunction.h"

#import <dispatch/dispatch.h>

using workContext = std::tuple<std::vector<float>&, pp::Image&, const pp::IFunction&, int>;

void work(void* context, size_t y)
{
    workContext* workPtr = reinterpret_cast<workContext*>(context);
    auto&[xs, img, f, height] = *workPtr;

    int half_height = static_cast<int>(height) / 2;
    auto y_pos = (y - half_height) / static_cast<float>(half_height);

    f.EvalRow(xs, y_pos, img.GetRow(y));
}

// TODO-jrk: it'd be cool if we supported arbitrary evaluation-space bounds so we could pan and zoom
pp::Image pp::Eval(const pp::IFunction& f, size_t width, size_t height, long gcdQos)
{
    pp::Image img(width, height);

    std::vector<float> xs;
    xs.reserve(width);
    for (int x = 0; x < width; ++x)
    {
        int half_width = static_cast<int>(width) / 2;
        auto x_pos = (x - half_width) / static_cast<float>(half_width);
        xs.push_back(x_pos);
    }

#if 1
    workContext context(xs, img, f, height);
    dispatch_apply_f(height, dispatch_get_global_queue(gcdQos, 0), &context, &work);
#else
    for (int y = 0; y < height; ++y)
    {
        int half_height = static_cast<int>(height) / 2;
        auto y_pos = (y - half_height) / static_cast<float>(half_height);

        f.EvalRow(xs, y_pos, img.GetRow(y));
    }
#endif

    return img;
}
