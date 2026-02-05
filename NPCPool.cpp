#include "NPCPool.h"
#include "NPC.h" //TODO: probably change this after NPC in done
#include <stdexcept>

//_____________Constuctor / Destructor_____________//
Pool::Pool(std::size_t count, bool trace)
{
  _block_size = sizeof(NPC);
  _memory_block = new std::byte[_block_size * count];
  trace_enabled = trace;
  live_npcs = 0;
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
  if (free_indices.empty())
  {
    throw std::bad_alloc();
  }
  else
  {
    std::size_t index = free_indices.back();
    free_indices.pop_back();
    ++live_npcs;
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
  // static cast to make pointer arithmatic work
  std::byte *p = static_cast<std::byte *>(ptr);
  std::size_t index = (p - _memory_block) / _block_size;

  for (int i = 0; i < free_indices.size(); i++)
  {
    if (free_indices[i] == index)
    {
      throw std::bad_alloc(); // probably the wrong error, but i think i need this check
    }
  }
  free_indices.push_back(index);
  --live_npcs;
  if (trace_enabled)
  {
    std::cout << "Deallicated Item at index " << index << "." << std::endl;
  }
}

void Pool::profile() const
{
  std::cout << "Number of live NPC's: " << live_npcs << std::endl;
  std::cout << "Avalible Indexes: " << std::endl;
  for (int i = 0; i < free_indices.size(); i++)
  {
    std::cout << free_indices[i] << " ";
  }
}