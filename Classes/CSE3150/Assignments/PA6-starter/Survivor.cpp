#include "Survivor.h"
#include <iostream>
using namespace std;

// ----- Survivor Base Implementation -----

Survivor::Survivor(const std::string &id, int health, int damage)
    : Combatant(id), health(health), damage(damage), poisonCounter(0) {}

bool Survivor::IsDead() const {
    return health <= 0;
}

int Survivor::GetHealth() const {
    return health;
}

int Survivor::GetDamage() const {
    return damage;
}

void Survivor::setHealth(int newHealth) {
    health = newHealth;
}

void Survivor::setDamage(int newDamage) {
    damage = newDamage;
}

void Survivor::ApplyPoison() {
    // If not already poisoned, set poison duration to 2 turns.
    if (poisonCounter == 0) {
        poisonCounter = 2;
    }
}

void Survivor::ProcessPoison() {
    // At the start of each turn, if poisoned, apply 2 damage and decrement the counter.
    if (poisonCounter > 0) {
        setHealth(health - 2);
        std::cout << GetID() << " takes 2 poison damage. ";
        poisonCounter--;
        if (poisonCounter == 0) {
            std::cout << GetID() << " is no longer poisoned. ";
        }
    }
}


// ----- Scavenger Implementation -----

Scavenger::Scavenger(const std::string &id, int health, int damage)
    : Survivor(id, health, damage) {}

void Scavenger::TakeTurn(Combatant* target) {
    ProcessPoison();
    cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
}

void Scavenger::ReceiveAttack(int dmg) {
    setHealth(health - dmg);
    cout << GetID() << " receives " << dmg << " damage. Health = " << GetHealth() << endl;
}

// brawler
Brawler::Brawler(const std::string &id, int health, int damage)
    : Survivor(id, health, damage) {}

void Brawler::TakeTurn(Combatant* target) {
    ProcessPoison();
    std::cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
    if (target->IsDead()) {
        std::cout << GetID() << " gains bonus damage for killing " << target->GetID() << ". ";
        setDamage(GetDamage() + 2);
        std::cout << "New damage = " << GetDamage() << "." << std::endl;
    }
}

void Brawler::ReceiveAttack(int dmg) {
    setHealth(GetHealth() - dmg);
    std::cout << GetID() << " receives " << dmg << " damage. Health = " << GetHealth() << std::endl;
}

// acrobat
Acrobat::Acrobat(const std::string &id, int health, int damage)
    : Survivor(id, health, damage), turnCounter(0), dodgeReady(true) {}

void Acrobat::TakeTurn(Combatant* target) {
    ProcessPoison();
    if (turnCounter % 4 == 0)
        dodgeReady = true;
    
    std::cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
    turnCounter++;
}

void Acrobat::ReceiveAttack(int dmg) {
    if (dodgeReady) {
        std::cout << GetID() << " dodges the attack." << std::endl;
        dodgeReady = false;
    } else {
        setHealth(GetHealth() - dmg);
        std::cout << GetID() << " receives " << dmg << " damage. Health = " << GetHealth() << std::endl;
    }
}

// medic
Medic::Medic(const std::string &id, int health, int damage)
    : Survivor(id, health, damage), turnCounter(0) {}

void Medic::TakeTurn(Combatant* target) {
    if (turnCounter % 3 == 0) {
        std::cout << GetID() << " heals for 5. ";
        setHealth(GetHealth() + 5);
        if (poisonCounter > 0) {
            poisonCounter = 0;
            std::cout << GetID() << " is no longer poisoned. ";
        }
        std::cout << "New health = " << GetHealth() << ". " << std::endl;
    } else {
        ProcessPoison();
    }
    std::cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
    turnCounter++;
}

void Medic::ReceiveAttack(int dmg) {
    setHealth(GetHealth() - dmg);
    std::cout << GetID() << " receives " << dmg << " damage. Health = " << GetHealth() << std::endl;
}
