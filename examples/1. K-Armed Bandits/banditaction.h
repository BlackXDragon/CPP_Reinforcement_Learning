#if !defined(BANDITACTION_H)
#define BANDITACTION_H

#include "../../lib/action.h"

class BanditAction : public BaseAction {
	private:
		unsigned int value;
	public:
		BanditAction(std::string Name, double Value) {
			this->name = "BanditAction-"+Name;
			this->value = Value;
		}
		BanditAction() {
			this->name = "AnonymousBanditAction";
			this->value = 1;
		}
		virtual double getValue() { return value; }
};

#endif // BANDITACTION_H
