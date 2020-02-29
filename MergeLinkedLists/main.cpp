/******************************************************************************
Author: CJ Kim
Date: 2/28/2020

Title: Merge Lists
Explain: Merging 2 sorted Linked Lists into one remained sorted.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
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

void TestMaker(int TestNumber, string memo, const vector<int>* a, const vector<int>* b, const vector<int>* answer){
    ListNode* l1 = CreateList(a);
    ListNode* l2 = CreateList(b);

    cout << "#" << TestNumber << " " << memo << "           ";
    ListNode* returned = mergeTwoLists(l1, l2);
    if(CompareLinkedListToVector(returned, answer)){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    // No duplicate, same lengths
    vector<int> a{1,3,5};
    vector<int> b{2,4,6};
    vector<int> s{1,2,3,4,5,6};
    TestMaker(1, "No Duplicates, Same Lengths", &a, &b, &s);

    // No duplicate, different lengths
    a.assign({1,3,5,7});
    b.assign({2,4,6});
    s.assign({1,2,3,4,5,6,7});
    TestMaker(2, "No Duplicates, Different Lengths", &a, &b, &s);
    
    // Duplicates, same lengths
    a.assign({1,4,5});
    b.assign({2,4,6});
    s.assign({1,2,4,4,5,6});
    TestMaker(3, "Duplicates, Same Lengths", &a, &b, &s);

    // Duplicates, different lengths
    a.assign({2,3,6,7});
    b.assign({2,4,6});
    s.assign({2,2,3,4,6,6,7});
    TestMaker(4, "Duplicates, Different Lengths", &a, &b, &s);

    // No Pattern
    a.assign({2,3,6,7,7,7,7});
    b.assign({2,4,6,7,8,9});
    s.assign({2,2,3,4,6,6,7,7,7,7,7,8,9});
    TestMaker(5, "No Pattern", &a, &b, &s);
    
    // No Input
    a.assign({1,2,3});
    b.assign({});
    s.assign({1,2,3});
    TestMaker(6, "Empty Array", &a, &b, &s);
    
    // Long Array
    a.assign({1,1,1,1,1,2,2,3,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,9,9,9,9,9,10,11,12,13,14,15,16,17});
    b.assign({1,1,1,2,2,3,3,4,4,4,5,5,6,6,6,7,7,7,8,8,9,9,10,11,11,12,12,12,13,13,13,14,14,14,14,15,15,15,16});
    s.assign({1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,9,10,10,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,14,15,15,15,15,16,16,17});
    TestMaker(7, "Long Arrays", &a, &b, &s);
}
