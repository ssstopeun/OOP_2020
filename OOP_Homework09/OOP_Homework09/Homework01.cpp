#include <iostream>

class MyData {
	int number;
	std::string strNumber;
public:
	//�����ڸ� ���� �� �ʱ�ȭ
	MyData(int data, std::string str) : number(data), strNumber(str) {}
	//Operator conversion ��ȯ������
	operator int() { return number; }
	operator std::string() { return strNumber; }

	//Unary operator
	int operator++(int) { //postfix operation (indicated by dummy 'int')
		int temp = *this;
		++*this;
		return temp;
	}
	int operator++() { //prefix operation
		number++;
		return* this;
	}

	friend std::ostream& operator<<(std::ostream&, MyData&);
};

// non-member operator<< function
std::ostream& operator<<(std::ostream& os, MyData& md) {
	return os << "This number is: " << md.strNumber << "\n";
}

int main() {
	MyData mydata(1, "one");

	//Operator conversation ���
	std::string strNum = mydata;
	int intNum = mydata;

	std::cout << strNum << std::endl; // one
	std::cout << intNum << std::endl; // 1
	std::cout << mydata++ << std::endl; // 1
	std::cout << ++mydata << std::endl; // 3
	std::cout << mydata;

}