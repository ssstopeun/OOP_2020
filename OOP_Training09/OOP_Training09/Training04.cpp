#include <iostream>

class Parent { //�θ�Ŭ����
    char* p;
public:
    Parent() {
        p = new char[10];
        std::cout << "Parent Constructor invocation" << std::endl; //������
    }
    virtual ~Parent() {
        delete[] p;
        std::cout << "Parent Destructor invocation" << std::endl; //�Ҹ���
    }
};
class Child : public Parent { //�θ�Ŭ������ ��ӹ��� �ڽ�Ŭ����
    char* c;
public:
    Child() : Parent() {
        c = new char[10];
        std::cout << "Child Constructor invocation" << std::endl;
    }
    ~Child() {
        delete[] c;
        std::cout << "Child Destructor invocation" << std::endl;
    }
};
int main() {
    std::cout << "--- Case1: Normal Child instantiation ---" << std::endl;
    Child* c = new Child(); //�ڽ� Ŭ���� ������
    delete c;

    std::cout << "--- Case2: Parent pointer to Child ---" << std::endl;

    Parent* p = new Child(); //�θ� Ŭ���� ������
    delete p;

    getchar();
}