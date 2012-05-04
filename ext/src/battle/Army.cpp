#include <Army.h>

#include <util/ErrorHandling.h>
#include <util/Random.h>
#include <algorithm>

Army::Army(int playerId) : playerId(playerId) {

}

Army::~Army() {

}

void Army::addUnit(Unit* unit) {
	this->units.push_back(unit);
}

Unit* Army::getUnit(size_t i) {
	return units[i];
}
size_t Army::numUnits() const {
	return units.size();
}

size_t Army::startSize() const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		re += (*it)->numUnitsAtStart;
	}
	return re;
}

size_t Army::startSizeOfCategory(int category) const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category) {
			re += (*it)->numUnitsAtStart;
		}
	}
	return re;
}

size_t Army::numUnitsAlive() const {
	size_t re = 0;
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		re += (*it)->numUnitsAtStart - (*it)->numDeaths;
	}
	return re;
}

bool Army::hasOfUnitsCategory(int category) const {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category) {
			return true;
		}
	}
	return false;
}

Unit* Army::getFirstAliveUnitOfCategory(int category) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if (!(*it)->valid()) {
			aweError("Unit was not valid");
		}
		if ((*it)->numUnitsAtStart > 0 && (*it)->unitCategoryId == category && (*it)->numUnitsAtStart > (*it)->numDeaths) {
			return (*it);
		}
	}
	return 0;
}

void Army::getAllUnitsOfCategory(int category, std::vector<Unit*> result) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category) {
			result.push_back(*it);
		}
	}
}

void Army::getAllAliveUnitsOfCategory(int category, std::vector<Unit*> result) {
	std::vector<Unit*>::const_iterator it;
	for(it = units.begin(); it != units.end(); it++) {
		awePtrCheck(*it);
		if ((*it)->unitCategoryId == category && (*it)->numUnitsAtStart > (*it)->numDeaths) {
			result.push_back(*it);
		}
	}
}

Army* Army::getAllAliveUnitsOfCategory(int category) {
	Army* re = new Army(-1);
	getAllAliveUnitsOfCategory(category, re->units);
	return re;
}

void Army::shuffle() {
	util::Random::shuffle<Unit*>(units);
}

void Army::sortByInitiative() {
	std::sort(units.begin(), units.end(), Unit::initiativeGreater);
}