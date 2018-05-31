#include "pp/Generate.h"
#include "pp/Registry.h"
#include "pp/fun/IFunction.h"

#include <iostream>

int main(int argc, char* argv[])
{
    pp::Registry r;
    auto e = RandomExpression(r);

    std::cout << *e << "\n";

	return 0;
}