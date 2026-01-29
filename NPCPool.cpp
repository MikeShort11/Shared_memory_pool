#include "NPCPool.h"
#include <stdexcept>

//_____________Constuctor / Destructor_____________//
Pool::Pool(std::size_t count, bool trace = true)
{
  _block_size = sizeof(int);
  _memory_block = new std::byte[_block_size * count];
  trace_enabled = trace;
  for (std::size_t i = 0; i < count; ++i)
  {
    free_indices.push_back(i);
  }
  if (trace_enabled)
  {
    std::cout << "Pool created with " << count << " slots of size " << _block_size << " bytes\n";
  }
}

Pool::~Pool()
{
  if (_memory_block != nullptr)
  {
    delete[] _memory_block;
  }
}

void *Pool::allocate()
{
  if (!free_indices.empty())
  {
    int index = free_indices.back();
    free_indices.pop_back();
    ++live_npcs;
    if (trace_enabled)
    {
      std::cout << "Allocated slot at index " << index << "\n";
    }
    return get_slot(index);
  }
  else
  {
    throw std::bad_alloc();
  }
}

void Pool::deallocate(void *ptr)
{
}