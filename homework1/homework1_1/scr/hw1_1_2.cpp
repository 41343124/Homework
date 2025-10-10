#include <iostream>// 前言:以下指令非完全自己架構出來的有部分程式用法與網路上相似但並非抄襲 ! ! ! 來源處Google 而非生成式AI
                   // 註解皆為本人 四資工二甲 41343124 張豈睿 標註
                   //概念:使用推疊空間(逆向撥洋蔥)來計算最內層的資料,最後在計算外層的資料

#include <stack>//<stack> 指令是內建的堆疊函式庫 EX: puch(),pop(), empty(),top(),size()......
                //而堆疊大小取決於記憶體大小與執行的環境限制

using namespace std;
//...........................................................................................
unsigned long long ackermann(unsigned int a, unsigned int b) {//雖使用unsigned long long但還是有一定的機會爆掉
    stack<unsigned int> A;
    A.push(a);

    while (!A.empty()) {//empty()用於確認堆疊空間內是否還有資料,無資料代表計算結束
        a = A.top();//top()查看堆疊最上層的資料,如果a和b接不等於0時使用top()將最內層的A先行計算避免執行錯誤 A(m-1,A(m,n-1))
        A.pop();//將以確認好的最上層資料傳給暫存器a後將最上層砍掉,如果第一個判斷成立即可算下一層,不成立就必須重複執行

        if (a == 0) {//m=0,輸出n+=1
            b += 1;
        }
        else if (b == 0) {//n=0,A(m-1,n+1)
            A.push(a - 1);
            b += 1;
        }
        else {//m和n接不等於0,A(m-1,A(m,n-1))
            A.push(a - 1);//先放最外層的A
            A.push(a);//先算最內層的A
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
