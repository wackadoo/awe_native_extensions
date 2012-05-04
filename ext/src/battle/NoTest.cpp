#include <NoTest.h>

NoTest::NoTest() {

}

void NoTest::pushCategoryToPriority(int category) {
	priorities.push_back(category);
}

const std::vector<int>& NoTest::test(const Faction* myFaction, const Battle& battle) const {
	return priorities;
}
