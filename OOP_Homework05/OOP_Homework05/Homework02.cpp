#include <iostream>
using namespace std;

int i;

class A {
public :
	~A() {
		i = 10;
	}
};
// return하고 난 후에 ob가 사라져서 3인체로 전달
int foo() {
	{i = 3;
	A ob; } //여기서 i가 10으로 업데이트 할 수 있게 한다.
	return i;
}
int main() {
	cout << foo() << endl;
	return 0;
}