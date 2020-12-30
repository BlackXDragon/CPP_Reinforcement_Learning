#if !defined(STATE_H)
#define STATE_H

#include <string>

class BaseState {
	protected:
		std::string name;
		double value;
	public:
		BaseState(std::string Name) : name(Name) {}
		BaseState() : name("AnonymousState"), value(0.0) {}
		virtual double calcValue() = 0;
		virtual double getValue() { return value; }
		virtual std::string getName() { return name; }
};

#endif // STATE_H
