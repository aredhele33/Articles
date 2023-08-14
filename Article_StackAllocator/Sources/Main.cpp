/// \file    Main.cpp
/// \project Articles
/// \module  StackAllocator
/// \author  Vincent CALISTO (@aredhele33) - https://vincentcalisto.com

#include <StackAllocatorGeneric.hpp>
#include <StackAllocatorSpecialized.hpp>

struct Dummy
{
    uint32_t m_A { 0 };
    uint32_t m_B { 0 };
};

int main()
{
    {
        // Creates a generic stack allocator with a pre-allocated
        // memory pool of 1024 bytes.
        StackAllocatorGeneric<1024> stackAllocatorGeneric;

        // You can now perform fast stack allocation as much as you want
        // with a minimal overhead, except when a new pool must be allocated.
        uint8_t* rawBufferA = stackAllocatorGeneric.Allocate(64);
        uint8_t* rawBufferB = stackAllocatorGeneric.Allocate(32);

        // Do whatever you want with these buffers.
        // Then, you can clear the allocations.
        stackAllocatorGeneric.Clear();

        // The allocator lifetime is over and memory will be freed.
    }

    {
        // Creates a specialized stack allocator with a pre-allocated
        // memory pool of 64 objects of type 'Dummy'.
        StackAllocatorSpecialized<Dummy, 64> stackAllocatorSpecialized;
        Dummy* unusedA = stackAllocatorSpecialized.Allocate();
        Dummy* unusedB = stackAllocatorSpecialized.Allocate();

        // Then, you can clear the allocations.
        // Important : Destructor will not be called in this implementation.
        stackAllocatorSpecialized.Clear();

        // The allocator lifetime is over and memory will be freed.
    }

    return 0;
}
