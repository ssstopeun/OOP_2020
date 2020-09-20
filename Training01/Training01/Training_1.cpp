#include<iostream>

class SetValue {
public:
	int x, y;
};

int main() {
	SetValue obj;
	obj.x = 33;
	obj.y = 44;

	std::cout << "x = " << obj.x << ", y = " << obj.y << std::endl;
	return 0;
}