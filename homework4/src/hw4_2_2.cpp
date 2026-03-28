// 四資工二甲 41343124 張豈睿
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
      

     
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }

     
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

      
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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