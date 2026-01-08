#ifndef SURVIVORCAMP_H
#define SURVIVORCAMP_H

#include <vector>
#include "Combatant.h"

// The simulation camp manages one survivor and a list of mutant combatants.
class SurvivorCamp {
public:
    SurvivorCamp(Combatant* survivor);
    ~SurvivorCamp();

    // Runs the simulation until the survivor dies or no mutants remain.
    int SimulateCamp();
    // Adds a mutant to the encounter list.
    void AddMutant(Combatant* mutant);
    
private:
    void SimulateTurn();
    
    Combatant* survivor;
    std::vector<Combatant*> mutants;
    int turn;
};

#endif // SURVIVORCAMP_H
