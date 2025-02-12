// robot.cpp

#include "robot.h"
#include <cstdlib> // For rand() function

// Static member initialization
int Kamikaze::creation_sequence_number = 0;
int Bulldozer::creation_sequence_number = 0;
int Roomba::creation_sequence_number = 0;
int OptimusPrime::creation_sequence_number = 0;
int RoboCop::creation_sequence_number = 0;

// Implementation of Robot class methods

Robot::Robot() {}

Robot::Robot(int newStrength, int newHit, std::string newName)
    : strength(newStrength), hitpoints(newHit), hitpointsBeforeHit(hitpoints), name(newName), moved(false) {}

Robot::~Robot() {}

void Robot::setStrength(int newStrength)
{
    strength = newStrength;
}

void Robot::setHitpoints(int newHitpoints)
{
    hitpoints = newHitpoints;
}

void Robot::setHitpointsBeforeHit(int hitpoints)
{
    hitpointsBeforeHit = hitpoints;
}

void Robot::setName(const std::string &newName)
{
    name = newName;
}

void Robot::setMoved(bool flag)
{
    moved = flag;
}

bool Robot::isItDead() const
{
    return hitpoints <= 0;
}

int Robot::getStrength() const
{
    return strength;
}

int Robot::getHitpoints() const
{
    return hitpoints;
}

int Robot::getHitpointsBeforeHit() const
{
    return hitpointsBeforeHit;
}

std::string Robot::getName() const
{
    return name;
}

bool Robot::hasMoved() const
{
    return moved;
}

// Implementation of Kamikaze class methods

Kamikaze::Kamikaze() : Robot(10, 10, "Kamikaze_" + std::to_string(creation_sequence_number++)) {}

int Kamikaze::getDamage()
{
    // A kamikaze robot inflicts damage equal to its hitpoints
    int damage = hitpoints;
    hitpoints = 0;
    return damage;
}

// Implementation of Bulldozer class methods

Bulldozer::Bulldozer() : Robot(50, 200, "Bulldozer_" + std::to_string(creation_sequence_number++)) {}

int Bulldozer::getDamage()
{
    // A bulldozer robot inflicts random damage between 1 and its strength
    return rand() % (strength + 1) + 1;
}

// Implementation of Roomba class methods

Roomba::Roomba() : Robot(3, 10, "Roomba_" + std::to_string(creation_sequence_number++)) {}

int Roomba::getDamage()
{
    // A Roomba robot gets to attack twice
    int damage = rand() % (strength + 1) + 1;
    // damage += rand() % (strength + 1) + 1; // Second attack
    return damage;
}

// Implementation of Humanic class methods

Humanic::Humanic(int newStrength, int newHit, std::string newName)
    : Robot(newStrength, newHit, newName) {}

int Humanic::getDamage()
{
    // Humanic robots have a base damage with a 10% chance of inflicting additional damage
    int damage = rand() % (strength + 1) + 1;
    if (rand() % 100 < 10)
        damage += 50;
    return damage;
}

// Implementation of OptimusPrime class methods

OptimusPrime::OptimusPrime()
    : Humanic(100, 100, "OptimusPrime_" + std::to_string(creation_sequence_number++)) {}

int OptimusPrime::getDamage()
{
    // OptimusPrime robots have a base damage with a 15% chance of inflicting double damage
    int damage = Humanic::getDamage();
    if (rand() % 100 < 15)
        damage *= 2;
    return damage;
}

// Implementation of RoboCop class methods

RoboCop::RoboCop() : Humanic(30, 40, "RoboCop_" + std::to_string(creation_sequence_number++)) {}

int RoboCop::getDamage()
{
    // RoboCop robots have the same base damage as Humanic robots
    return Humanic::getDamage();
}
