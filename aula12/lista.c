#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode AVLNode;

struct AVLNode {
    char* key;
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
};

AVLNode* newAVLNode(char* key, int value) {
    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int balance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* insert(AVLNode* node, char* key, int value) {
    if (node == NULL) {
        return newAVLNode(key, value);
    }

    if (strcmp(key, node->key) < 0) {
        node->left = insert(node->left, key, value);
    } else if (strcmp(key, node->key) > 0) {
        node->right = insert(node->right, key, value);
    } else {
        node->value = value;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = balance(node);

    if (balanceFactor > 1 && strcmp(key, node->left->key) < 0) {
        return rotateRight(node);
    }

    if (balanceFactor < -1 && strcmp(key, node->right->key) > 0) {
        return rotateLeft(node);
    }

    if (balanceFactor > 1 && strcmp(key, node->left->key) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1 && strcmp(key, node->right->key) > 0) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
}
// update the height of the node
node->height = max(height(node->left), height(node->right)) + 1;

return node;
}

// function to insert a key-value pair in the hashtable
void put(char* key, char* value) {
int index = hashCode(key) % 9;
table[index] = insert(table[index], key, value);
}

// function to print all the key-value pairs in the hashtable
void printHashtable() {
for (int i = 0; i < 9; i++) {
AVLNode* node = table[i];
while (node != NULL) {
printf("%s: %s\n", node->key, node->value);
node = node->next;
}
}
}

int main() {
// create a hashtable of size 9 with AVL tree collision handling
Hashtable hashtable = createHashtable(9);
	// insert some key-value pairs
hashtable.put("key1", "5");
hashtable.put("key2", "28");
hashtable.put("key3", "19");
hashtable.put("key4", "15");
hashtable.put("key5", "20");
hashtable.put("key6", "33");
hashtable.put("key7", "12");
hashtable.put("key8", "17");
hashtable.put("key9", "10");

// print all the key-value pairs in the hashtable
for (int i = 1; i <= 9; i++) {
    char* key = (char*)malloc(sizeof(char)*5);
    sprintf(key, "key%d", i);
    char* value = get(hashtable, key);
    printf("%s: %s\n", key, value);
}

return 0;
}