#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include "banditaction.h"
#include "banditenvironment.h"
#include "banditagent.h"

int main() {
	srand(time(0));

	BanditAction action("Arm 1", 1);
	std::cout << "Value of " << action.getName() << ": " << action.getValue() << std::endl;

	// std::default_random_engine generator;
	// std::normal_distribution<double> means(0, 1);
	// std::vector<std::normal_distribution<double>> dists;
	// for(int i = 0; i < 3; i++) {
	// 	dists.emplace_back(means(generator), 1);
	// }
	// BanditEnvironment<std::normal_distribution<double>, 3> gbe("1", dists);
	// std::cout << gbe.showDist() << std::endl;

	GaussianBanditEnvironment<3> gbe("1", 3, 2, std::chrono::system_clock::now().time_since_epoch().count());
	std::cout << gbe.showDist() << std::endl;

	std::cout << "Possible actions:" << std::endl;

	std::vector<BanditAction> possibleActions = gbe.getPossibleActions();
	for(auto &i: possibleActions) {
		std::cout << i.getName() << ", " << i.getValue() << "\n";
	}

	std::cout << "Reward for action 1: " << gbe.performAction(action) << std::endl;

	RandomBanditAgent agent;

	std::cout << "Random Agent choice for action: " << agent.getAction(possibleActions).getName() << std::endl;

	agent.run(gbe, 10, true);

	return 0;
}