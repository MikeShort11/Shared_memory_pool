#pragma once
#include <string>
#include "NPCPool.h"

// TODO: add << operator
class NPC
{
private:
    std::string _name; // e.g., "Goblin_247"
    std::string _type; // e.g., "merchant", "enemy",
    int _x, _y;        // Grid location on the map
    int _health;       // Health points
    static inline Pool _pool{100, true};

public:
    NPC(const std::string &name, const std::string &type, int x, int y, int health)
        : _name(name), _type(type), _x(x), _y(y), _health(health) {}
    static void *operator new(std::size_t)
    {
        void *p = _pool.allocate();
        return p;
    };
    static void operator delete(void *ptr)
    {
        _pool.deallocate(ptr);
        free(ptr);
    };
    static void profile() { _pool.profile(); }
};