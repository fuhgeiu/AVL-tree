#include <iostream>
#include <string>
#include <sstream>
#include <queue>

namespace Tree {


class Treenode {
public:

    int value;

    Tree::Treenode* left;
    Tree::Treenode* right;

    int height;

    Treenode () = default;

    Treenode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};



class AVLTree {

    Tree::Treenode* root;

    int getHeight(Treenode* node) {return node == nullptr ? 0 : node->height;}

    int getBalanceFactor(Treenode* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }


    Tree::Treenode* rotateRight(Tree::Treenode* y) {

        Tree::Treenode* x = y->left;
        Tree::Treenode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Tree::Treenode* rotateLeft(Tree::Treenode* x) {

        Tree::Treenode* y = x->right;
        Tree::Treenode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Tree::Treenode* rebalance(Tree::Treenode* node) {

        int balance = getBalanceFactor(node);

        if (balance > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balance < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Tree::Treenode* insert(Tree::Treenode* node, int value) {

        if (node == nullptr)
            return new Tree::Treenode(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

        return rebalance(node);
    }

    Tree::Treenode* minNode(Tree::Treenode* node) {
        Tree::Treenode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Tree::Treenode* deleteNode(Tree::Treenode* root, int value) {

        if (root == nullptr) return root;

        if (value < root->value) root->left = deleteNode(root->left, value);
        else if (value > root->value) root->right = deleteNode(root->right, value);

        else {

            if (root->left == nullptr) return root->right;

            else if (root->right == nullptr) return root->left;

            Tree::Treenode* temp = minNode(root->right);

            root->value = temp->value;

            root->right = deleteNode(root->right, temp->value);
        }

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

        return rebalance(root);
        }

    void serializeHelper(Tree::Treenode* node, std::stringstream& ss) {

        if (node == nullptr) {
            ss << "null,";
            return;
        }

        ss << node->value << ",";
        serializeHelper(node->left, ss);
        serializeHelper(node->right, ss);
    }

    Tree::Treenode* deserializeHelper(std::queue<std::string>& q) {

        if (q.empty()) return nullptr;

        std::string val = q.front();
        q.pop();

        if (val == "null") return nullptr;

        Tree::Treenode* node = new Tree::Treenode(std::stoi(val));

        node->left = deserializeHelper(q);
        node->right = deserializeHelper(q);

        return node;
    }

public:

    AVLTree() : root(nullptr) {}

    void insert(int value) {root = insert(root, value);}

    void deleteValue(int value) {root = deleteNode(root, value);}

    std::string serialize() {

        std::stringstream ss;
        serializeHelper(root, ss);

        return ss.str();
    }

    void deserialize(const std::string& data) {

        std::queue<std::string> q;
        std::stringstream ss(data);
        std::string item;

        while (std::getline(ss, item, ',')) {

            q.push(item);
        }

        root = deserializeHelper(q);
    }

    void inorder(Tree::Treenode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

    void printInOrder() {

        inorder(root);
        std::cout << std::endl;
    }
};

}
