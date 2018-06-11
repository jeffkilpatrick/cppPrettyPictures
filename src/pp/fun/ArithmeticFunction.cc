#include "pp/fun/ArithmeticFunction.h"

using pp::ArithmeticFunction;

template<typename TraitsT>
static void EvalRow(
    const std::vector<float>& xs,float y,
    const pp::IFunction& arg0, const pp::IFunction& arg1,
    std::vector<pp::Color>& buf0, std::vector<pp::Color>& buf1,
    pp::Color* out)
{
    buf0.resize(xs.size(), pp::Color{0.f});
    buf1.resize(xs.size(), pp::Color{0.f});

    arg0.EvalRow(xs, y, buf0.data());
    arg1.EvalRow(xs, y, buf1.data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        *out = pp::Color{
            TraitsT::Eval(buf0[i].C1, buf1[i].C1),
            TraitsT::Eval(buf0[i].C2, buf1[i].C2),
            TraitsT::Eval(buf0[i].C3, buf1[i].C3)
        };
        ++out;
    }
}

// --------------------------------------------------------------------

template<typename TraitsT>
ArithmeticFunction<TraitsT>::ArithmeticFunction(IFunctionPtr arg0, IFunctionPtr arg1)
    : IBinaryFunction(std::move(arg0), std::move(arg1))
{ }

template<typename TraitsT>
void ArithmeticFunction<TraitsT>::EvalRow(const std::vector<float>& xs, float y, Color* out) const
{
    ::EvalRow<TraitsT>(xs, y, *GetArgs().at(0), *GetArgs().at(1), m_buffers.at(0), m_buffers.at(1), out);
}

template<typename TraitsT>
float ArithmeticFunction<TraitsT>::EvalSingle(float x, float y, float a0, float a1) const
{
    return TraitsT::Eval(a0, a1);
}

template<typename TraitsT>
const std::string& ArithmeticFunction<TraitsT>::GetName() const
{
    static std::string name = TraitsT::GetName();
    return name;    
}

// --------------------------------------------------------------------

template<typename GeneratedT>
const std::string& pp::ArithmeticFunctionGenerator<GeneratedT>::GetName() const
{
    static std::string name = GeneratedT::Traits::GetName();
    return name;    
}

template<typename GeneratedT>
pp::IFunctionPtr pp::ArithmeticFunctionGenerator<GeneratedT>::Make(IFunctionPtr arg0, IFunctionPtr arg1)
{
    return std::make_unique<GeneratedT>(std::move(arg0), std::move(arg1));
}

// --------------------------------------------------------------------

template class pp::ArithmeticFunctionGenerator<pp::AddFunction>;
template class pp::ArithmeticFunctionGenerator<pp::SubtractFunction>;
template class pp::ArithmeticFunctionGenerator<pp::MultiplyFunction>;
template class pp::ArithmeticFunctionGenerator<pp::DivideFunction>;
