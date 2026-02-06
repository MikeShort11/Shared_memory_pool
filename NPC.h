#pragma once
#include <string>
#include "NPCPool.h"

class NPC
{
private:
    std::string _name; // e.g., "Goblin_247"
    std::string _type; // e.g., "merchant", "enemy",
    int _x, _y;        // Grid location on the map
    int _health;       // Health points
    static inline Pool _pool{100, true};

public:
    NPC(const std::string &name, const std::string &type, int x, int y, int health);
    ~NPC() {};
    static void *operator new(std::size_t);
    static void operator delete(void *ptr);
    static void profile();
    friend std::ostream &operator<<(std::ostream &os, const NPC &npc);
};