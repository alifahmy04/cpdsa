#include <algorithm>
#include <iostream>
using namespace std;

struct Node;
int height(Node* n);
int numberOfNodes(Node* n);
void update(Node* n);
 
struct Node {
    int value;
    int height;
    int numberOfNodes;
    Node* left;
    Node* right;
 
 
    Node(int value) : 
        value(value), height(1), numberOfNodes(1), left(nullptr), right(nullptr) {}    
 
    Node(int value, Node* left, Node* right) :
        value(value), left(left), right(right) {
        update(this);
    }
};
 
int height(Node* n) {
    return n == nullptr ? 0 : n->height;
}
 
int numberOfNodes(Node* n) {
    return n == nullptr ? 0 : n->numberOfNodes;
}
 
void update(Node* n) {
    n->height = max(height(n->left), height(n->right)) + 1;
    n->numberOfNodes = numberOfNodes(n->left) + numberOfNodes(n->right) + 1;
}
 
class AVLTree {
private:
    Node* root;
 
public:
    AVLTree() : root(nullptr) {}
 
    Node* rotateLeft(Node* n) {
        if (n->right == nullptr) {
            return n;
        }
 
        Node* rightChild = n->right;
        n->right = n->right->left;
        rightChild->left = n;
        if (n == root) {
            root = rightChild;
        }
        update(n);
        update(rightChild);
        return rightChild;
    }
 
    Node* rotateRight(Node* n) {
        if (n->left == nullptr) {
            return n;
        }
 
        Node* leftChild = n->left;
        n->left = n->left->right;
        leftChild->right = n;
        if (n == root) {
            root = leftChild;
        }
        update(n);
        update(leftChild);
        return leftChild;
    }
 
    Node* balance(Node* n) {
        if (n == nullptr) {
            return nullptr;
        }
        int balanceFactor = height(n->right) - height(n->left);
        if (abs(balanceFactor) < 2) {
            return n;
        }
 
        if (balanceFactor == -2) {
            Node* leftChild = n->left;
            int leftBalanceFactor = height(leftChild->right) - height(leftChild->left);
            if (leftBalanceFactor == 1) {
                n->left = rotateLeft(n->left);
            }
            return rotateRight(n);
        } else {
            Node* rightChild = n->right;
            int rightBalanceFactor = height(rightChild->right) - height(rightChild->left);
            if (rightBalanceFactor == -1) {
                n->right = rotateRight(n->right);
            }
            return rotateLeft(n);
        }
    }
 
    Node* insert(int val, Node* currentNode) {
        if (currentNode == nullptr) {
            return new Node(val);
        }
 
        if (currentNode->value >= val) {
            currentNode->left = insert(val, currentNode->left);
        } else {
            currentNode->right = insert(val, currentNode->right);
        }
 
        update(currentNode);
        currentNode = balance(currentNode);
        return currentNode;
    }
 
    void insert(int val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
 
        insert(val, root);
    }
 
    int findMax(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        while (n->right != nullptr) {
            n = n->right;
        }
        return n->value;
    }
 
    Node* deleteVal(int val, Node* currentNode) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        if (currentNode->value > val) {
            currentNode->left = deleteVal(val, currentNode->left);
        } else if (currentNode->value < val) {
            currentNode->right = deleteVal(val, currentNode->right);
        } else {
            if (currentNode->right == nullptr) {
                Node* temp = currentNode->left;
                delete currentNode;
                return temp;
            } else if (currentNode->left == nullptr) {
                Node* temp = currentNode->right;
                delete currentNode;
                return temp;
            } else {
                int successor = findMax(currentNode->left);
                currentNode->left = deleteVal(successor, currentNode->left);
                currentNode->value = successor;
            }
        }
 
