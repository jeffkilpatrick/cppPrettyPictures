#pragma once

#include "pp/utility/Exports.h"

#include <random>

namespace pp {
    class PP_EXPORT IRandom {
    public:
        using result_type = std::random_device::result_type;

        virtual result_type operator()() = 0;
    };

    class PP_EXPORT RandomDevice : public IRandom {
        public:
            result_type operator()() override;

        private:
            std::random_device m_rand;
    };
}
