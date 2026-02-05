#include "NPC.h"

void *NPC::operator new(std::size_t)
{
  void *p = _pool.allocate();
  return p;
};
void NPC::operator delete(void *ptr)
{
  _pool.deallocate(ptr);
};
void NPC::profile() { _pool.profile(); }
std::ostream &operator<<(std::ostream &os, const NPC &npc)
{
  // Should output: "NPC[name='Goblin_247', type='enemy', pos=(5,10), hp=100]"
  os << "NPC[name='" << npc._name << "', type='" << npc._type << "', pos=(" << npc._x << "," << npc._y << "), hp=" << npc._health << "]" << std::endl;
  return os;
}