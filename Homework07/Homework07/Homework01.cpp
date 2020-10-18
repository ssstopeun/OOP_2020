#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class AnyString {
	std::string anyString;

public:
	AnyString(const std::string& anyString) : anyString(anyString) {}
	std::string getAnyString() {
		return "Stored String :: " + anyString;
	}
	friend ostream& operator<<(ostream& os, const AnyString& s);
};

ostream& operator<<(ostream& os, const AnyString& s) {
	os << s.anyString;
	return os;
}


int main() {
	std::ofstream out("testOveroding.txt");
	AnyString a("Hello, this is operator overloading test!!!");
//	std::string output = a.getAnyString();
	out << a << std::endl;

	return 0;
}