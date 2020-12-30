#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include <string>
#include "state.h"
#include "action.h"

class BaseEnvironment {
	protected:
		std::string name;
	public:
		BaseEnvironment(std::string Name) : name(Name) {};
		virtual std::string getName() { return name; }
		virtual double performAction(BaseAction action) = 0;
};

#endif // ENVIRONMENT_H
