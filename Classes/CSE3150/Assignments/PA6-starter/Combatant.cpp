#include "Combatant.h"

Combatant::Combatant(const std::string &id) : id(id) {}

void Combatant::Attack(Combatant* target) const {
    // Default behavior: do nothing.
}
