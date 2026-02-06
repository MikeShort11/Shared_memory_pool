#include "NPCPool.h"
#include "NPC.h" //TODO: probably change this after NPC in done
#include <stdexcept>

//_____________Constuctor / Destructor_____________//
Pool::Pool(std::size_t count, bool trace)
{
  // assign default values to the member variables
  _block_size = sizeof(NPC);
  _memory_block = new std::byte[_block_size * count];
  trace_enabled = trace;
  live_npcs = 0;
  // Build the free index vector
  for (std::size_t i = 0; i < count; ++i)
  {
    free_indices.push_back(i);
  }
  // print data if trace enabled
  if (trace_enabled)
  {
    std::cout << "Pool created with " << count << " slots of size " << _block_size << " bytes\n";
  }
}

Pool::~Pool()
{
  // Check for double deletion of the memory block
  if (_memory_block != nullptr)
  {
    delete[] _memory_block;
  }
}

void *Pool::allocate()
{
  // check if there are any free slots
  if (free_indices.empty())
  {
    throw std::bad_alloc();
  }
  else
  {
    // get index from the back of the free indexes
    std::size_t index = free_indices.back();
    free_indices.pop_back();
    ++live_npcs;
    // print data if trace enabled
    if (trace_enabled)
    {
      std::cout << "Allocated slot at index " << index << "\n"
                << std::endl;
    }
    return get_slot(index);
  }
}

void Pool::deallocate(void *ptr)
{
  // static cast to make pointers the same type
  std::byte *p = static_cast<std::byte *>(ptr);
  // p - block is number of elements between pointers, /size makes it the index
  std::size_t index = (p - _memory_block) / _block_size;

  // check that the index is not empty when dellocating
  for (int i = 0; i < free_indices.size(); i++)
  {
    if (free_indices[i] == index)
    {
      throw std::bad_alloc();
    }
  }
  // No need to delete object as we will just overwrite it later
  free_indices.push_back(index);
  --live_npcs;
  if (trace_enabled)
  {
    std::cout << "Deallicated Item at index " << index << "." << std::endl;
  }
}

void Pool::profile() const
{
  // print out needed data
  std::cout << "Number of live NPC's: " << live_npcs << std::endl;
  std::cout << "Avalible Indexes: " << std::endl;
  for (int i = 0; i < free_indices.size(); i++)
  {
    std::cout << free_indices[i] << " ";
  }
}

[[nodiscard]] void *Pool::get_slot(std::size_t index)
{
  return _memory_block + (index * _block_size);
}