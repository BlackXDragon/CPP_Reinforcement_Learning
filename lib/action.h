#if !defined(ACTION_H)
#define ACTION_H

#include <string>

class BaseAction {
	protected:
		std::string name;
		double value;
	public:
		BaseAction(std::string Name, double Value) : name(Name), value(Value) {}
		BaseAction() : name(""), value(0.0) {}
		virtual double getValue() { return value; }
		virtual std::string getName() { return name; }
};

#endif // ACTION_H
