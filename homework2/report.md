
# 41343124

## 作業二 (Polynomial)

## 解題說明

本題目為運用多項式(Polynomial)來進行四維運算中的加法以及乘法，其中會用到algorithm及cmath這兩個標頭檔。

1.```<algorithm>``` 這個標頭檔提供大量常用的演算法函式，但在這個題目中只會用到sort()排序，主要適用於在輸入兩個多項式以及合併前最後輸出等使用。

2.```<cmath>``` 這個標頭檔是 C++ 數學函式庫，包含各種數學運算函式，題目中用於多項式的 Eval() 函式，計算 pow(x, exp)。

### 解題策略

最開始會以讓使用者輸入兩多項後，進行istream and ostream運算子的運作，至於為什麼要用到輸入輸出運算子多載呢?因為這兩個運算子原本只認得內建型別，可是如果你想要直接對「自訂類別」輸入或輸出（Polynomial）就不知道要怎麼印，所以使用運算子多載來告知編譯器，再來進行運算子輸入的合併(有可能有相同指數)以及排序，最後將兩多項式進行四則運算以及帶入參數，在運算過程中的每個獨立指數項都會帶入動態記憶體termArray中，且必須時刻判斷空間是否不足，不足時要進行記憶體擴充，方法會以2的N次方倍增加。

加法運算:將兩排序後多項式判斷是否有相同項進行合併並排序

乘法運算:把兩排序後多項式每一項常數項以及指數項相乘並傳入新多項式空間進行合併並排序

輸出:若係數為 -1 且次方 !=0，顯示 "-" 不顯示 1，非-1 且次方 !=0，顯示的顯示 "-" 以及絕對值後的常數項，次方項=0，顯示的顯示 "0"

## 程式實作

### IDE:
Microsoft Visual Studio 2019 C++

