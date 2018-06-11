#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    template<typename TraitsT>
    class DefaultUnaryFunction : public IUnaryFunction {
    public:
        using Traits = TraitsT;

        DefaultUnaryFunction(IFunctionPtr arg)
            : IUnaryFunction(std::move(arg))
        { }

        const std::string& GetName() const override
        {
            static std::string name = TraitsT::GetName();
            return name;
        }

        float EvalSingle(float x, float y, float a) const override
        {
            return TraitsT::Eval(a);
        }
    };

    template<typename GeneratedT>
    class DefaultUnaryFunctionGenerator : public IUnaryFunctionGenerator {
    public:
        const std::string& GetName() const override
        {
            static std::string name = GeneratedT::Traits::GetName();
            return name;
        }

        IFunctionPtr Make(IFunctionPtr arg0) override
        {
            return std::make_unique<GeneratedT>(std::move(arg0));
        }
    };

    // -----------------------------------------------------------------------

    template<typename TraitsT>
    class DefaultBinaryFunction : public IBinaryFunction {
    public:
        using Traits = TraitsT;

        DefaultBinaryFunction(IFunctionPtr arg0, IFunctionPtr arg1)
            : IBinaryFunction(std::move(arg0), std::move(arg1))
        { }

        const std::string& GetName() const override
        {
            static std::string name = TraitsT::GetName();
            return name;
        }

        float EvalSingle(float x, float y, float a0, float a1) const override
        {
            return TraitsT::Eval(a0, a1);
        }

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override
        {
            auto& buf0 = m_buffers.at(0);
            auto& buf1 = m_buffers.at(1);

            buf0.resize(xs.size(), Color{0.f});
            buf1.resize(xs.size(), Color{0.f});

            GetArgs().at(0)->EvalRow(xs, y, buf0.data());
            GetArgs().at(1)->EvalRow(xs, y, buf1.data());

            for (size_t i = 0; i < xs.size(); ++i)
            {
                *out = Color{
                    TraitsT::Eval(buf0[i].C1, buf1[i].C1),
                    TraitsT::Eval(buf0[i].C2, buf1[i].C2),
                    TraitsT::Eval(buf0[i].C3, buf1[i].C3)
                };
                ++out;
            }
        }
    };

    template<typename GeneratedT>
    class DefaultBinaryFunctionGenerator : public IBinaryFunctionGenerator {
    public:
        const std::string& GetName() const override
        {
            static std::string name = GeneratedT::Traits::GetName();
            return name;
        }

        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1) override
        {
            return std::make_unique<GeneratedT>(std::move(arg0), std::move(arg1));
        }
    };

}