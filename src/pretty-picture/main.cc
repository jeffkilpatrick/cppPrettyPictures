#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/IFunction.h"

#include "libbmp.h"
#include <iostream>

int main(int argc, char* argv[])
{
    pp::Registry r;
    auto e = RandomExpression(r);

    BmpImg img(512, 512);

    for (int x = 0; x < 512; ++x)
    {
        auto x_pos = (x - 256) / 256.f;
        for (int y = 0; y < 512; ++y)
        {
            auto y_pos = (y - 256) / 256.f;
            auto c = e->Eval(x_pos, y_pos);

            unsigned char r = (c.C1 + 1.f) * 128.f;
            unsigned char g = (c.C2 + 1.f) * 128.f;
            unsigned char b = (c.C3 + 1.f) * 128.f;

            std::cout << c << " --> rgb(" << int(r) << ',' << int(g) << ',' << int(b) << ")\n";

            img.set_pixel(x, y, r, g, b);
        }
    }

    img.write("pretty_picture.bmp");

    std::cout << *e << "\n";

	return 0;
}