```cpp
//41343124 四資工二甲 張豈睿
#include <iostream>//此題目為運用多項式(Polynomial)來進行四維運算中的加法以及乘法。
#include <algorithm>//這個標頭檔提供大量常用的演算法函式，但在這個題目中只會用到sort()排序。
#include <cmath>//這個標頭檔是 C++ 數學函式庫，包含各種數學運算函式，題目中用於多項式的 Eval() 函式，計算 pow(x, exp)。
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Term {// Term 類別
    friend class Polynomial;//將Polynomial加入友誼類別就能使用Polynomial類別的私有項內容了
public:
    float coef;//常數項變數
    int exp;//指數項變數
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}//紀錄Polynomial的常數及指數
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Polynomial {// Polynomial 類別
private:
    Term* termArray;//記錄點記憶體
    int capacity;//記憶體的空間小記錄點
    int terms;//儲存非零項變數

    void NewArray(int n1) {  // 如果需要，擴增容量
        if (n1 <= capacity) return;//判斷記憶體空間是否足夠
        int n2 = capacity;//不足時將現在的空間大小存起來
        while (n2 < n1) n2 *= 2;//並加兩倍的空間，概念2的N次方倍增加
        Term* n3 = new Term[n2];//建立新的記憶體空間
        for (int i = 0; i < terms; ++i) n3[i] = termArray[i];//並將現在的空間內容轉移
        delete[] termArray;//刪除原本的記憶體
        termArray = n3;/////////////////////////////////注意!! 此時已刪除原本指標項的記憶體，需要重新指項新的記憶體空間
        capacity = n2;//傳入新的空間大小
    }

    void addTerm(const Term& t) {//與STerm大致相同但此函式是專門判斷Term資料型態的而非初始輸入coef及exp，用於 Mult 以及 add
        if (t.coef == 0) return;
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == t.exp) {
                termArray[i].coef += t.coef;
                return;
            }
        }
        NewArray(terms + 1);
        termArray[terms++] = t;
    }

    void Sort() { // 依次方由大到小排序，並移除係數為 0 的項，合併可能重複的次方（簡單做法：先排序再合併）
        sort(termArray, termArray + terms, [](const Term& a, const Term& b) {//sort(起始位置, 結束位置, 比較函式)，這是一個 lambda 表達式
            return a.exp > b.exp; // 從高次到低次
            });
        int c = 0;//記錄點
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].coef == 0) continue;//乎略係數為 0 的項
            if (c > 0 && termArray[c - 1].exp == termArray[i].exp) {//判斷指數項是否相同
                termArray[c - 1].coef += termArray[i].coef; // 相同的話合併
            }
            else {
                termArray[c++] = termArray[i];//不相同的話就紀錄並讓c+1
            }
        }
        terms = c;//更新記錄點
        c = 0;//重新紀錄常數非零項
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].coef != 0) termArray[c++] = termArray[i];//只紀錄常數非零項
        }
        terms = c;//更新記錄點
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    Polynomial(int n = 2) {//如果使用者傳入的容量太小（小於 2），系統仍會確保至少有 2 的預設大小
        capacity = max(2, n);//取「2」和「n」之中較大的那個作為容量
        termArray = new Term[capacity];// 建立記憶體
        terms = 0;// 清掉原有內容以免有殘值
    }

    Polynomial(const Polynomial& n) {//複製一份多項式以做比較
        capacity = n.capacity;
        terms = n.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) termArray[i] = n.termArray[i];
    }

    Polynomial& operator=(const Polynomial& n) {//這個函式會把原本的資料n完整複製，但由於有指標成員（termArray），不能使用直接拷貝否則兩個物件會共用同一塊記憶體，會造成記憶體錯誤
        if (this == &n) return *this;
        delete[] termArray;
        capacity = n.capacity;
        terms = n.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) termArray[i] = n.termArray[i];
        return *this;
    }

    ~Polynomial() {//Polynomial解構子
        delete[] termArray;//程式執行完的最後解除記憶體動態配置以免異常
    }

    void STerm(float coef, int exp) {// 將使用者輸入的項加入（會合併相同次方）
        if (coef == 0) return; // 常數項等於"0"直接忽略 
        for (int i = 0; i < terms; ++i) {//判斷記憶體陣列(termArray)中是否有相同的指數項
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;//有的話直接合併
                return;//並結束
            }
        }
        NewArray(terms + 1);//沒有的話檢查記憶體空間，傳入目前空間加一的大小加以判斷
        termArray[terms++] = Term(coef, exp);//並將常數跟指數加入記憶體
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Polynomial Add(const Polynomial& n) const {//多項式加法
        Polynomial a;// 把兩邊的項插入 a（addTerm 會合併相同次方）
        for (int i = 0; i < terms; ++i) a.addTerm(termArray[i]);//多項式一合併
        for (int j = 0; j < n.terms; ++j) a.addTerm(n.termArray[j]);//多項式二合併
        a.Sort();//排序
        return a;
    }

    Polynomial Mult(const Polynomial& n) const {//多項式乘法
        Polynomial p;// 把兩多項式每一項常數項以及指數項相乘並傳入新多項式空間 t（addTerm 會合併相同次方）
        for (int i = 0; i < terms; ++i) {//多項式一第一項開始
            for (int j = 0; j < n.terms; ++j) {//多項式二頭到尾項
                Term t(termArray[i].coef * n.termArray[j].coef, termArray[i].exp + n.termArray[j].exp);
                p.addTerm(t);//新多項式合併
            }
        }
        p.Sort();//排序
        return p;
    }

    float Eval(float f) const {
        float sum = 0;
        for (int i = 0; i < terms; ++i) {
            sum += termArray[i].coef * powf(f, termArray[i].exp);
        }
        return sum;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       //為什麼要用到輸入輸出運算子多載呢?
       //這兩個運算子原本只認得內建型別，可是如果你想要直接對「自訂類別」輸入或輸出（Polynomial）就不知道要怎麼印，所以使用運算子多載來告知編譯器

    friend istream& operator>>(istream& a, Polynomial& pin) {// 輸入操作令運算子多載：cin >> p;
        pin.terms = 0;// 清掉原有內容以免有殘值
        cout << "請輸入多項式個數: ";
        int n;
        a >> n;
        cout << "請輸入多項式測資, EX. 3 2  輸出: 3x^2\n";
        for (int i = 0; i < n; ++i) {
            float c; int e;//常數以及指數項
            a >> c >> e;
            pin.STerm(c, e); // STerm 會將相同的指數項進行常數項合併
        }
        pin.Sort();//Sort會將termArray記憶體內容排序
        return a;
    }

    friend ostream& operator<<(ostream& t, const Polynomial& pin) {// 輸出操作令運算子多載：cout << t;
        if (pin.terms == 0) {//多項式只有零只需輸出零
            t << "0";
            return t;
        }
        for (int i = 0; i < pin.terms; ++i) {
            float c = pin.termArray[i].coef;//指派經過排序後的常數項
            int e = pin.termArray[i].exp;//所對應的指數項
            if (i == 0) {//判斷第一項，若係數為 -1 且次方 !=0，顯示 "-" 不顯示 1
                if (c == -1 && e != 0) t << "-";
                else if (c != 1 || e == 0) t << c;
            }
            else {
                if (c < 0) {//若係數為 -1 且次方 !=0，顯示 "-" 不顯示 1
                    if (c == -1 && e != 0) t << " - ";
                    else t << " - " << fabs(c);//以外的顯示 "-" 以及絕對值後的常數項
                }
                else {
                    if (c == 1 && e != 0) t << " + ";//若係數為 + 且次方 !=0，顯示 "+" 以及常數項
                    else t << " + " << c;
                }
            }
            if (e != 0) {// 判斷次方是否為零
                if (!(i == 0 && (c == -1))) t << "x";//常數項不等於-1且不是第一項就輸出一個未知數"x"
                if (e != 1) t << "^" << e;//次方項不等於1就輸出一個"^"表示次方位
            }
        }
        return t;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    Polynomial p1, p2;//宣告兩個多項式
    cout << "輸入第一個多項式\n";
    cin >> p1;//呼叫 istream
    cout << "輸入第二個多項式\n";
    cin >> p2;//呼叫 istream

    // 顯示兩個多項式
    cout << "\nP1(x) = " << p1 << "\n";//第一項
    cout << "P2(x) = " << p2 << "\n";//第二項

    // 相加與相乘結果所對應的結果
    Polynomial s = p1.Add(p2);
    cout << "\nP1 + P2 = " << s << "\n";//加法多項式
    Polynomial p = p1.Mult(p2);
    cout << "P1 * P2 = " << p << "\n";//乘法多項式

    float x; // 代入 x 計算多項式後的總結果
    cout << "\n請輸入要代入的 x 值：";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;//多項式 P1(X)
    cout << "P2(" << x << ") = " << p2.Eval(x) << endl;//多項式 P2(X)

    return 0;//執行結束回傳0
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


### 結論

1. 僅管使用了堆疊以及unsigned long long但還是有一定的機會爆掉。
2. 程式所能執行的範圍大約在 m=4,n=1以上時就無法執行了不管是遞迴或是非遞迴，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$m = 0$、$ m和n不等於0 $），等驗證程式的正確性。

## 申論及開發報告

### 選擇堆疊的原因

1. **程式碼邏輯簡單**  
   Stack的寫法相當於自己管理堆疊且空間計算上能以最內層的資料計算最後在計算外層的資料避免執行錯誤。  
   例如：  
      empty()用於確認堆疊空間內是否還有資料,無資料代表計算結束。
      top()查看堆疊最上層的資料,如果a和b接不等於0時使用top()將最內層的A先行計算。
      m和n接不等於0的話:
        A.push(a - 1);//先放最外層的A
        A.push(a);//先算最內層的A
        b = b - 1;

2. **推疊的分析**  
   堆疊演算法（Stack） 是一種有序串列（即一群相同資料型態的組合），具有「後進先出」（Last In First Out, LIFO）的特性,故其所有的動作、資料的處理方式均在同一邊進行,
   同時實現了在大量測資運行時避免使用遞迴空間的浪費空間,而是把所有側資放放在同一個空間中。
   
3. **優缺點**
   優點：
   不用系統遞迴呼叫，因此可處理較大參數。
   控制流程更靈活。
 
   缺點：
   寫法較複雜。
   若數值太大,堆疊大小仍可能不足。

4. **理想推演**
   雖然每總解法都大同小異但在時間與空間的限制下要實現是有一定的複雜但下列這些方法是我找到有趣的解法之一 ! !
   1.利用「已知規律」或「特殊情況」進行公式化。
   2.include <map> 。
   3.鏈結串列節省空間。
