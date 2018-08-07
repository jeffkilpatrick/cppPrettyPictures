#include "pp/utility/BufferPool.h"

using pp::BufferPool;

/*static*/ BufferPool& BufferPool::Instance()
{
    static BufferPool s_pool;
    return s_pool;
}

BufferPool::BufferPtr BufferPool::Get()
{
    // TODO-jrk: read/write lock and only get exclusive lock if we need to pull from the pool
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_pool.empty()) {
        return std::make_unique<Buffer>();
    }

    auto pool = std::move(m_pool.back());
    m_pool.pop_back();

    return pool;
}

void BufferPool::Return(BufferPool::BufferPtr buffer)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_pool.push_back(std::move(buffer));
}
