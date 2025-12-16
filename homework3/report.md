

# 41343124

## 作業三 (Linked lists representation Polynomials)

## 前言

首先我認真覺得把一個程式拆成多個名詞來表示成題目真的是吃飽撐著，比如Chain/ChainNode等不用特別標示出來吧 !!
因為題目就是用Linked lists去實作Polynomial啊，不如說是逼你把裡面的函式名稱限制的如此軍事化那不就大家的程式都長得差不多了嗎 ??

## 解題說明

本題是使用Linked lists來實作Polynomial的題目同時解決Polynomial本身會因為預設空間不足所導致的呼叫還是擴充的問題，
而題目有要求實作出(加、減、乘、除)的四則運算但除法會有餘數問題所以必須多寫一個餘數的樣本函式非常靠杯，然後題目體面的
Chain()/ChainNode()......等到底是來做什麼的我也不知道但因為沒有特別要求要做什麼我也就沒有特別輸出了，反正我的程式裡
有差不多的功能有特別標示名稱。

### 解題策略

最開始會以讓使用者輸入兩多項後，接著進行運算子多載的運作，至於為什麼要用到輸入輸出運算子多載呢??因為這兩個運算子原本只認得內建型別，可是如果你想要直接對「自訂類別」輸入或輸出（Polynomial）就不知道要怎麼印，所以使用運算子多載來告知編譯，器最後先將多項式物件A帶入多項式物件C後，再將多項式物件B帶入進行四則運算，在運算過程中的每個獨立指數項都會帶入C物件的每個Node中判斷，且不必擔心空間是否不足。

void Sort(): 運算子輸入可能為錯誤排序，所以需要針對Node做排序的工作，注意!!不可使用內建的因為Sort()只能對隨機存取的容器（如 vector, array）使用但鏈結串列只能順序存取 → 無法用內建排序。
void del(): 刪除所有Node。
void Newnode(T coef, int exp):是 Polynomial 類別裡用來新增或合併多項式項目的函式功能是「把一個係數和指數的項加入到多項式中」，同時維持鏈結串列的降冪順序(大到小的意思啦)。

四則運算:
operator + :
operator - :
operator * :
operator / :

## 程式實作

### IDE:
Microsoft Visual Studio 2019 C++

