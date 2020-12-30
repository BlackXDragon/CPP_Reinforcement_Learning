#if !defined(BANDITACTION_H)
#define BANDITACTION_H

#include "../../lib/action.h"

class BanditAction : public BaseAction {
	private:
		unsigned int value;
	public:
		BanditAction(std::string Name, unsigned int Value) {
			this->name = "BanditAction-"+Name;
			this->value = Value;
		}
		BanditAction() {
			this->name = "AnonymousBanditAction";
			this->value = 1;
		}
		double getValue() const {
			return this->value;
		}
};

struct BanditActionHash {
	public:
		size_t operator() (const BanditAction &ba) const {
			return ba.getValue();
		}
};

struct BanditActionEquality {
	public:
		size_t operator() (const BanditAction &ba1, const BanditAction &ba2) const {
			return ba1.getValue() == ba2.getValue();
		}
};

#endif // BANDITACTION_H
