#include <iostream>// �e��:�H�U���O�D�����ۤv�[�c�X�Ӫ��������{���Ϊk�P�����W�ۦ����ëD��ŧ ! ! ! �ӷ��BGoogle �ӫD�ͦ���AI
                   // ���ѬҬ����H �|��u�G�� 41343124 �i�Z�� �е�
                   //����:�ϥα��|�Ŷ�(�f�V���v��)�ӭp��̤��h�����,�̫�b�p��~�h�����

#include <stack>//<stack> ���O�O���ت����|�禡�w EX: puch(),pop(), empty(),top(),size()......
                //�Ӱ��|�j�p���M��O����j�p�P���檺���ҭ���

using namespace std;
//...........................................................................................
unsigned long long ackermann(unsigned int a, unsigned int b) {//���ϥ�unsigned long long���٬O���@�w�����|�z��
    stack<unsigned int> A;
    A.push(a);

    while (!A.empty()) {//empty()�Ω�T�{���|�Ŷ����O�_�٦����,�L��ƥN��p�⵲��
        a = A.top();//top()�d�ݰ��|�̤W�h�����,�p�Ga�Mb��������0�ɨϥ�top()�N�̤��h��A����p���קK������~ A(m-1,A(m,n-1))
        A.pop();//�N�H�T�{�n���̤W�h��ƶǵ��Ȧs��a��N�̤W�h�屼,�p�G�Ĥ@�ӧP�_���ߧY�i��U�@�h,�����ߴN�������ư���

        if (a == 0) {//m=0,��Xn+=1
            b += 1;
        }
        else if (b == 0) {//n=0,A(m-1,n+1)
            A.push(a - 1);
            b += 1;
        }
        else {//m�Mn��������0,A(m-1,A(m,n-1))
            A.push(a - 1);//����̥~�h��A
            A.push(a);//����̤��h��A
            b = b - 1;
        }
    }
    return b;
}
//...........................................................................................
void main() {
    unsigned int m, n;
    cin >> m >> n;
    cout << ackermann(m, n);
}
