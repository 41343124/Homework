//四資工二甲 41343124 張豈睿 

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

        while (i < n) {
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
