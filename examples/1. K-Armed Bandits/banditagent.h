#if !defined(BANDITAGENT_H)
#define BANDITAGENT_H

#include "../../lib/agent.h"
#include "../../lib/state.h"
#include "../../lib/environment.h"
#include "banditaction.h"
#include "banditenvironment.h"
#include <stdlib.h>
#include <iostream>
#include <unordered_map>

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
				std::cout << "Running Random Bandit Agent for " << nSteps << " steps in " << env.getName() << "\n";
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

class epsilonGreedyBanditAgent : public BanditAgent {
	protected:
		std::unordered_map<BanditAction, double, BanditActionHash, BanditActionEquality> actionValueTable;
		double init_exp = 0;
		double eps = 0.3;
		double step_s = 0.5;
	public:
		epsilonGreedyBanditAgent(std::string Name = "1", double initial_expectation = 0, double epsilon = 0.3, double step_size = 0.5): BanditAgent(Name), init_exp(initial_expectation), eps(epsilon), step_s(step_size) {}

		BanditAction getAction(const std::vector<BanditAction> possibleActions) override {
			BanditAction greedyAction;
			double highestVal = -99999;
			for(auto i: possibleActions) {
				if(this->actionValueTable.find(i) == this->actionValueTable.end())
					this->actionValueTable.insert(std::pair<BanditAction, double>(i, this->init_exp));
				auto el = this->actionValueTable.find(i);
				if(el->second > highestVal) {
					greedyAction = el->first;
					highestVal = el->second;
				}
			}
			if((rand()/RAND_MAX) < this->eps) {
				return possibleActions[rand()%possibleActions.size()];
			}
			return greedyAction;
		}

		void update(BanditAction a, double reward) {
			auto x = this->actionValueTable.find(a);
			x->second = x->second + this->step_s * (reward - x->second);
		}
		
		void run(BaseEnvironment<BaseState, BanditAction> &env, int nSteps = 100, bool verbose = false) {
			if(verbose) {
				std::cout << "Running epsilon Greedy Bandit Agent for " << nSteps << " steps in " << env.getName() << "\n";
			}
			for(int i = 0; i < nSteps; i++) {
				BanditAction a = this->getAction(env.getPossibleActions());
				std::cout << "Step: " << i+1 << "\n";
				double r = env.performAction(a);
				this->update(a, r);
				if(verbose) {
					std::cout << "Step: " << i+1 << "\n";
					std::cout << "Bandit took action: " << a.getName() << "\n";
					std::cout << "Bandit got reward: " << r << "\n";
					std::cout << "Action Value Table: " << "\n";
					this->printAVTable();
					std::cout << "------------------------" << "\n";
				}
			}
		}
		void printAVTable() const {
			for (auto itr: this->actionValueTable) { 
				std::cout << itr.first.getName() << '\t' << itr.second << '\n'; 
			}
		}
};

#endif // BANDITAGENT_H
