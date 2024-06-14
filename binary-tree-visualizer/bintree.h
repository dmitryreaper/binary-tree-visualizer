#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>

#define BINTREE_PRINT_FMT "(" << leaf->key << ";" << leaf->data << "), ";

template <typename T>
struct node {
    T* data;
    int key;

    node<T>* left;
    node<T>* right;
};

template <typename T>
class bintree {
public:
    bintree();
    ~bintree();

    node<T>* insert(int key);
    node<T>* search(int key);
    node<T>* searchMax();
    node<T>* searchMin();
    int leftDepth();
    int rightDepth();

    static int leftDepth(node<T>* leaf);
    static int rightDepth(node<T>* leaf);
    static int depth(node<T>* leaf);
    static int getMaxWidth(node<T>* leaf);
    void destroy(int key);

    void destroyTree();

    void inorderPrint();
    void postorderPrint();
    void preorderPrint();


    node<T>* root;
private:
    void destroyTree(node<T>* leaf);

    node<T>* insert(int key, node<T>* leaf);
    node<T>* search(int key, node<T>* leaf);
	node<T>* searchMax(node<T>* leaf);
	node<T>* searchMin(node<T>* leaf);
    static int getWidth(node<T>* leaf, int level);
    node<T>* destroy(int* key, node<T>* leaf);

    void inorderPrint(node<T>* leaf);
    void postorderPrint(node<T>* leaf);
    void preorderPrint(node<T>* leaf);
};


// implementation
template <typename T>
bintree<T>::bintree() {
    root = nullptr;
}

template <typename T>
bintree<T>::~bintree() {
    destroyTree();
}

template <typename T>
void bintree<T>::destroyTree(node<T> *leaf) {
    if (leaf != nullptr) {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf->data;
        delete leaf;
    }
}

template <typename T>
node<T>* bintree<T>::insert(int key, node<T> *leaf) {
    if (key < leaf->key) {
        if (leaf->left != nullptr) {
            return insert(key, leaf->left);
        } else {
            leaf->left = new node<T>;
            leaf->left->key = key;
            leaf->left->data = new T;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
            return leaf->left;
        }
    } else if (key >= leaf->key)  {
        if (leaf->right != nullptr) {
            return insert(key, leaf->right);
        } else {
            leaf->right = new node<T>;
            leaf->right->key = key;
            leaf->right->data = new T;
            leaf->right->right = nullptr;
            leaf->right->left = nullptr;
            return leaf->right;
        }
    }
}

template <typename T>
node<T>* bintree<T>::insert(int key) {
    if (root != nullptr) {
        return insert(key, root);
    } else {
        root = new node<T>;
        root->key = key;
        root->data = new T;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
}

template <typename T>
node<T>* bintree<T>::search(int key, node<T> *leaf) {
    if (leaf != nullptr) {
        if  (key == leaf->key) {
            return leaf;
        }
        if (key < leaf->key) {
            return search(key, leaf->left);
        } else {
            return search(key, leaf->right);
        }
    } else {
        return nullptr;
    }
}

template <typename T>
node<T>* bintree<T>::search(int key) {
    return search(key, root);
}

template <typename T>
node<T>* bintree<T>::searchMax(node<T>* leaf) {
	if (leaf->right == nullptr)
		return leaf;
	else
		return searchMax(leaf->right);
}

template <typename T>
node<T>* bintree<T>::searchMax() {
	if (root == nullptr) 
		return nullptr;

	return searchMax(root);
}

template <typename T>
node<T>* bintree<T>::searchMin(node<T>* leaf) {
	if (leaf->left == nullptr)
		return leaf;
	else
		return searchMin(leaf->left);
}

template <typename T>
node<T>* bintree<T>::searchMin() {
	if (root == nullptr)
		return nullptr;

	return searchMin(root);
}

template <typename T>
int bintree<T>::leftDepth() {
    int depth = 0;

    node<T>* leaf = root;

    while (leaf != nullptr) {
        leaf = leaf->left;
        depth++;
    }
    depth--;

    return depth;
}

template <typename T>
int bintree<T>::rightDepth() {
    int depth = 0;

    node<T>* leaf = root;

    while (leaf != nullptr) {
        leaf = leaf->right;
        depth++;
    }
    depth--;

    return depth;
}

template <typename T>
int bintree<T>::leftDepth(node<T>* leaf) {
    int depth = 0;

    while (leaf != nullptr) {
        leaf = leaf->left;
        depth++;
    }
    depth--;

    return depth;
}

template <typename T>
int bintree<T>::rightDepth(node<T>* leaf) {
    int depth = 0;

    while (leaf != nullptr) {
        leaf = leaf->right;
        depth++;
    }
    depth--;

    return depth;
}

template <typename T>
int bintree<T>::depth(node<T>* leaf) {
    if (leaf == nullptr)
        return 0;

    int leftHeight = depth(leaf->left);
    int rightHeight = depth(leaf->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

template <typename T>
int bintree<T>::getMaxWidth(node<T>* leaf) {
    int maxWidth = 0;
    int width;
    int h = depth(leaf);
    int i;

    for (i = 1; i <= h; i++) {
        width = getWidth(leaf, i);
        if (width > maxWidth)
            maxWidth = width;
    }

    return maxWidth;
}

template<typename T>
int bintree<T>::getWidth(node<T>* leaf, int level) {
    if (leaf == nullptr)
        return 0;

    if (level == 1)
        return 1;

    if (level > 1)
        return getWidth(leaf->left, level - 1) + getWidth(leaf->right, level - 1);
}

template <typename T>
node<T>* bintree<T>::destroy(int* key, node<T>* leaf) {
	if (leaf->key > *key)
		leaf->left = destroy(key, leaf->left);
	else if (leaf->key < *key)
		leaf->right = destroy(key, leaf->right);
	else {
		if (leaf->left == nullptr) {
			node<T>* right = leaf->right;
			delete leaf;
			return right;
		} else if (leaf->right == nullptr) {
			node<T>* left = leaf->left;
			delete leaf;
			return left;
		}

		node<T>* min = searchMin(leaf->right);
		leaf->key = min->key;
		leaf->right = destroy(&min->key, leaf->right);
	}
	
	return leaf;
}

template <typename T>
void bintree<T>::destroy(int key) {
	if (root == nullptr)
        return;
	
    destroy(&key, root);
}

template <typename T>
void bintree<T>::destroyTree() {
    destroyTree(root);
}

template <typename T>
void bintree<T>::inorderPrint() {
    inorderPrint(root);
    std::cout << "\n";
}

template <typename T>
void bintree<T>::inorderPrint(node<T>* leaf) {
    if (leaf != nullptr) {
        inorderPrint(leaf->left);
        std::cout << BINTREE_PRINT_FMT;
        inorderPrint(leaf->right);
    }
}

template <typename T>
void bintree<T>::postorderPrint() {
    postorderPrint(root);
    std::cout << "\n";
}

template <typename T>
void bintree<T>::postorderPrint(node<T>* leaf) {
    if (leaf != nullptr) {
        postorderPrint(leaf->left);
        postorderPrint(leaf->right);
        std::cout << BINTREE_PRINT_FMT;
    }
}

template <typename T>
void bintree<T>::preorderPrint() {
    preorderPrint(root);
    std::cout << "\n";
}

template <typename T>
void bintree<T>::preorderPrint(node<T>* leaf) {
    if (leaf != nullptr) {
        std::cout << BINTREE_PRINT_FMT;
        preorderPrint(leaf->left);
        preorderPrint(leaf->right);
    }
}

#endif
