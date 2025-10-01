#include<stdio.h>
#include<stdlib.h>
#include<vector>

using namespace std;

struct Node{
    int val;
    Node* next;
};

class LinkedList{
    Node *head;

    public:
        LinkedList() : head(NULL){}

    void insertStart(int val){
        Node *newNode = new Node();
        newNode->val = val;
        newNode->next = head;
        head=newNode;
    }

    void insertEnd(int val){
        Node *newNode = new Node();
        newNode->val = val;
        newNode->next = NULL;
        if(!head){
            head=newNode;
            return;
        }
        Node *temp = head;
        while(temp->next){
            temp=temp->next;
        }
        temp->next = newNode;
    }

    Node *reverseList(Node *head){
        Node *currNode=head, *prevNode=nullptr, *forwardNode;
        while(currNode!=nullptr){
            forwardNode=currNode->next;
            currNode->next=prevNode;

            prevNode=currNode;
            currNode=forwardNode;
        }
        return prevNode;
    }
};

Node *getIntersectionNode(Node* head1, Node* head2){
    while(head2!=NULL){
        Node* temp = head1;
        while(temp){
            if(temp==head2)
                return head2;
            temp=temp->next;
        }
        head2=head2->next;
    }
    return head2;
}
