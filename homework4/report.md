
# 41343124

## 作業四 (Max/Min Heap & Binary Search Tree)

## 解題說明 Max/Min Heap
本題目為抽象資料型別，該抽象類別定義了一個最小優先權佇列，然後寫一個繼承自該抽象類別的 C++ 類別 MinHeap及MaxHeap作比較，主要在驗證MinHeap及MaxHeap時間複雜度。

### 解題策略
在程式選寫的過程中可以加入heap_up & heap_down 來幫助判斷節點大小以及是否需要刪除節點。
```cpp
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
```


## 程式實作

### IDE:
Microsoft Visual Studio 2019 C++

```cpp
﻿//四資工二甲 41343124 張豈睿 

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
        int index = 0;

        while (index < n) {
            int count = 1 << index; // 每層節點數 = 2^level
            cout << "Level " << level << ": ";
            for (int i = 0; i < count && index < n; i++) {
                cout << heap[index++] << " ";
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

**1.bool C(const T& a, const T& b) const**

運作：只做一次比較 (< 或 >)

時間複雜度：O(1)

**2.heap_up(int i)**

運作：每次往父節點移動 i → (i-1)/2

時間複雜度：平均情況：O(1)，最壞情況：O(log n)

**3.heap_down(int i)**

運作：每次往下一層（左或右子節點）最多走到葉節點

時間複雜度：平均情況：O(1)，最壞情況：O(log n)

**4.Push()**

運作：push_back() → O(1) heap_up() → O(log n)
時間複雜度：O(log n)

**5.Pop()**

運作：swap → O(1) pop_back → O(1) heap_down → O(log n)

時間複雜度：時間複雜度：O(log n)

**6.Top()**

運作：直接取陣列第一個元素

時間複雜度：時間複雜度：O(1)

**7.Empty()**

時間複雜度：時間複雜度：O(1)

**9.in_p(int n)**

運作：每次 Push = O(log n)

時間複雜度：時間複雜度：O(n log n)

**MinHeap 部分**
 輸入 n 個元素 → in_p(n) → O(n log n)
 印樹 → printTree() → O(n)
 Top → O(1)
 Pop → O(log n)
 再印一次 → O(n)

 O(n log n) + O(n) + O(log n) + O(n)
 ≈ O(n log n)#
 
 MaxHeap 部分（完全一樣）也是 O(n log n)
 
## 測試與驗證

<img width="1273" height="740" alt="image" src="https://github.com/user-attachments/assets/616bb9c3-2f6d-4daf-8ac7-14f47d9b2cfe" />

| 測試案例 | 組數 | 測資 | MinHeap Tree | MaxHeap Tree |
|---------|---|-------|---| ------------------------------------------------------------|
| 測試一   | 5 |  55 0 88 6 3 | Level 0: 0  Level 1: 3 88  Level 2: 55 6 | Level 0: 88  Level 1: 6 55  Level 2: 0 3 |
| 測試二   | 7 | -1 44 -5 100 51 -101 8 | Level 0: -101  Level 1: 44 -5  Level 2: 100 51 -1 8| Level 0: 100  Level 1: 51 8  Level 2: -1 44 -101 -5 |

## 心得

heap有完整且實作層面，透過自己撰寫 MinHeap 與 MaxHeap，並進一步將兩者整合成一個通用的 Heap 類別，我發現其核心差異其實只在「比較方式」，而不是整體結構，這讓我更深刻體會到抽象化與程式重用的重要性。

在實作過程中，heap_up 與 heap_down 是最關鍵的部分。一開始對於為什麼要這樣交換節點沒有完全理解，但透過插入與刪除的過程，才真正明白它們的目的是為了維持「完全二元樹」。特別是 Pop() 的（交換、刪除），讓我理解到資料結構操作其實是一種「策略設計」，而不只是單純刪除資料。

另外，使用 vector 來實作 Heap 也讓我學到如何用陣列索引來模擬樹結構（例如父節點 (i-1)/2、子節點 2i+1），這比用指標建樹更簡潔有效率。
同時，我也學到了 runtime_error 的用途，讓程式在遇到錯誤（例如空堆取值）時可以有更安全的處理方式，而不是直接崩潰。

在時間複雜度方面，透過分析 Push 和 Pop 為 O(log n)，以及整體為 O(n log n)，讓我更清楚 Heap 在效率上的優勢，也理解為什麼它常被用在優先佇列（Priority Queue）中。

整體來說，這次的實作不只是完成一個資料結構，更讓我學會：

如何將兩個類似結構（Min / Max）整合
如何分析演算法時間複雜度
如何設計更安全（例外處理）且可重用的程式

## 申論及開發報告

### 使用Heap Sort（堆排序）

1. **程式功能分析**
 
 Heap 可以直接用來做排序：

 步驟：
 建立 MaxHeap
 將最大值（根）與最後元素交換
 縮小範圍，繼續 heapify

 特點：
 時間複雜度：O(n log n)
 空間複雜度：O(1)（原地排序）

 
2. **優點**
   優點：
   更快建堆（O(n)）
   排序演算法（Heap Sort）
   優先佇列（Priority Queue）
   圖論演算法（Dijkstra、Prim）
   Top-K 問題
   即時資料分析（Median）

3. **理想推演**
   使用vector<Term> 管理記憶體、增加多項式輸入驗證、用模板（template）支援整數或複數型別等方法

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

## 解題說明 Binary Search Tree（BST）

本題分為兩部分：

### (a) BST 高度分析

建立一棵空的 Binary Search Tree，插入 n 個隨機數，並計算：

* 樹的高度（height）
* 比值：

```
height / log₂(n)
```

驗證此比值是否接近常數（約 2）。

---

### (b) 刪除節點

實作一個函式，從 BST 中刪除指定 key，並分析時間複雜度。

---

## 解題策略

### (a) 隨機建樹與高度分析

1. 使用 `rand()` 產生隨機數
2. 插入 BST
3. 使用遞迴計算高度
4. 計算：

```
height / log₂(n)
```

用來驗證 BST 平均高度 ≈ O(log n)

---

### (b) 刪除節點（核心重點）

刪除分成三種情況：

| 情況          | 說明        |
| ----------- | --------- |
|  葉節點     | 直接刪除      |
|  只有一個子節點 | 用子節點取代    |
|  兩個子節點   | 用右子樹最小值取代 |

---

## 程式實作

---

```cpp
(a) 高度分析程式
﻿//四資工二甲 41343124 張豈睿 

