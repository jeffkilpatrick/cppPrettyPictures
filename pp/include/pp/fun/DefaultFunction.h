#pragma once

#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"

namespace pp {

    template<typename TraitsT>
    class DefaultNonaryFunction : public INonaryFunction {
    public:
        using Traits = TraitsT;

        const std::string& GetName() const override
        {
            static std::string name = TraitsT::GetName();
            return name;
        }

        float EvalSingle(float x, float y) const override
        {
            return TraitsT::Eval(x, y);
        }

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override
        {
            for (size_t i = 0; i < xs.size(); ++i)
            {
                *out = Color{
                    TraitsT::Eval(xs[i], y),
                    TraitsT::Eval(xs[i], y),
                    TraitsT::Eval(xs[i], y)
                };
                ++out;
            }
        }
    };

    template<typename GeneratedT>
    class DefaultNonaryFunctionGenerator : public INonaryFunctionGenerator {
    public:
        const std::string& GetName() const override
        {
            static std::string name = GeneratedT::Traits::GetName();
            return name;
        }

        IFunctionPtr Make() override
        {
            return std::make_unique<GeneratedT>();
        }
    };

    // -----------------------------------------------------------------------

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
            return TraitsT::Eval(x, y, a);
        }

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override
        {
            auto& buf = m_buffers.at(0);

            buf.resize(xs.size(), Color{0.f});

            GetArgs().at(0)->EvalRow(xs, y, buf.data());

            for (size_t i = 0; i < xs.size(); ++i)
            {
                *out = Color{
                    TraitsT::Eval(xs[i], y, buf[i].C1),
                    TraitsT::Eval(xs[i], y, buf[i].C2),
                    TraitsT::Eval(xs[i], y, buf[i].C3)
                };
                ++out;
            }
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
            return TraitsT::Eval(x, y, a0, a1);
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
                    TraitsT::Eval(xs[i], y, buf0[i].C1, buf1[i].C1),
                    TraitsT::Eval(xs[i], y, buf0[i].C2, buf1[i].C2),
                    TraitsT::Eval(xs[i], y, buf0[i].C3, buf1[i].C3)
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

    // -----------------------------------------------------------------------

    template<typename TraitsT>
    class DefaultTrinaryFunction : public ITrinaryFunction {
    public:
        using Traits = TraitsT;

        DefaultTrinaryFunction(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2)
            : ITrinaryFunction(std::move(arg0), std::move(arg1), std::move(arg2))
        { }

        const std::string& GetName() const override
        {
            static std::string name = TraitsT::GetName();
            return name;
        }

        float EvalSingle(float x, float y, float a0, float a1, float a2) const override
        {
            return TraitsT::Eval(x, y, a0, a1, a2);
        }

        void EvalRow(const std::vector<float>& xs, float y, Color* out) const override
        {
            auto& buf0 = m_buffers.at(0);
            auto& buf1 = m_buffers.at(1);
            auto& buf2 = m_buffers.at(2);

            buf0.resize(xs.size(), Color{0.f});
            buf1.resize(xs.size(), Color{0.f});
            buf2.resize(xs.size(), Color{0.f});

            GetArgs().at(0)->EvalRow(xs, y, buf0.data());
            GetArgs().at(1)->EvalRow(xs, y, buf1.data());
            GetArgs().at(2)->EvalRow(xs, y, buf2.data());

            for (size_t i = 0; i < xs.size(); ++i)
            {
                *out = Color{
                    TraitsT::Eval(xs[i], y, buf0[i].C1, buf1[i].C1, buf2[i].C1),
                    TraitsT::Eval(xs[i], y, buf0[i].C2, buf1[i].C2, buf2[i].C2),
                    TraitsT::Eval(xs[i], y, buf0[i].C3, buf1[i].C3, buf2[i].C3)
                };
                ++out;
            }
        }
    };

    template<typename GeneratedT>
    class DefaultTrinaryFunctionGenerator : public ITrinaryFunctionGenerator {
    public:
        const std::string& GetName() const override
        {
            static std::string name = GeneratedT::Traits::GetName();
            return name;
        }

        IFunctionPtr Make(IFunctionPtr arg0, IFunctionPtr arg1, IFunctionPtr arg2) override
        {
            return std::make_unique<GeneratedT>(std::move(arg0), std::move(arg1), std::move(arg2));
        }
    };
}