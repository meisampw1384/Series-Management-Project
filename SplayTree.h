
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

class SplayNode{
public:
    string mediaName;
    SplayNode *left;
    SplayNode *right;

    SplayNode(const string &name);
};
class SplayTree {
private:
    SplayNode* rightRotate(SplayNode* x);
    SplayNode* leftRotate(SplayNode* x);
    SplayNode* splay(SplayNode* root, const string &key);

public:
    SplayNode *root;
    SplayTree();
    ~SplayTree();
    void insert(const string &key);
    bool search(const string &key);
    void deleteTree(SplayNode* node);

};

#endif 
