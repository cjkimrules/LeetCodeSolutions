/******************************************************************************
Author: CJ Kim
Date: 2/28/2020

Title: Merge Lists
Explain: Merging 2 sorted Linked Lists into one remained sorted.

*******************************************************************************/

#include <iostream>
#include <vector>
#include "ListNode.h"
#include "MergeLists.h"

using namespace std;

ListNode* CreateList(const vector<int>* nums){
    if(nums->size() == 0) return nullptr;

    // Add the first element as root.
    ListNode* root = new ListNode((*nums)[0]);
    ListNode* Next = root;

    // Loop all elements into Linked List.
    for(int i = 1; i < nums->size(); i ++){
        Next->next = new ListNode((*nums)[i]);
        Next = Next->next;
    }

    // Make sure the last Link Node has no "next" element. Set it to nullptr.
    Next->next = nullptr;

    return root;
}

bool CompareLinkedListToVector(ListNode* test, const vector<int>* solution){
    for(int i = 0; i < solution->size(); i ++){
        // If there are solution left but no more Link Node, then they are not the same.
        if(test == nullptr) return false;

        // If corresponding values are not the same, return false;
        if((*solution)[i] != test->val) return false;

        test = test->next;
    }

    // When comparing is done, but there is still solution left, then they are not identical.
    if(test != nullptr) return false;

    return true;
}

void TestMaker(int TestNumber, const vector<int>* a, const vector<int>* b, const vector<int>* answer){
    ListNode* l1 = CreateList(a);
    ListNode* l2 = CreateList(b);

    cout << "#" << TestNumber << " ";
    ListNode* returned = mergeTwoLists(l1, l2);
    if(CompareLinkedListToVector(returned, answer)){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    vector<int> a{1,2,4};
    vector<int> b{1,3,4};
    vector<int> s{1,1,2,3,4,4};
    TestMaker(1, &a, &b, &s);
}
