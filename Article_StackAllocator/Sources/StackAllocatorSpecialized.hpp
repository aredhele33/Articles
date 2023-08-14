/// \file    StackAllocatorSpecialized.hpp
/// \project Articles
/// \module  StackAllocator
/// \author  Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

#pragma once

#include <cstdint> //< uint64_t
#include <utility> //< std::forward
#include <vector>

/// This simple allocator provides a way to perform fast stack allocations in pre-allocated memory pools.
///
/// \class StackAllocatorSpecialized
/// \tparam T The type of objects to allocate.
/// \tparam N The number of objects to reserve in each memory pool.
template<class T, uint64_t N>
class StackAllocatorSpecialized
{
public:
    /// Constructor. Calls Grow() to have at least one pre-allocated memory pool.
    ///
    StackAllocatorSpecialized()
    : m_Pools           ()
    , m_CurrentPoolIndex(0)
    {
        Grow();
    }

    /// Destructor. Frees all allocated memory pools.
    ///
    ~StackAllocatorSpecialized()
    {
        for (Pool* pool : m_Pools)
        {
             operator delete(pool->m_Base, std::align_val_t(alignof(T)));
             delete pool;
        }
    }

    /// Allocates one object of type T and returns it. If the current pool is full,
    /// this method will call Grow() and perform real memory allocation to get a
    /// new empty pool.
    ///
    /// \param args The inplace parameters to construct an new object of type T.
    /// \return A valid pointer on an object of type T.
    template <class ...Args>
    T* Allocate(Args&& ... args)
    {
        if (m_Pools[m_CurrentPoolIndex]->m_Head == m_Pools[m_CurrentPoolIndex]->m_Tail)
        {
            if (m_CurrentPoolIndex + 1 >= m_Pools.size())
            {
                // The pool is either full or there is no more pool available.
                // Allocate a new one.
                Grow();
            }

            m_CurrentPoolIndex++;
        }

        T* object = new (m_Pools[m_CurrentPoolIndex]->m_Head) T(std::forward<Args>(args)...);
        m_Pools[m_CurrentPoolIndex]->m_Head += sizeof(T);
        return object;
    }

    /// Clears all allocations without calling the destructor.
    ///
    /// \note If you need to handle non-POD types, you have to destroy all objects
    ///       in order to avoid resource leak, this is important.
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
        pool->m_Base = reinterpret_cast<uint8_t*>(operator new (sizeof(T) * N, std::align_val_t(alignof(T))));
        pool->m_Head = pool->m_Base;
        pool->m_Tail = pool->m_Base + sizeof(T) * N;
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