```cpp
//41343124 四資工二甲 張豈睿
#include <iostream>
using namespace std;

template <class T> class Polynomial;
template <class T>
class Node {  //----------------------這個是ChainNode但我比較想叫Node
    friend class Polynomial<T>;
public:
    int exp;
    T coef;
    Node<T>* link;
    Node(T c = 0, int e = 0, Node<T>* p = nullptr)
        : coef(c), exp(e), link(p) {}
};

////////////////////////////////////////////////////////////////

template <class T>
class Polynomial {
private:
    Node<T>* head;

public:
    Polynomial();
    Polynomial(const Polynomial<T>& a);
    Polynomial<T>& operator=(const Polynomial<T>& a);
    Polynomial<T> operator+(const Polynomial<T>& b) const;
    Polynomial<T> operator-(const Polynomial<T>& b) const;
    Polynomial<T> operator*(const Polynomial<T>& b) const;
    Polynomial<T> operator/(const Polynomial<T>& b) const;
    Polynomial<T> R(const Polynomial<T>& b) const;
    void Newnode(T coef, int exp);
    void del();
    void Sort(); 
    ~Polynomial();

    friend istream& operator>>(istream& in, Polynomial<T>& x) {
        int n;
        in >> n;
        for (int i = 0; i < n; i++) {
            T coef;
            int exp;
            in >> coef >> exp;
            x.Newnode(coef, exp);
        }
        x.Sort(); 
        return in;
    }

    friend ostream& operator<<(ostream& out, const Polynomial<T>& x) {
        Node<T>* p = x.head->link;
        bool first = true;

        while (p != x.head) {
            T c = p->coef;
            int e = p->exp;
            if (!first) {
                if (c > 0) out << " + ";
                else       out << " - ";
            }
            else {
                if (c < 0) out << "-";
            }

            T absCoef = (c < 0) ? -c : c;
            if (e == 0) {
                out << absCoef;
            }
            else {
                if (absCoef != 1)
                    out << absCoef;
                out << "x";
                if (e != 1)
                    out << "^" << e;
            }

            first = false;
            p = p->link;
        }
        if (first)
            out << "0";

        return out;
    }
};

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::Polynomial() {
    head = new Node<T>();
    head->link = head;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::Polynomial(const Polynomial<T>& a) {
    head = new Node<T>();
    head->link = head;
    Node<T>* p = a.head->link;
    while (p != a.head) {
        Newnode(p->coef, p->exp);
        p = p->link;
    }
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& a) {
    if (this == &a) return *this;
    del();
    Node<T>* p = a.head->link;
    while (p != a.head) {
        Newnode(p->coef, p->exp);
        p = p->link;
    }
    return *this;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T>::~Polynomial() {
    del();
    delete head;
}

////////////////////////////////////////////////////////////////
template <class T>
void Polynomial<T>::del() {
    Node<T>* p = head->link;
    while (p != head) {
        Node<T>* t = p;
        p = p->link;
        delete t;
    }
    head->link = head;
}

////////////////////////////////////////////////////////////////
template <class T>
void Polynomial<T>::Newnode(T coef, int exp) { //----------------------這個是ChainIterator但我比較想叫Newnode
    if (coef == 0) return;

    Node<T>* p = head;
    Node<T>* q = head->link;

    while (q != head && q->exp > exp) {
        p = q;
        q = q->link;
    }

    if (q != head && q->exp == exp) {
        q->coef += coef;
        if (q->coef == 0) {
            p->link = q->link;
            delete q;
        }
        return;
    }

    p->link = new Node<T>(coef, exp, q);
}

////////////////////////////////////////////////////////////////
template <class T>
void Polynomial<T>::Sort() {
    if (head->link == head || head->link->link == head) return;

    bool swapped;
    do {
        swapped = false;
        Node<T>* p = head->link;
        while (p->link != head) {
            if (p->exp < p->link->exp) { 
                swap(p->coef, p->link->coef);
                swap(p->exp, p->link->exp);
                swapped = true;
            }
            p = p->link;
        }
    } while (swapped);
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
    Polynomial<T> c;
    Node<T>* p = head->link;
    Node<T>* q = b.head->link;

    while (p != head && q != b.head) {
        if (p->exp == q->exp) {
            c.Newnode(p->coef + q->coef, p->exp);
            p = p->link;
            q = q->link;
        }
        else if (p->exp > q->exp) {
            c.Newnode(p->coef, p->exp);
            p = p->link;
        }
        else {
            c.Newnode(q->coef, q->exp);
            q = q->link;
        }
    }

    while (p != head) {
        c.Newnode(p->coef, p->exp);
        p = p->link;
    }
    while (q != b.head) {
        c.Newnode(q->coef, q->exp);
        q = q->link;
    }

    return c;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& b) const {
    Polynomial<T> c;
    Node<T>* p = head->link;
    Node<T>* q = b.head->link;

    while (p != head && q != b.head) {
        if (p->exp == q->exp) {
            c.Newnode(p->coef - q->coef, p->exp);
            p = p->link;
            q = q->link;
        }
        else if (p->exp > q->exp) {
            c.Newnode(p->coef, p->exp);
            p = p->link;
        }
        else {
            c.Newnode(-q->coef, q->exp);
            q = q->link;
        }
    }

    while (p != head) {
        c.Newnode(p->coef, p->exp);
        p = p->link;
    }
    while (q != b.head) {
        c.Newnode(-q->coef, q->exp);
        q = q->link;
    }

    return c;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& b) const {
    Polynomial<T> c;
    for (Node<T>* p = head->link; p != head; p = p->link) {
        for (Node<T>* q = b.head->link; q != b.head; q = q->link) {
            c.Newnode(p->coef * q->coef, p->exp + q->exp);
        }
    }
    return c;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::operator/(const Polynomial<T>& b) const {
    Polynomial<T> D, S(*this);

    if (b.head->link == b.head) {
        return D;
    }

    Node<T>* bLead = b.head->link;

    while (S.head->link != S.head &&
        S.head->link->exp >= bLead->exp) {

        T coef = S.head->link->coef / bLead->coef;
        int exp = S.head->link->exp - bLead->exp;

        Polynomial<T> term;
        term.Newnode(coef, exp);

        D = D + term;
        S = S - (term * b);
    }

    return D;
}

////////////////////////////////////////////////////////////////
template <class T>
Polynomial<T> Polynomial<T>::R(const Polynomial<T>& b) const {
    Polynomial<T> S(*this);

    if (b.head->link == b.head)
        return S;

    Node<T>* bLead = b.head->link;

    while (S.head->link != S.head &&
        S.head->link->exp >= bLead->exp) {

        T coef = S.head->link->coef / bLead->coef;
        int exp = S.head->link->exp - bLead->exp;

        Polynomial<T> term;
        term.Newnode(coef, exp);

        S = S - (term * b);
    }

    return S;
}

////////////////////////////////////////////////////////////////
int main() {
    Polynomial<int> A, B;

    cin >> A;
    cin >> B;

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    cout << "A + B: " << (A + B) << endl;
    cout << "A - B: " << (A - B) << endl;
    cout << "A * B: " << (A * B) << endl;

    Polynomial<int> D = A / B;
    Polynomial<int> S = A.R(B);

    cout << "A / B = " << D << endl;
    cout << "A % B = " << S << endl;

    cout << "41343124.洋芋";//此乃防委標記
    return 0;
}
```

