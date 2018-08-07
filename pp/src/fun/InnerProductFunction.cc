#include "pp/fun/InnerProductFunction.h"
#include "pp/utility/BufferPool.h"

using pp::InnerProductFunction;

InnerProductFunction::InnerProductFunction(IFunctionPtr fun0, IFunctionPtr fun1)
    : IFunction(std::move(fun0), std::move(fun1))
{ }

void InnerProductFunction::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    auto buf0 = BufferPool::Instance().Get();
    auto buf1 = BufferPool::Instance().Get();

    buf0->resize(xs.size(), Color{0.f});
    buf1->resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf0->data());
    GetArgs().at(1)->EvalRow(xs, y, buf1->data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = Color{
            (*buf0)[i].C1 * (*buf1)[i].C1
          + (*buf0)[i].C2 * (*buf1)[i].C2
          + (*buf0)[i].C3 * (*buf1)[i].C3
        };
        ++out;
    }

    BufferPool::Instance().Return(std::move(buf1));
    BufferPool::Instance().Return(std::move(buf0));
}

const std::string& InnerProductFunction::GetName() const
{
    return InnerProductFunctionGenerator{}.GetName();
}
