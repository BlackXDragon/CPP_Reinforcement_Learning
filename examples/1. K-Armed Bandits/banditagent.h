#if !defined(BANDITAGENT_H)
#define BANDITAGENT_H

#include "../../lib/agent.h"
#include "../../lib/state.h"
#include "../../lib/environment.h"
#include "banditaction.h"
#include "banditenvironment.h"
#include <stdlib.h>
#include <iostream>

class BanditAgent : public BaseAgent<BaseState, BanditAction> {
	public:
		BanditAgent(std::string Name = "1") { this->name = "BanditAgent-"+Name; };
		bool setState(BaseState state) override { return true; };
};

class RandomBanditAgent : public BanditAgent {
	public:
		BanditAction getAction(std::vector<BanditAction> possibleActions) {
			return possibleActions[rand()%possibleActions.size()];
		}
		void run(BaseEnvironment<BaseState, BanditAction> &env, int nSteps = 100, bool verbose = false) {
			if(verbose) {
				std::cout << "Running Random Bandit Agent for " << nSteps << " in " << env.getName() << "\n";
			}
			for(int i = 0; i < nSteps; i++) {
				BanditAction a = this->getAction(env.getPossibleActions());
				double r = env.performAction(a);
				if(verbose) {
					std::cout << "Step: " << i+1 << "\n";
					std::cout << "Bandit took action: " << a.getName() << "\n";
					std::cout << "Bandit got reward: " << r << "\n";
					std::cout << "------------------------" << "\n";
				}
			}
		}
};

#endif // BANDITAGENT_H