## 效能分析

**1.void Sort()**

運作：sort()：O(t log t)合併重複次方與移除 0 項：O(t)

時間複雜度：O(t log t)

空間複雜度：O(1)（就地排序）

**2.void STerm(float coef, int exp)**

運作：用線性搜尋判斷是否已有相同次方（O(terms)）若沒有，插入新項（O(1)），若空間不足時呼叫 NewArray()（可能觸發 O(terms) 的搬移）

時間複雜度：平均情況：O(t)，最壞情況（空間擴充）：O(t)

空間複雜度：O(t)（動態陣列）

**3.Polynomial Add(const Polynomial& n) const**

運作：對兩個多項式的每一項呼叫 addTerm()本身需要線性搜尋 (O(t))，所以總共約有：
O(m * (平均搜尋長度)) + O(n * (平均搜尋長度))≈ O(m^2 + n^2)（若項數接近）最後呼叫 Sort()（O(t log t)）

時間複雜度：
𝑂((𝑚+𝑛)^2)

空間複雜度：
O(m + n)（儲存結果多項式）

**4.Polynomial Mult(const Polynomial& n) const**

運作：雙層迴圈 m × n 次相乘（O(m·n)，每次乘積都呼叫 addTerm()（線性搜尋，O(t)，若結果多項式項數接近 m·n，則：
O(m*n * t) ≈ O(m^2 * n^2) 最壞情況，最後 Sort()：O(t log t)

時間複雜度：平均情況：O(m·n·t) ≈ O(m² n²) 最壞情況，若合併有效（少重複次方）約 O(m·n)

空間複雜度：
O(m + n + m·n)（儲存中間結果）

**5.float Eval(float f) const**

運作：單一迴圈，計算每項 coef * powf(x, exp)，而 powf() 通常為 O(1)（硬體或快速冪），因此整體線性。

時間複雜度：O(t)

空間複雜度：O(1)

## 測試與驗證

| 測試案例 | P1(x) | P2(x) | x | Add | Mult | Eval |
|---------|-------|-------|---| ----|----- |--------|
| 測試一   | 3x^2 |  x^2 | 1       | P1 + P2 =4x^2 |P1 * P2 =3x^4 |P1(1) = 3 ,P2(1) = 1 |
| 測試二   | -x^2 + 3x + 2 | -2x^2 + x| 2        | P1 + P2 = -3x^2 + 4x + 2 |P1 * P2 = 2x^4 - 7x^3 - x^2 + 2x |P1(2) = 4 ,P2(2) = -6 |
| 測試三   | x^9999 | 0        | 1        | P1 + P2 = x^9999 |P1 * P2 = 0|P1(1) = 1,P2(1) = 0 |


## 心得

1. 在記憶體管理的過程中發現了手動 new、delete、擴充容量、複製建構子、解構子的重要性，整個流程是以 C++「動態記憶體」為核心的控制，且將來寫大型專案或考試遇到考「深拷貝 / 淺拷貝」，時也將不是問題這程式的結構就是經典範例，而在解決四則運算的同時擴充記憶體其實是一個非常好用的方法，因為在不知道最終結果需求空間時可以隨時分配空間，在分配的時候會運用到```<algorithm>``` 中的sort()排序以免在最後空間浪費的情況發生。

## 申論及開發報告

### 使用物件導向運算子負載及動態記憶體控制

1. **實際的分析**
 
 **a.程式功能分析**
 
 這份程式主要設計目的：以「物件導向」方式實作多項式（Polynomial）的：

 加法（Add()）

 乘法（Mult()）

 求值（Eval()）

 輸入與輸出（operator>>、operator<<）

 程式透過 Term 類別記錄每一項（係數與指數），Polynomial 類別則用 Term* termArray 動態儲存整個多項式。

 **b.執行流程分析**
 
 物件建立與輸入建立 Polynomial 物件 → 配置記憶體（capacity 預設至少 2）使用者輸入多項式的項數與 (coef, exp) 將每一項插入，若遇到同次項會直接合併

 **c.可維護性與擴充性分析**
|項目|	分析| 
|---------|-------|
|可讀性	高|註解完整、結構清楚|
|可維護性	中等|有重複邏輯（STerm/addTerm/Sort）|
|擴充性	|可加入 Sub()、Div()、Derivative()|
|可攜性	良好| C++ 寫法|
|模組化適中|可將 Term 改為 struct 並放外部檔案|


   
2. **優缺點**
   優點：
   提高記憶體空間配置以免浪費。
   使用直接自訂結構輸入輸出以增加可讀性。
 
   缺點：
   寫法較複雜。
   用乘法的部分消耗太多處理時間。

3. **理想推演**
   使用vector<Term> 管理記憶體、增加多項式輸入驗證、用模板（template）支援整數或複數型別等方法

