#include "pp/fun/Arity.h"
#include "pp/fun/ConstantFunction.h"
#include "pp/fun/IFunction.h"
#include "pp/fun/IFunctionGenerator.h"
#include "pp/serialize/FunctionParser.h"
#include "pp/serialize/Scanner.h"
#include "pp/Registry.h"

using pp::TokenType;

static pp::IFunctionPtr ParseExpression(pp::Scanner& scanner, const pp::Registry& registry);

static pp::IFunctionPtr ParseNonaryFunction(pp::IFunctionGeneratorPtr generator)
{
    return dynamic_cast<pp::INonaryFunctionGenerator&>(*generator).Make();
}

static pp::IFunctionPtr ParseUnaryFunction(
    pp::IFunctionGeneratorPtr generator,
    pp::Scanner& scanner,
    const pp::Registry& registry)
{
    auto arg = ParseExpression(scanner, registry);
    return dynamic_cast<pp::IUnaryFunctionGenerator&>(*generator).Make(std::move(arg));
}

static pp::IFunctionPtr ParseBinaryFunction(
    pp::IFunctionGeneratorPtr generator,
    pp::Scanner& scanner,
    const pp::Registry& registry)
{
    auto arg0 = ParseExpression(scanner, registry);
    auto arg1 = ParseExpression(scanner, registry);
    return dynamic_cast<pp::IBinaryFunctionGenerator&>(*generator)
        .Make(std::move(arg0), std::move(arg1));
}

static pp::IFunctionPtr ParseTrinaryFunction(
    pp::IFunctionGeneratorPtr generator,
    pp::Scanner& scanner,
    const pp::Registry& registry)
{
    auto arg0 = ParseExpression(scanner, registry);
    auto arg1 = ParseExpression(scanner, registry);
    auto arg2 = ParseExpression(scanner, registry);
    return dynamic_cast<pp::ITrinaryFunctionGenerator&>(*generator)
        .Make(std::move(arg0), std::move(arg1), std::move(arg2));
}

static pp::IFunctionPtr ParseFunction(
    const std::string& name,
    pp::Scanner& scanner,
    const pp::Registry& registry)
{
    auto generator = registry.Get(name);

    switch (generator->GetArity())
    {
    case pp::Arity::Nonary:
        return ParseNonaryFunction(std::move(generator));

    case pp::Arity::Unary:
        return ParseUnaryFunction(std::move(generator), scanner, registry);

    case pp::Arity::Binary:
        return ParseBinaryFunction(std::move(generator), scanner, registry);

    case pp::Arity::Trinary:
        return ParseTrinaryFunction(std::move(generator), scanner, registry);
    }
}

static pp::IFunctionPtr ParseConst(pp::Scanner& scanner)
{
    auto r = scanner.Next(TokenType::Real).GetReal();
    auto g = scanner.Next(TokenType::Real).GetReal();
    auto b = scanner.Next(TokenType::Real).GetReal();
    return std::make_unique<pp::ConstantFunction>(pp::Color{r, g, b});
}

static pp::IFunctionPtr ParseExpression(pp::Scanner& scanner, const pp::Registry& registry)
{
    scanner.Next(TokenType::OpenParen);

    auto ident = scanner.Next();

    pp::IFunctionPtr fun;

    switch (ident.GetType())
    {
    case TokenType::Identifier:
        fun = ParseFunction(ident.GetString(), scanner, registry);
        break;
    case TokenType::Const:
        fun = ParseConst(scanner);
        break;
    default:
        throw std::runtime_error("Parse error");
    }

    scanner.Next(TokenType::CloseParen);

    return fun;
}

pp::IFunctionPtr pp::Parse(std::string&& str, const pp::Registry& registry)
{
    pp::Scanner scanner(std::move(str));

    return ParseExpression(scanner, registry);
}
