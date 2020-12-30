#if !defined(AGENT_H)
#define AGENT_H

#include <string>
#include <vector>

template<class StateType, class ActionType>
class BaseAgent {
	protected:
		std::string name;
		BaseState state;
	public:
		BaseAgent(std::string Name) : name(Name) {}
		BaseAgent() : name("AnonymousAgent") {}
		virtual std::string getName() { return name; }
		virtual bool setState(StateType state) = 0;
		virtual ActionType getAction(std::vector<ActionType> possibleActions) = 0;
};

#endif // AGENT_H
