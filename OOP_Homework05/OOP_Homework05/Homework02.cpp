#include <iostream>
using namespace std;

int i;

class A {
public :
	~A() {
		i = 10;
	}
};
// return�ϰ� �� �Ŀ� ob�� ������� 3��ü�� ����
int foo() {
	{i = 3;
	A ob; } //���⼭ i�� 10���� ������Ʈ �� �� �ְ� �Ѵ�.
	return i;
}
int main() {
	cout << foo() << endl;
	return 0;
}