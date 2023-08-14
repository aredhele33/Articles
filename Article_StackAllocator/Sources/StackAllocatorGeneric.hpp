/// \file    StackAllocatorGeneric.hpp
/// \project Articles
/// \module  StackAllocator
/// \author  Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

#pragma once

#include <cstdint>   //< uint64_t
#include <stdexcept>
#include <utility>   //< std::forward
#include <vector>

/// This simple allocator provides a way to perform fast stack allocations in pre-allocated memory pools.
///
/// \class StackAllocatorGeneric
/// \tparam N The number of bytes to reserve in each memory pool.
template<uint64_t N>
class StackAllocatorGeneric
{
public:
    /// Constructor. Calls Grow() to have at least one pre-allocated memory pool.
    ///
    StackAllocatorGeneric()
    : m_Pools           ()
    , m_CurrentPoolIndex(0)
    {
        Grow();
    }

    /// Destructor. Frees all allocated memory pools.
    ///
    ~StackAllocatorGeneric()
    {
        for (Pool* pool : m_Pools)
        {
             delete[] pool->m_Base;
             delete   pool;
        }
    }

    /// Allocates N bytes and returns it. If the current pool is full,
    /// this method will call Grow() and perform real memory allocation to get a
    /// new empty pool.
    ///
    /// \param n The number of bytes to allocate.
    /// \return A valid pointer on on a buffer of n bytes.
    uint8_t* Allocate(uint32_t n)
    {
        if(n > N)
        {
            // Well, this is the pathological case.
            // Someone is trying to allocate a buffer larger than the pool itself.
            // Obviously, you can handle it with an assertion or a nullptr, I personally don't
            // use exceptions in my projects.
            throw std::bad_alloc();
        }

        if (m_Pools[m_CurrentPoolIndex]->m_Head + n > m_Pools[m_CurrentPoolIndex]->m_Tail)
        {
            if (m_CurrentPoolIndex + 1 >= m_Pools.size())
            {
                // The pool is either full or there is no more pool available.
                // Allocate a new one.
                Grow();
            }

            m_CurrentPoolIndex++;
        }

        uint8_t* buffer = m_Pools[m_CurrentPoolIndex]->m_Head;
        m_Pools[m_CurrentPoolIndex]->m_Head += n;
        return buffer;
    }

    /// Clears all allocations. Fast and efficient.
    ///
    void Clear()
    {
        for (Pool* pool : m_Pools)
        {
            pool->m_Head = pool->m_Base;
        }

        m_CurrentPoolIndex = 0;
    }

private:
    void Grow()
    {
        Pool* pool   = m_Pools.emplace_back(new Pool());
        pool->m_Base = new uint8_t[N];
        pool->m_Head = pool->m_Base;
        pool->m_Tail = pool->m_Base + N;
    }

private:
    struct Pool
    {
        uint8_t* m_Head { nullptr };
        uint8_t* m_Tail { nullptr };
        uint8_t* m_Base { nullptr };
    };

    using Pools = std::vector<Pool*>;

private:
    Pools    m_Pools;
    uint64_t m_CurrentPoolIndex;
};
