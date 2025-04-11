#include "SurvivorCamp.h"
#include "Survivor.h"  // for survivor's functionality
#include "Mutant.h"    // for mutant types
#include <iostream>

SurvivorCamp::SurvivorCamp(Combatant* survivor) 
    : survivor(survivor), turn(0) 
{
}

SurvivorCamp::~SurvivorCamp() {
    for (Combatant* mutant : mutants) {
        delete mutant;
    }
}

void SurvivorCamp::AddMutant(Combatant* mutant) {
    mutants.push_back(mutant);
}

void SurvivorCamp::SimulateTurn() {
    if (!survivor->IsDead() && !mutants.empty()) {
        survivor->TakeTurn(mutants.front());
    }
    
    if (!mutants.empty()) {
        Combatant* currentMutant = mutants.front();
        if (currentMutant->IsDead()) {
            std::cout << currentMutant->GetID() << " has been defeated." << std::endl;
            mutants.erase(mutants.begin());
            delete currentMutant;
        } else {
            currentMutant->TakeTurn(survivor);
        }
    }
}

int SurvivorCamp::SimulateCamp() {
    while (!survivor->IsDead() && !mutants.empty()) {
        SimulateTurn();
        turn++;
    }
    return turn;
}
