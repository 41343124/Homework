
# 41343124

## 作業四 (Binary Search Tree)

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
﻿//四資工二甲 41343124 張豈睿 

/*
   這個程式可以讓使用者選擇：
   輸入 n 個數字
   建立 Tree:
   Max Heap Tree（最大樹）
   Min Heap Tree（最小樹）
   輸出方式「樹的層級」
   功能移除節點 ex. 最大/最小
   參考網站: Medium 來征服資料結構與演算法吧 ! 搞懂 Binary Heap 的排序原理
*/

#include <iostream>
#include <vector> // 提供動態陣列容器 vector，用來存放堆中的元素，大小可動態增加或縮減
#include <stdexcept> // 提供標準例外類別 runtime_error，用來在程式中報錯（例如空堆呼叫 Top()）
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Heap { // 建立Heap 類別
private:
    vector<T> heap;
    bool V1; // true = MinHeap, false = MaxHeap（可選 MinHeap 或 MaxHeap）

    bool C(const T& a, const T& b) const { // 比較大小並判斷使用哪種樹 ?
        return V1 ? a < b : a > b; // '<' 時使用最小樹 ，'>' 時使用最大樹
    }

    void heap_up(int i) { // 當新元素加入時，用 heap_up函式計算父節點並判斷是否要向上交換
        while (i > 0) {
            int p = (i - 1) / 2; // 計算父節點在 vector 中的索引
            if (C(heap[i], heap[p])) { // 使用 C函式判斷是否需要交換
                swap(heap[i], heap[p]); // 交換
                i = p;
            }
            else break; // 不須交換就退出整個迴圈
        }
    }

    void heap_down(int i) { // 當頂元素被刪除時，用 heap_down函式判斷是否需要向下調整。
        int size = heap.size(); // 取得的總元素數量，用於判斷左右子節點是否存在
        while (2 * i + 1 < size) { // 判斷當前節點 index 是否有子節點
            int L = 2 * i + 1; // 左子節點索引
            int R = 2 * i + 2; // 右子節點索引
            int t = L; // 暫時假設要交換的是左子節點，後面再比較右子節點

            if (R < size && C(heap[R], heap[L])) // 如果子節點比父節點更符合就交換
                t = R;

            if (C(heap[t], heap[i])) { // 使用 C函式判斷是否需要交換
                swap(heap[t], heap[i]);
                i = t;
            }
            else break; // 不須交換就退出整個迴圈
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    Heap(bool V2 = true) : V1(V2) {} // 預設為 true--> Min 如果傳入 false--> Max

    bool Empty() const {
        return heap.empty(); // 判斷堆是否為空
    }

    const T& Top() const {
        if (Empty()) // 回傳根節點（最小/最大元素），空堆會丟出例外
            throw runtime_error("Heap is empty!"); // 無意間想到如果內容為空拋出是否會有錯誤，所以就找到了這個東西
        return heap[0]; // runtime_error--> 例外拋出
    }

    void Push(const T& value) {
        heap.push_back(value); // 加入新元素
        heap_up(heap.size() - 1); // 判斷是否有大於父節點
    }

    void Pop() {
        if (Empty()) { // 判斷是否為空
            throw runtime_error("Heap is empty!"); // 空堆會丟出例外
        }
        swap(heap[0], heap.back()); // 把根節點和最後一個元素互換
        heap.pop_back(); // pop_back() 會把 vector 最後一個元素移除
        if (!Empty()) // 如果是空的，就不用調整
            heap_down(0);
    }

    void in_p(int n) { // 輸入建樹
        T x;
        for (int i = 0; i < n; i++) {
            cin >> x;
            Push(x);
        }
    }

    void printTree() { // 樹狀層層輸出
        int n = heap.size();
        int level = 0;
        int i = 0;

        while (index < n) {
            int count = 1 << i; // 每層節點數 = 2^level
            cout << "Level " << level << ": ";
            for (int i = 0; i < count && i < n; i++) {
                cout << heap[i++] << " ";
            }
            cout << endl;
            level++;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    int n;

    cout << "請輸入測資組數: ";
    cin >> n;

    Heap<int> minH(true); // true = MinHeap
    cout << "請輸入" << n << "個測資數 (MinHeap):\n";
    minH.in_p(n);

    cout << "\nMinHeap Tree:\n";
    minH.printTree();
    cout << "\n最小元素: " << minH.Top() << endl;
    minH.Pop();
    cout << "刪除最小元素後的樹:\n";
    minH.printTree();

    Heap<int> maxH(false); // false = MaxHeap
    cout << "\n請輸入" << n << "個測資數 (MaxHeap):\n";
    maxH.in_p(n);

    cout << "\nMaxHeap Tree:\n";
    maxH.printTree();
    cout << "\n最大元素: " << maxH.Top() << endl;
    maxH.Pop();
    cout << "刪除最大元素後的樹:\n";
    maxH.printTree();

    cout << "\n41343124.洋芋 =>防委標記";//此乃防委標記
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
