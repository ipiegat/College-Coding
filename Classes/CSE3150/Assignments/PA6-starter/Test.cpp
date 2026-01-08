#include "SurvivorCamp.h"
#include "Survivor.h"
#include "Mutant.h"
#include <iostream>
using namespace std;

// compile: g++ .\Mutant.cpp .\Survivor.cpp .\SurvivorCamp.cpp .\Combatant.cpp .\Test.cpp -o sim
// run: ./sim

int main(){
    // Here's an example test case

    // usage:
    // Survivor* survivor = new Scavenger("Scavenger", 85, 10);
    // Survivor* survivor = new Brawler("Brawler", 85, 10);
    // Survivor* survivor = new Acrobat("Acrobat", 85, 10);

    Survivor* survivor = new Medic("Medic", 85, 10);
    SurvivorCamp camp(survivor);
    
    Mutant* zombie = new Zombie("weak zombie", 5, 5);
    camp.AddMutant(zombie);

    MutantPack* pack = new MutantPack("Pack1");
    pack->AddMutant(new Replicator("Rep1", 15, 5, &camp));
    pack->AddMutant(new Replicator("Rep2", 15, 5, &camp));
    pack->AddMutant(new Zombie("Zombie2", 15, 5));
    camp.AddMutant(pack);

    MutantPack* pack2 = new MutantPack("Pack2");
    pack2->AddMutant(new Spitter("Spit1", 15, 5));
    pack2->AddMutant(new Replicator("Rep3", 15, 5, &camp));
    pack2->AddMutant(new Zombie("Zombie3", 40, 5));
    camp.AddMutant(pack2);

    // Output
    int turns = camp.SimulateCamp();
    cout << "Simulation ended after " << turns << " turns." << endl;
    cout << "Ending health of " << survivor->GetID() << " is " << survivor->GetHealth() << endl;
    
    delete survivor;
    return 0;
}
/*
Sample output:


Medic heals for 5. New health = 90.
Medic attacks weak zombie. weak zombie takes 10 damage. Health = -5
weak zombie has been defeated.
Medic attacks Pack1. Rep1 takes 10 damage. Health = 5
Pack1 pack attacks Medic with 3 mutants.
Rep1 replicates itself, creating Rep1_clone1. Rep1 attacks Medic. Medic receives 5 damage. Health = 85
Rep2 replicates itself, creating Rep2_clone1. Rep2 attacks Medic. Medic receives 5 damage. Health = 80
Zombie2 attacks Medic. Medic receives 5 damage. Health = 75
Medic attacks Pack1. Rep1 takes 10 damage. Health = -5
Pack1 pack attacks Medic with 2 mutants.
Rep2 attacks Medic. Medic receives 5 damage. Health = 70
Zombie2 attacks Medic. Medic receives 5 damage. Health = 65
Medic heals for 5. New health = 70.
Medic attacks Pack1. Rep2 takes 10 damage. Health = 5
Pack1 pack attacks Medic with 2 mutants.
Rep2 replicates itself, creating Rep2_clone2. Rep2 attacks Medic. Medic receives 5 damage. Health = 65
Zombie2 attacks Medic. Medic receives 5 damage. Health = 60
Medic attacks Pack1. Rep2 takes 10 damage. Health = -5
Pack1 pack attacks Medic with 1 mutants.
Zombie2 attacks Medic. Medic receives 5 damage. Health = 55
Medic attacks Pack1. Zombie2 takes 10 damage. Health = 5
Pack1 pack attacks Medic with 1 mutants.
Zombie2 attacks Medic. Medic receives 5 damage. Health = 50
Medic heals for 5. New health = 55.
Medic attacks Pack1. Zombie2 takes 10 damage. Health = -5
Pack1 has been defeated.
Medic attacks Pack2. Spit1 takes 10 damage. Health = 5
Pack2 pack attacks Medic with 3 mutants.
Spit1 applies acid effect to Medic.
Rep3 replicates itself, creating Rep3_clone1. Rep3 attacks Medic. Medic receives 5 damage. Health = 50
Zombie3 attacks Medic. Medic receives 5 damage. Health = 45
Medic takes 2 poison damage. Medic attacks Pack2. Spit1 takes 10 damage. Health = -5
Pack2 pack attacks Medic with 2 mutants.
Rep3 attacks Medic. Medic receives 5 damage. Health = 38
Zombie3 attacks Medic. Medic receives 5 damage. Health = 33
Medic heals for 5 and is no longer poisoned. New health = 38.
Medic attacks Pack2. Rep3 takes 10 damage. Health = 5
Pack2 pack attacks Medic with 2 mutants.
Rep3 replicates itself, creating Rep3_clone2. Rep3 attacks Medic. Medic receives 5 damage. Health = 33
Zombie3 attacks Medic. Medic receives 5 damage. Health = 28
Medic attacks Pack2. Rep3 takes 10 damage. Health = -5
Pack2 pack attacks Medic with 1 mutants.
Zombie3 attacks Medic. Medic receives 5 damage. Health = 23
Medic attacks Pack2. Zombie3 takes 10 damage. Health = 30
Pack2 pack attacks Medic with 1 mutants.
Zombie3 attacks Medic. Medic receives 5 damage. Health = 18
Medic heals for 5. New health = 23.
Medic attacks Pack2. Zombie3 takes 10 damage. Health = 20
Pack2 pack attacks Medic with 1 mutants.
Zombie3 attacks Medic. Medic receives 5 damage. Health = 18
Medic attacks Pack2. Zombie3 takes 10 damage. Health = 10
Pack2 pack attacks Medic with 1 mutants.
Zombie3 attacks Medic. Medic receives 5 damage. Health = 13
Medic attacks Pack2. Zombie3 takes 10 damage. Health = 0
Pack2 has been defeated.
Medic heals for 5. New health = 18.
Medic attacks Rep1_clone1. Rep1_clone1 takes 10 damage. Health = -5
Rep1_clone1 has been defeated.
Medic attacks Rep2_clone1. Rep2_clone1 takes 10 damage. Health = 5
Rep2_clone1 replicates itself, creating Rep2_clone1_clone1. Rep2_clone1 attacks Medic. Medic receives 5 damage. Health = 13
Medic attacks Rep2_clone1. Rep2_clone1 takes 10 damage. Health = -5
Rep2_clone1 has been defeated.
Medic heals for 5. New health = 18.
Medic attacks Rep2_clone2. Rep2_clone2 takes 10 damage. Health = -5
Rep2_clone2 has been defeated.
Medic attacks Rep3_clone1. Rep3_clone1 takes 10 damage. Health = 5
Rep3_clone1 replicates itself, creating Rep3_clone1_clone1. Rep3_clone1 attacks Medic. Medic receives 5 damage. Health = 13
Medic attacks Rep3_clone1. Rep3_clone1 takes 10 damage. Health = -5
Rep3_clone1 has been defeated.
Medic heals for 5. New health = 18.
Medic attacks Rep3_clone2. Rep3_clone2 takes 10 damage. Health = -5
Rep3_clone2 has been defeated.
Medic attacks Rep2_clone1_clone1. Rep2_clone1_clone1 takes 10 damage. Health = -5
Rep2_clone1_clone1 has been defeated.
Medic attacks Rep3_clone1_clone1. Rep3_clone1_clone1 takes 10 damage. Health = -5
Rep3_clone1_clone1 has been defeated.
Simulation ended after 24 turns.
Ending health of Medic is 18


*/