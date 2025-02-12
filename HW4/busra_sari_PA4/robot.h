// robot.h

#ifndef ROBOT_H
#define ROBOT_H

#include <string>

class Robot {
protected:
    int strength;
    int hitpoints;
    int hitpointsBeforeHit;
    std::string name;
    bool moved;

public:
    Robot();
    Robot(int newStrength, int newHit, std::string newName);

    void setStrength(int newStrength);
    void setHitpoints(int newHitpoints);
    void setHitpointsBeforeHit(int hitpoints);
    void setName(const std::string &newName);
    void setMoved(bool flag);
    bool isItDead() const;
    int getStrength() const;
    int getHitpoints() const;
    int getHitpointsBeforeHit() const;
    std::string getName() const;
    bool hasMoved() const;

    virtual ~Robot();
    virtual int getDamage() = 0;
};

class Kamikaze : public Robot {
protected:
    static int creation_sequence_number;

public:
    Kamikaze();

    int getDamage() override;
};

class Bulldozer : public Robot {
protected:
    static int creation_sequence_number;

public:
    Bulldozer();

    int getDamage() override;
};

class Roomba : public Robot {
protected:
    static int creation_sequence_number;

public:
    Roomba();

    int getDamage() override;
};

class Humanic : public Robot {
public:
    Humanic(int newStrength, int newHit, std::string newName);

    int getDamage() override;
};

class OptimusPrime : public Humanic {
protected:
    static int creation_sequence_number;

public:
    OptimusPrime();

    int getDamage() override;
};

class RoboCop : public Humanic {
protected:
    static int creation_sequence_number;

public:
    RoboCop();

    int getDamage() override;
};

#endif // ROBOT_H
