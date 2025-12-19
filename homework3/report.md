

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
operator + : 先將多項式物件A存取入多項式物件C後利用自訂排序處理，再將多項式物件B的每個次方向帶入多項式物件C走訪相同進行相"+"運算，無相同則進行大小判斷並插入。
operator - : 先將多項式物件A存取入多項式物件C後利用自訂排序處理，再將多項式物件B的每個次方向帶入多項式物件C走訪相同進行相"-"運算，無相同則進行大小判斷並插入。
operator * : 先將多項式物件A存取入多項式物件C後利用自訂排序處理，再將多項式物件B的每個次方向帶入多項式物件C走訪相同進行相"*"運算，並帶入新的連結串列中相加，最後再進行排序。
operator / : 建立商(D)與「暫存被除式」(S)並檢查除式是否為 0，利用迴圈算出「商的一項」後把這一項變成多項式加到商裡並更新被除式回到 while，繼續除直到不能再除為止。

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

### 基礎操作效能

**1.Newnode(coef, exp)**

時間複雜度：最壞情況走訪過整條 linked list 花費 O(n)

空間複雜度：新增一個Node後並指向下一個Node 花費 O(1)

**2.void Sort()**

運作：其實Newnode()已經維持排序只有 >> 輸入才需要

時間複雜度： 花費 O(n^2) 

空間複雜度：花費 O(1)（排序）

**3.void del()**

時間複雜度： 走訪一次 linked list 花費 O(k)

空間複雜度：無額外空間 花費 O(1)

### 四則運算效能

**4.operator "+"**

時間複雜度：花費 O(n + m)

空間複雜度：花費 O(n + m) 

**5.operator "-"**

時間複雜度：花費 O(n + m)

空間複雜度：花費 O(n + m)

**6.operator "*"**

時間複雜度：乘法次數 = n * m ，最壞情況花費 O(n^2m^2)

空間複雜度：花費 O(n + m)

**7.operator "/"**

時間複雜度：蹦!!  花費 O(n^3) 大約拉

空間複雜度：O(n + m)

## 測試與驗證

| 測試案例 | A(x) | B(x) | Add | Mult | Eval | Div |
|---------|-------|-------|---| ----|----- |--------|
| 測試一  | A = 3x^2 + 2x + 1 | B = x + 1 | A + B = 3x^2 + 3x + 2  | A - B = 3x^2 + x |A * B = 3x^3 + 5x^2 + 3x + 1 |A / B = 3x - 1 |
| 測試二  | A = 5x^3 + 3x^2 + 2x + 1 | B = x - 1 | A + B = 5x^3 + 3x^2 + 3x  | A - B = 5x^3 + 3x^2 + x + 2 |A * B = 5x^4 - 2x^3 - x^2 - x - 1 |A / B = 5x^2 + 8x + 10 |
| 測試三  | A = x + 1 | B = x^3 + x + 1 | A + B = x^3 + x + 1  | A - B = -x^3 |A * B = x^4 + x^3 + x^2 + 2x + 1 |A / B = 0 |


## 心得

本次實作以 單向循環鏈結串列（header node） 來表示多項式，每一個Node儲存一個係數與指數，並透過 Newnode() 負責Node的插入、合併與刪除，這樣的設計使得多項式在進行加減乘除運算時，不需要額外處理同次方合併與零係數項，讓各運算子實作更為單純，也降低了錯誤發生的機率，並在實作過程中，我對 operator overloading 的使用時機有更深刻的理解了，透過重載 "+"、"-"、"*"、"/" 與輸入輸出運算子，使主程式閱讀性明顯提升，效能方面，本實作在加法與減法上可於線性時間完成，但乘法與除法因為使用鏈結串列搭配逐項插入，時間複雜度較高，尤其在Node增加時效能下降，這讓我理解到資料結構的選擇會直接影響演算法效率，也了解到在實務上可能需要改用其他結構（如 map 或陣列）來改善效能。

## 申論及開發報告

 **實際的分析**
 
1. **a.程式功能分析**
 
 這份程式主要設計目的：以「Linked lists」方式實作多項式（Polynomial）的：

 加法 operator "+"

 減法 operator "-"

 乘法 operator "*"

 除法 operator "/"

2.**b.問題與改進方向**
 
 在實作過程中，發現鏈結串列在插入與搜尋上的成本較高若要提升效能，可考慮以下改進方式：

 1使用 map 或 unordered_map 依指數儲存係數

 2.以陣列表示多項式，適合較密集的次方情況

 3.對乘法使用更高效的演算法（如 FFT）

 這些方式雖可改善效能，但會增加實作複雜度，需在效率與可讀性之間取捨。
 
3. **優缺點**
   優點：
   a.資料結構設計清楚。
   b.自動維持多項式有序性
   c.運算子多載提升可讀性
   d.記憶體管理完整
 
   缺點：
   a.插入成本高
   b.乘法與除法效能不佳
   c.額外指標記憶體開銷
