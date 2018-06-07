#pragma once

namespace pp {
    enum class TokenType {
        End,
        Whitespace,

        OpenParen,
        CloseParen,

        Identifier,
        Real
    };
}