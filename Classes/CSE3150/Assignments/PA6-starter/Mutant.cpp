#include "Mutant.h"
#include "SurvivorCamp.h" // Needed for Replicator.
#include "Survivor.h"   // Needed for Spitter
#include <iostream>
using namespace std;

// ----- Mutant Base Implementation -----

Mutant::Mutant(const std::string &id, int health, int damage)
    : Combatant(id), health(health), damage(damage) {}

bool Mutant::IsDead() const {
    return health <= 0;
}

int Mutant::GetHealth() const {
    return health;
}

int Mutant::GetDamage() const {
    return damage;
}

void Mutant::setHealth(int newHealth) {
    health = newHealth;
}

void Mutant::setDamage(int newDamage) {
    damage = newDamage;
}

// ----- Zombie Implementation -----

Zombie::Zombie(const std::string &id, int health, int damage)
    : Mutant(id, health, damage) {}

void Zombie::TakeTurn(Combatant* target) {
    cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
}

void Zombie::ReceiveAttack(int dmg) {
    setHealth(health - dmg);
    cout << GetID() << " takes " << dmg << " damage. Health = " << GetHealth() << endl;
}

// replicator
Replicator::Replicator(const std::string &id, int health, int damage, SurvivorCamp* camp)
    : Mutant(id, health, damage), turnCounter(0), cloneCount(0), camp(camp) {}

void Replicator::TakeTurn(Combatant* target) {
    if (turnCounter % 2 == 1) {
        cloneCount++;
        string cloneId = GetID() + "_clone" + to_string(cloneCount);
        Replicator* clone = new Replicator(cloneId, health, damage, camp);
        camp->AddMutant(clone);
        cout << GetID() << " replicates itself, creating " << cloneId << ". ";
    }
    cout << GetID() << " attacks " << target->GetID() << ". ";
    target->ReceiveAttack(damage);
    turnCounter++;
}

void Replicator::ReceiveAttack(int dmg) {
    setHealth(health - dmg);
    cout << GetID() << " takes " << dmg << " damage. Health = " << GetHealth() << endl;
}

// spitter
Spitter::Spitter(const std::string &id, int health, int damage)
    : Mutant(id, health, damage), turnCounter(0) {}

    void Spitter::TakeTurn(Combatant* target) {
        if (turnCounter % 2 == 0) {
            std::cout << GetID() << " applies acid effect to " << target->GetID() << ". ";
            Survivor* survivorTarget = dynamic_cast<Survivor*>(target);
            if (survivorTarget) {
                survivorTarget->ApplyPoison();
            }
        } else {
            std::cout << GetID() << " attacks " << target->GetID() << ". ";
            target->ReceiveAttack(damage);
        }
        turnCounter++;
    }

void Spitter::ReceiveAttack(int dmg) {
    setHealth(health - dmg);
    cout << GetID() << " takes " << dmg << " damage. Health = " << GetHealth() << endl;
}

// mutant pack
MutantPack::MutantPack(const std::string &id)
    : Mutant(id, 0, 0) {}

MutantPack::~MutantPack() {
    for (auto mutant : pack) {
        delete mutant;
    }
}

void MutantPack::AddMutant(Combatant* mutant) {
    pack.push_back(mutant);
}

void MutantPack::TakeTurn(Combatant* target) {
    int activeCount = 0;
    for (auto mutant : pack) {
        if (!mutant->IsDead())
            activeCount++;
    }
    cout << GetID() << " pack attacks " << target->GetID() << " with " << activeCount << " mutants." << endl;
    for (auto mutant : pack) {
        if (!mutant->IsDead())
            mutant->TakeTurn(target);
    }
}

void MutantPack::ReceiveAttack(int dmg) {
    if (!pack.empty()) {
        Combatant* first = pack.front();
        first->ReceiveAttack(dmg);
        if (first->IsDead()) {
            cout << first->GetID() << " has been defeated." << endl;
            pack.erase(pack.begin());
            delete first;
        }
    }
}

bool MutantPack::IsDead() const {
    return pack.empty();
}