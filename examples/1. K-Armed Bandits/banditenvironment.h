#if !defined(BANDITENV_H)
#define BANDITENV_H

#include "../../lib/environment.h"
#include "../../lib/state.h"
#include "banditaction.h"
#include <stdlib.h>
#include <vector>
#include <random>
#include <cassert>
#include <stdexcept>

template<class distribution, int k>
class BanditEnvironment : public BaseEnvironment<BaseState, BanditAction> {
	protected:
		std::default_random_engine generator;
		std::vector<distribution> dists;
		int _k = k;
	public:
		BanditEnvironment(std::string Name, std::vector<distribution> d, int seed = false) {
			if(seed) {
				this->generator = std::default_random_engine(seed);
			}
			this->name = std::to_string(k)+"-BanditEnvironment-"+Name;
			assert(d.size() == k);
			this->dists = d;
		}
		BanditEnvironment() {
			this->name = std::to_string(k)+"-AnonymousBanditEnvironment-";
		}
		std::vector<BanditAction> getPossibleActions(BaseState s = BaseState()) override {
			std::vector<BanditAction> actions;
			for(int i = 0; i < k; i++) {
				actions.emplace_back("Arm "+std::to_string(i+1), i+1);
			}
			return actions;
		}
		double performAction(BanditAction action) override {
			int aVal = action.getValue() - 1;
			if(aVal >= this->_k || aVal < 0) {
				throw std::invalid_argument((const char*)("Action value out of bounds. Expected between 1 and "+std::to_string(this->_k)+", got "+std::to_string(aVal+1)+".").c_str());
			}
			return this->dists[aVal](this->generator);
		}
		std::string showDist() {
			std::string output = "Distribution of " + this->name + ":\n";
			output += "k: " + std::to_string(this->_k) + "\n";
			for(int i = 0; i < this->dists.size(); i++) {
				output += "Arm " + std::to_string(i+1) + ": " + std::to_string(this->dists[i].mean()) + ", " + std::to_string(this->dists[i].stddev()) + "\n";
			}
			return output;
		}
};

template<int k>
class GaussianBanditEnvironment : public BanditEnvironment<std::normal_distribution<double>, k> {
	public:
		GaussianBanditEnvironment(std::string Name = "1", double mean = 0, double stddev = 1, int seed = false) {
			if(seed) {
				this->generator = std::default_random_engine(seed);
			}
			this->name = std::to_string(k)+"-GaussianBanditEnvironment-"+Name;
			std::normal_distribution<double> means(mean, stddev);
			for(int i = 0; i < k; i++) {
				this->dists.emplace_back(means(this->generator), 1);
			}
		}
};

#endif // BANDITENV_H
