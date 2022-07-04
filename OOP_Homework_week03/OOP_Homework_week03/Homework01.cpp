#include <iostream>
class SetValue {
	int x, y;

public:
	void setX(int number) {
		x = number;
	}
	void setY(int number) {
		y = number;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};


int main() {
	SetValue obj;
	obj.setX(33);
	obj.setY(44);

	std::cout << "x = " << obj.getX()<< ", y = " << obj.getY() << std::endl;
	system("pause");
	return 0;
}
