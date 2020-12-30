#if !defined(BANDITAGENT_H)
#define BANDITAGENT_H

#include "../../lib/agent.h"
#include "../../lib/state.h"
#include "banditaction.h"
#include <stdlib.h>

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
};

#endif // BANDITAGENT_H
