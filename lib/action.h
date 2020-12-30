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
		virtual double getValue() const { return value; }
		virtual std::string getName() const { return name; }
};

struct BaseActionHash {
	public:
		size_t operator() (const BaseAction* &ba) const {
			return ba->getValue();
		}
};

struct BaseActionEquality {
	public:
		size_t operator() (const BaseAction &ba1, const BaseAction &ba2) const {
			return ba1.getValue() == ba2.getValue();
		}
};

#endif // ACTION_H
