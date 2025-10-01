#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<iostream>

using namespace std;

class Node{
    public:
        int key;
        Node *leftNode;
        Node *rightNode;

    Node(int key){
        this->key = key;
    }
};

class BST{
    public:
        Node *root;

        BST(){
            root=NULL;
        }

        void insertKey(int key){
            root = insertRec(root, key);
        }

        Node *insertRec(Node *root, int key){
            if(root==NULL)
                return new Node(key);
            if(root->key > key){
                root->leftNode = insertRec(root->leftNode, key);
            } else {
                root->rightNode = insertRec(root->rightNode, key);
            }
            return root;
        }

        void Traverse(){
            Traverse(root);
        }

        void Traverse(Node *root){
            if(root!=NULL){
                Traverse(root->leftNode);
                cout << root->key << endl;
                Traverse(root->rightNode);
            }
        }

        int height(Node *root){
            if(root==NULL)
                return 0;
            else{
                int lh = height(root->leftNode);
                int rh = height(root->rightNode);
                return max(lh, rh) + 1;
            }
        }

        void PrintCurrentLevel(Node *root, int level){
            if(root==NULL)
                return;
            if(level==1)
                cout << root->key << endl;
            else if(level>1){
                PrintCurrentLevel(root->leftNode, level-1);
                PrintCurrentLevel(root->rightNode, level-1);
            }
        }

        void PrintLevelOrder(){
            int h = height(root);
            for(int i=1; i<=h; i++)
                PrintCurrentLevel(root, i);
        }

        Node *getSuccessor(Node *currNode){
            currNode = currNode->rightNode;
            while(currNode!=NULL && currNode->leftNode!=NULL)
                currNode = currNode->leftNode;
            return currNode;
        }

        void delNode(int key){
            root = delNode(root,key);
        }

        Node *delNode(Node *root, int key){
            if(root==NULL)
                return root;
            if(root->key > key)
                root->leftNode = delNode(root->leftNode, key);
            else if(root->key < key)
                root->rightNode = delNode(root->rightNode, key);
            else{
                // Only right child
                if(root->leftNode==NULL){
                    Node *temp = root->leftNode;
                    delete root;
                    return temp;
                }

                // Only left child
                if(root->rightNode==NULL){
                    Node *temp = root->rightNode;
                    delete root;
                    return temp;
                }

                // When both children are present
                Node *succ = getSuccessor(root);
                root->key = succ->key;
                root->rightNode = delNode(root->rightNode, succ->key);
            }
            return root;
        }

};

int main(){
    BST* bst = new BST();
    bst->insertKey(10);
    bst->insertKey(20);
    bst->insertKey(15);
    bst->insertKey(25);
    bst->insertKey(30);
    bst->insertKey(5);

    bst->delNode(10);
    bst->Traverse();
    //bst->PrintLevelOrder();
    return 0;
}
