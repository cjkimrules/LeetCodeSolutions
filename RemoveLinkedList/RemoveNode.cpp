
#include <iostream>
#include "RemoveNode.h"
#include "ListNode.h"

using namespace std;

int LinkedListSize(ListNode* root){
    int Size = 0;
    while(root != nullptr){
        root = root->next;
        Size ++;
    }
    return Size;
}

// Time complexity: Size of linked list

// If we have 1,2,3,4,5 and n = 2,
// we want to work on the node with value 3 even though we are deleting the node with value 4.
// Because node 3 will have new "next". But make sure to "delete" node 4's memory.

ListNode* removeNthFromEnd(ListNode* head, int n) {
    int ListSize = LinkedListSize(head);

    if(n > ListSize){
        // Not specified in the problem, but if requested Nth removal is greater than the Linked Size,
        // we will return undefined behavior, nullptr.
        return nullptr;
    }else if(n == ListSize){
        // When we wish to remove the very first element, then we do not have a previous node to work on.
        // Thus free the first element and return the second element as root.
        ListNode* dead = head;
        head = head->next;
        delete dead;
    }else{
        // When we wish to remove any element in the middle (including the very last element),
        // we save the pointer to removing element for "delete" and point to next element.
        // Last element is the same since "nullptr" will act as next element.
        const int Index = ListSize - n - 1; // "1" offset is because we start counting index at 0.

        // After the for-loop, "node" will point to "current working node" which is the node
        // right before the node that is getting deleted.
        // In the example of {1,2,3,4,5} & n=2, working node will be {3} since {4} is getting deleted.
        ListNode* node = head;
        for(int i = 0; i < Index; i ++){
            node = node->next;
        }

        // Record current working node's next so we can free memory (delete).
        ListNode* dead = node->next;

        // Change "next" of current working node.
        node->next = node->next->next;
        delete dead;
    }

    return head;
}

