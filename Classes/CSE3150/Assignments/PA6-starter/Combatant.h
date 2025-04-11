#ifndef COMBATANT_H
#define COMBATANT_H

#include <string>

// Base class for all combatants.
class Combatant {
public:
    // Constructor takes an ID.
    Combatant(const std::string &id);
    virtual ~Combatant() {}

    // Return the combatant's ID.
    std::string GetID() const { return id; }

    // Pure virtual methods.
    virtual bool IsDead() const = 0;
    virtual void TakeTurn(Combatant* target) = 0;
    virtual void ReceiveAttack(int damage) = 0;
    
protected:
    // A helper attack function.
    virtual void Attack(Combatant* target) const;
    
private:
    std::string id;
};

#endif // COMBATANT_H
