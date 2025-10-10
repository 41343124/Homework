#include <iostream>//此題為ackermann function的遞迴解法
using namespace std;
//...........................................................................
unsigned long long A(unsigned int a, unsigned int b) {//雖使用unsigned long long但還是有一定的機會爆掉 ! ! !
	if (a == 0) {//當m=0時,輸出n+1
		return b + 1;
	}
	else if (b == 0) {//當n=0時,再次呼叫函式A()同時令傳入的m-1,n+1
		return A(a - 1, b + 1);
	}
	else {
		return A(a - 1, A(a, b - 1));//m和n接不等於0時,呼叫函式A().左參數為m-1,右參數為函式A(m,n-1)
	}
}
//...........................................................................
void main() {
	unsigned int m, n;
	cin >> m >> n;
	cout << A(m, n);
}








