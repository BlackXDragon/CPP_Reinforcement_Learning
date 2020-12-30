#if !defined(AGENT_H)
#define AGENT_H

#include <string>
#include "action.h"
#include "state.h"

class BaseAgent {
	protected:
		std::string name;
		BaseState state;
	public:
		BaseAgent(std::string Name) : name(Name) {};
		virtual std::string getName() { return name; }
		virtual bool setState(BaseState state) = 0;
		virtual BaseAction getAction() = 0;
};

#endif // AGENT_H