/*
老實說他這題拆成兩個完全相關的二元數功能完全不懂事來做什麼的
第一題要驗證第二題要單純寫一個函式那幹嘛不合併寫一個就好了
*/

#include <iostream>
#include <cmath> // 數學函式在計算log2(n)時用到
#include <cstdlib> // 一般工具函式 rand()--> 產生隨機數 srand()--> 設定亂數種子
#include <ctime> // 時間函式 time(0)--> 取得現在時間（當亂數種子用）
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node { // 定義一個「節點」的結構
    int t; // 節點存的值
    Node* L; // 左子樹
    Node* R; // 右子樹
    Node(int k) : t(k), L(nullptr), R(nullptr) {} // 建立節點並令左右節點為空
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* FF(Node* root, int t) {
    if (!root) return new Node(t); // 如果目前是空樹建立新節點
    if (t < root->t) // 如果 t 比目前節點小放左邊
        root->L = FF(root->L, t); // 遞迴往左子樹插入
    else
        root->R = FF(root->R, t); // 否則往右子樹
    return root;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HF(Node* root) { // 計算二元數高度
    if (!root) return 0; // 如果為空樹 高度 = 0
    return max(HF(root->L), HF(root->R)) + 1; // height = max(左子樹, 右子樹) + 1 
} // max 函數會挑出兩邊比較大的那個數字

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DF(Node* root) { // 釋放記憶體
    if (!root) return; // 空節點不用處理
    DF(root->L); // 先刪子節點
    DF(root->R);
    delete root; // 再刪根節點
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test(int n) { // 測試用的函式
    Node* root = nullptr; // 一開始是空樹

    for (int i = 0; i < n; i++) { // 做 n 次插入
        root = FF(root, rand()); // 插入隨機數
    }

    int h = HF(root); //計算高度
    double r = h / log2(n);

    cout << "n = " << n //印出 n
        << ", height = " << h // 印出高度
        << ", height/log2(n) = " << r << endl; // 印出比值

    DF(root); // 清掉記憶體 很重要 ! !
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    srand(time(0)); // 設定亂數種子且每次執行都不同
    test(100); // 先輸出 100 和 500
    test(500);

    for (int n = 1000; n <= 10000; n += 1000) {// 再從 1000 到 10000  ++1000
        test(n);
    }

    cout << "\n41343124.洋芋 =>防委標記";//此乃防委標記
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

(b) 刪除節點程式

// 四資工二甲 41343124 張豈睿
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // Case 1: 葉節點
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }

        // Case 2: 單子節點
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: 兩個子節點
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;

    int arr[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int x : arr)
        root = insert(root, x);

    cout << "原始 BST (inorder): ";
    inorder(root);
    cout << endl;

    int key;
    cout << "請輸入要刪除的值: ";
    cin >> key;

    root = deleteNode(root, key);

    cout << "刪除後 BST (inorder): ";
    inorder(root);
    cout << endl;

    return 0;
}
```

---

## 效能分析

### (a) 高度分析

| 操作     | 複雜度            |
| ------ | -------------- |
| 插入 n 次 | O(n log n)（平均） |
| 高度計算   | O(n)           |

---

### (b) 刪除操作

| 操作   | 複雜度  |
| ---- | ---- |
| 搜尋節點 | O(h) |
| 刪除節點 | O(h) |

 其中 h = 樹高度

* 平均：O(log n)
* 最壞：O(n)（退化成鏈結串列）

---

##  測試與驗證

### (a) 高度分析結果
測試(一)
<img width="1268" height="483" alt="image" src="https://github.com/user-attachments/assets/c5c619e4-1d59-4433-a16f-2e3c92f88246" />

測試(二)
<img width="1222" height="493" alt="image" src="https://github.com/user-attachments/assets/46051119-3a8e-456e-a092-f0bc1e58e1d2" />


```
n = 100 → ratio ≈ 2.x
n = 1000 → ratio ≈ 2.x
n = 10000 → ratio ≈ 2.x
```

符合題目「約為常數」的預期

---

### (b) 刪除測試

範例：

```
原始：20 30 40 50 60 70 80
刪除 50
結果：20 30 40 60 70 80
```

---

## 心得

本次作業讓我深入理解 Binary Search Tree 的運作原理，特別是插入與刪除節點的流程，透過隨機資料建立樹並分析高度，我觀察到 BST 在平均情況下接近 O(log n)，但在特殊情況會退化，刪除節點時三種情況的處理也讓我更加熟悉指標操作與遞迴邏輯，整體提升了我對資料結構實作與效能分析的理解。

## 申論及開發報告
這題讓我更深入理解 BST 的兩個核心重點：

### BST 的效率不穩定

* 隨機資料 → 接近 O(log n)
* 排序資料 → 最壞 O(n)

---

### 刪除操作最複雜

特別是：

* 「兩個子節點」情況
* 需要找 **中序後繼（右子樹最小值）**

---

### 實作觀念提升

* 遞迴設計
* 指標操作
* 記憶體管理（delete）

---
### 延伸

* AVL Tree（平衡 BST）
* Red-Black Tree
* Database Index
* 搜尋系統

---

## 結論

* BST 平均效率良好，但最壞情況差
* 刪除操作需特別注意三種情況
* 實務上會使用平衡樹改善效能

---

```
41343124.洋芋 => 防委標記
```
