#pragma once
#include <string>

class NPC
{
private:
    std::string _name; // e.g., "Goblin_247"
    std::string _type; // e.g., "merchant", "enemy",
    int _x, _y;        // Grid location on the map
    int _health;       // Health points
public:
    NPC(std::string &name, std::string &type, int x, int y, int health)
        : _name(name), _type(type), _x(x), _y(y), _health(health) {}
    static void *operator new(std::size_t);
    static void operator delete(void *ptr);
};