        update(currentNode);
        currentNode = balance(currentNode);
        return currentNode;
    }
 
    void deleteVal(int val) {
        if (root == nullptr) {
            return;
        }
        root = deleteVal(val, root);
    }
 
    Node* deleteIndex(int i, Node* currentNode, int carryOver) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        int currentIndex = numberOfNodes(currentNode->left) + carryOver;
        if (currentIndex > i) {
            currentNode->left = deleteIndex(i, currentNode->left, carryOver);
        } else if (currentIndex < i) {
            currentNode->right = deleteIndex(i, currentNode->right, currentIndex + 1);
        } else {
            if (currentNode->right == nullptr) {
                Node* temp = currentNode->left;
                delete currentNode;
                return temp;
            } else if (currentNode->left == nullptr) {
                Node* temp = currentNode->right;
                delete currentNode;
                return temp;
            } else {
                int successor = findMax(currentNode->left);
                currentNode->left = deleteVal(successor, currentNode->left);
                currentNode->value = successor;
            }
        }
 
        update(currentNode);
        currentNode = balance(currentNode);
        return currentNode;
    }
 
    void deleteIndex(int i) {
        int n = numberOfNodes(root);
        if (i < 0 || i >= n) {
            return;
        }
        deleteIndex(i, root, 0);
    }
 
    int get(int i) {
        int n = numberOfNodes(root);
        if (i < 0 || i >= n) {
            return INT_MIN;
        }
 
        Node* currentNode = root;
        int currentIndex;
        int carryOver = 0;
        while (currentNode != nullptr) {
            currentIndex = carryOver + numberOfNodes(currentNode->left);
            if (currentIndex == i) {
                return currentNode->value;
            } else if (currentIndex < i) {
                carryOver = currentIndex + 1;
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }
        return INT_MIN;
    }
 
    int getRank(int val) {
        Node* currentNode = root;
        int currentIndex;
        int carryOver = 0;
        while (currentNode != nullptr) {
            currentIndex = numberOfNodes(currentNode->left) + carryOver;
            if (currentNode->value < val) {
                currentNode = currentNode->right;
                carryOver = currentIndex + 1;
            } else if (currentNode->value > val) {
                currentNode = currentNode->left;
            } else {
                return currentIndex;
            }
        }
        return -1;
    }
 
    int search(int val, bool low, bool inclusive) {
        Node* currentNode = root;
        int currentValue = INT_MIN;
        while (currentNode != nullptr) {
            if (currentNode->value == val && inclusive) {
                return val;
            }
            if (currentNode->value < val && low || currentNode->value > val && !low) {
                currentValue = currentNode->value;
            }
            if (currentNode->value < val || currentNode->value == val && !low) {
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }
        return currentValue;
    }
 
    int floor(int val) {
        return search(val, true, true);
    }
 
    int lower(int val) {
        return search(val, true, false);
    }
 
    int ceil(int val) {
        return search(val, false, true);
    }
 
    int higher(int val) {
        return search(val, false, false);
    }
 
    int searchRank(int val, bool low, bool inclusive) {
        Node* currentNode = root;
        int currentIndex;
        int carryOver = 0;
        int index = -1;
        int valIndex = -1;
        while (currentNode != nullptr) {
            currentIndex = carryOver + numberOfNodes(currentNode->left);
            if (currentNode->value == val && inclusive) {
                valIndex = currentIndex;
            }
            if (currentNode->value < val && low || currentNode->value > val && !low) {
                index = currentIndex;
            }
            if (currentNode->value < val || currentNode->value == val && !low) {
                carryOver = currentIndex + 1;
                currentNode = currentNode->right;
            } else {
                currentNode = currentNode->left;
            }
        }
        if (valIndex != -1) {
            return valIndex;
        }
        return index;
    }
 
    int floorRank(int val) {
        return searchRank(val, true, true);
    }
 
    int lowerRank(int val) {
        return searchRank(val, true, false);
    }
 
    int ceilRank(int val) {
        return searchRank(val, false, true);
    }
 
    int higherRank(int val) {
        return searchRank(val, false, false);
    }
 
    void printValues(Node* n) {
        if (n == nullptr) {
            return;
        }
        printValues(n->left);
        cout << n->value << " ";
        printValues(n->right);
    }
 
    void printValues() {
        printValues(root);
        cout << '\n';
    }
};
