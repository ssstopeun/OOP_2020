#include <iostream>
#define interface struct

interface Strategy {
public:
	virtual int doOperation(int n1, int n2) = 0;
};

class add : public Strategy {
public:
	virtual int doOperation(int n1, int n2) override {
		return n1 + n2;
	}
};

class multiply : public Strategy {
public:
	virtual int doOperation(int n1, int n2) override {
		return n1 * n2;
	}
};

class sub : public Strategy {
public:
	virtual int doOperation(int n1, int n2) override {
		return n1 - n2;
	}
};

class Context {
private:
	Strategy* strategy;
public:
	Context(Strategy* s) {
		strategy = s;
	}
	int executeStrategy(int n1, int n2) {
		return strategy->doOperation(n1, n2);
	}
};

int main() {
	Context* context = new Context(new add());
	std::cout << "10 + 5= " << context->executeStrategy(10, 5) << std::endl;

	context = new Context(new multiply());
	std::cout << "10 * 5= " << context->executeStrategy(10, 5) << std::endl;

	context = new Context(new sub());
	std::cout << "10 - 5= " << context->executeStrategy(10, 5) << std::endl;
}
