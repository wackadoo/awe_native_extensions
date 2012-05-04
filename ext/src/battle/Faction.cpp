#include <Faction.h>

#include <util/ErrorHandling.h>

Faction::Faction() {}
Faction::~Faction() {}

void Faction::addArmy(Army* army) {
	armies.push_back(army);
}
size_t Faction::numArmies() const {
	return armies.size();
}
Army* Faction::getArmy(size_t i) {
	return armies[i];
}

size_t Faction::startSize() const {
	size_t num = 0;
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		num += (*it)->startSize();
	}
	return num;
}

size_t Faction::startSizeOfCategory(int category) const {
	size_t num = 0;
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		num += (*it)->startSizeOfCategory(category);
	}
	return num;
}

bool Faction::hasOfUnitsCategory(int category) const {
	std::vector<Army*>::const_iterator it;
	for (it = armies.begin(); it != armies.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->hasOfUnitsCategory(category)) {
			return true;
		}
	}
	return false;
}