#ifndef MUTANT_H
#define MUTANT_H

#include "Combatant.h"
#include <vector>
#include <string>

// Base mutant class.
class Mutant : public Combatant {
public:
    Mutant(const std::string &id, int health, int damage);
    virtual ~Mutant() {}

    bool IsDead() const override;

    int GetHealth() const;
    int GetDamage() const;
    
protected:
    void setHealth(int newHealth);
    void setDamage(int newDamage);
    
    int health;
    int damage;
};

// --- Derived Mutant Types ---

// Zombie: basic mutant that attacks every turn.
class Zombie : public Mutant {
public:
    Zombie(const std::string &id, int health, int damage);
    void TakeTurn(Combatant* target) override;
    void ReceiveAttack(int damage) override;
};    

// replicator
class SurvivorCamp; // Forward declaration.

class Replicator : public Mutant {
public:
    Replicator(const std::string &id, int health, int damage, SurvivorCamp* camp);
    void TakeTurn(Combatant* target) override;
    void ReceiveAttack(int dmg) override;
private:
    int turnCounter;
    int cloneCount;
    SurvivorCamp* camp;
};

// spitter
class Spitter : public Mutant {
public:
    Spitter(const std::string &id, int health, int damage);
    void TakeTurn(Combatant* target) override;
    void ReceiveAttack(int dmg) override;
private:
    int turnCounter;
};

// mutantpack
class MutantPack : public Mutant {
public:
    MutantPack(const std::string &id);
    ~MutantPack();

    void AddMutant(Combatant* mutant);
    void TakeTurn(Combatant* target) override;
    void ReceiveAttack(int dmg) override;
    bool IsDead() const override;
private:
    std::vector<Combatant*> pack;
};

#endif