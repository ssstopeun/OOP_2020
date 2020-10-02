#include <iostream>
using namespace std;

int i;

class A {
public:
	~A() {
		i = 10;
	}
};
int foo() {
	i = 3;
	A ob;
	return i;
}
int main() {
	cout << foo() << endl; //위에 namespace때문에 cout로 바로 시작 가능
	return 0;
}