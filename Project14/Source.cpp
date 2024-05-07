#include <iostream>
#include <iomanip>
#include <queue>

class AVLNode {
public:
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};


class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* rotateLeft(AVLNode* node) {
        AVLNode* newRoot = node->right;
        AVLNode* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    AVLNode* rotateRight(AVLNode* node) {
        AVLNode* newRoot = node->left;
        AVLNode* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    AVLNode* insertNode(AVLNode* node, int key) {
        if (node == nullptr)
            return new AVLNode(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);


        if (balanceFactor > 1 && key < node->left->key)
            return rotateRight(node);


        if (balanceFactor < -1 && key > node->right->key)
            return rotateLeft(node);


        if (balanceFactor > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balanceFactor < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }

    void printLevelOrder(const AVLNode* t, unsigned shift)
    {
        if (t != nullptr)
        {
            printLevelOrder(t->right, shift + 1);  
            
            for (unsigned i = 0; i < shift; ++i) std::cout << '\t';
            std::cout << t->key << '\n';           
            printLevelOrder(t->left, shift + 1);
        }
    }
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                AVLNode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }
    void preorderTraversal(AVLNode* node) {
        if (node == nullptr)
            return;

        std::cout << node->key << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(AVLNode* node) {
        if (node == nullptr)
            return;

        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->key << " ";
    }

public:
    AVLTree() {
        root = nullptr;
    }
    void remove(int key) {
        root = deleteNode(root, key);
    }
    void insert(int key) {
        root = insertNode(root, key);
    }

    void printInorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
    void printPreorder() {
        preorderTraversal(root);
        std::cout << std::endl;
    }

    void printPostorder() {
        postorderTraversal(root);
        std::cout << std::endl;
    }
    void printTree() {
        printLevelOrder(root,0);
    }
    AVLNode* getRoot() {
		return root;
	}

};

int main() {
    AVLTree tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(40);
    tree.insert(45);
    tree.insert(50);
    tree.insert(70);
    tree.insert(65);

    std::cout << "Inorder Traversal: ";
    tree.printInorder();
    std::cout << "Preorder Traversal: ";
    tree.printPreorder();
    std::cout << "Postorder Traversal: ";
    tree.printPostorder();

    std::cout << "\nAVL Tree Structure:" << std::endl;
    tree.printTree();

    std::cout << "\nRemoving node with key 45..." << std::endl;
    tree.remove(45);

    std::cout << "\nAVL Tree Structure after removal:" << std::endl;
    tree.printTree();
    return 0;
}