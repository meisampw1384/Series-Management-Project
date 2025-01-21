#include "SplayTree.h"

SplayNode::SplayNode(const string &name) : mediaName(name), left(nullptr), right(nullptr) {}
SplayNode *SplayTree::rightRotate(SplayNode *x)
{
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode *SplayTree::leftRotate(SplayNode *x)
{
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode *SplayTree::splay(SplayNode *root, const string &key)
{
    if (!root || root->mediaName == key)
        return root;

    if (key < root->mediaName)
    {
        if (!root->left)
            return root;
        if (key < root->left->mediaName)
        {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (key > root->left->mediaName)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else
    {
        if (!root->right)
            return root;
        if (key > root->right->mediaName)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        else if (key < root->right->mediaName)
        {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree()
{
    deleteTree(root);
}

void SplayTree::deleteTree(SplayNode* node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}



void SplayTree::insert(const string &key)
{
    if (!root)
    {
        root = new SplayNode(key);
        return;
    }
    root = splay(root, key);
    if (root->mediaName == key)
        return;

    SplayNode *newNode = new SplayNode(key);
    if (key < root->mediaName)
    {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else
    {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    root = newNode;
}
bool SplayTree::search(const string &key)
{
    root = splay(root, key);
    return root && root->mediaName == key;
}