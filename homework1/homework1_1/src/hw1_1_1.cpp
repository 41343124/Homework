#include <iostream>//���D��ackermann function�����j�Ѫk
using namespace std;
//...........................................................................
unsigned long long A(unsigned int a, unsigned int b) {//���ϥ�unsigned long long���٬O���@�w�����|�z�� ! ! !
	if (a == 0) {//��m=0��,��Xn+1
		return b + 1;
	}
	else if (b == 0) {//��n=0��,�A���I�s�禡A()�P�ɥO�ǤJ��m-1,n+1
		return A(a - 1, b + 1);
	}
	else {
		return A(a - 1, A(a, b - 1));//m�Mn��������0��,�I�s�禡A().���ѼƬ�m-1,�k�ѼƬ��禡A(m,n-1)
	}
}
//...........................................................................
void main() {
	unsigned int m, n;
	cin >> m >> n;
	cout << A(m, n);
}








