#include <iostream>

class MyData {
	int number;
	std::string strNumber;
public:
	//생성자를 통해 값 초기화
	MyData(int data, std::string str) : number(data), strNumber(str) {}
	//Operator conversion 변환연산자
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

	//Operator conversation 사용
	std::string strNum = mydata;
	int intNum = mydata;

	std::cout << strNum << std::endl; // one
	std::cout << intNum << std::endl; // 1
	std::cout << mydata++ << std::endl; // 1
	std::cout << ++mydata << std::endl; // 3
	std::cout << mydata;

}