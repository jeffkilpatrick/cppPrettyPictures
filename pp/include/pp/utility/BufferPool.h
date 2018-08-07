#pragma once

#include "pp/Color.h"

#include <mutex>
#include <vector>

namespace pp {
    class PP_EXPORT BufferPool {
    public:
        ~BufferPool();
        BufferPool(const BufferPool&) = delete;
        BufferPool& operator=(const BufferPool&) = delete;

        static BufferPool& Instance();

        using Buffer = std::vector<Color>;
        using BufferPtr = std::unique_ptr<Buffer>;
        using Pool = std::vector<BufferPtr>;

        BufferPtr Get();
        void Return(BufferPtr buffer);

    private:
        BufferPool();

        Pool m_pool;
        std::mutex m_mutex;
    };
}
