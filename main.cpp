#include <iostream>
#include <vector>
#include "NPC.h"
int main()
{
  // Create several NPCs
  std::vector<NPC *> npcs;
  // Spawn a wave of enemies
  for (int i = 0; i < 10; ++i)
  {
    npcs.push_back(new NPC(
        "Goblin_" + std::to_string(i),
        "enemy",
        i * 10, i * 10, // Position
        50 + i * 5      // Health
        ));
  }
  // Show one NPC
  std::cout << *npcs[5] << std::endl;
  // Delete some NPCs (simulating death)
  delete npcs[3];
  delete npcs[5];
  npcs[3] = nullptr;
  npcs[5] = nullptr;
  // Profile the pool
  NPC::profile();
  // Spawn replacements
  npcs[3] = new NPC("Dragon_Boss", "boss", 50, 50, 500);
  npcs[5] = new NPC("Shopkeeper", "merchant", 25, 25, 100);
  // Clean up all NPCs
  for (auto *npc : npcs)
  {
    delete npc;
  }
  // Final profile
  NPC::profile();
  return 0;
}