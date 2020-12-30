#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include <string>
#include <vector>

template<class StateType, class ActionType>
class BaseEnvironment {
	protected:
		std::string name;
	public:
		BaseEnvironment(std::string Name) : name(Name) {}
		BaseEnvironment() : name("AnonymousEnvironment") {}
		virtual std::string getName() { return name; }
		virtual std::vector<ActionType> getPossibleActions(StateType state = StateType()) = 0;
		virtual double performAction(ActionType action) = 0;
};

#endif // ENVIRONMENT_H
