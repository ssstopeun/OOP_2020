#include <stdio.h>

int main() {
	char s[100];
	prinf("문자를 입력하세요(100자 이내).");
	scamf("%s", &s);
	printf("입력된 문자는 &s 입니다.");

	return 0;
}
