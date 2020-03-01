/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Remove Nth Node from the end of Linked List.
Explain: Given the root node of Linked List with the size unknown.
         Remove Nth node and link the rest correctly.
*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include "ListNode.h"
#include "RemoveNode.h"

using namespace std;

ListNode* CreateList(const vector<int>& nums){
    if(nums.size() == 0) return nullptr;

    // Add the first element as root.
    ListNode* root = new ListNode(nums[0]);
    ListNode* Next = root;

    // Loop all elements into Linked List.
    for(int i = 1; i < nums.size(); i ++){
        Next->next = new ListNode(nums[i]);
        Next = Next->next;
    }

    // Make sure the last Link Node has no "next" element. Set it to nullptr.
    Next->next = nullptr;

    return root;
}

bool CompareLinkedListToVector(ListNode* test, const vector<int>& solution){
    for(int i = 0; i < solution.size(); i ++){
        // If there are solution left but no more Link Node, then they are not the same.
        if(test == nullptr) return false;

        // If corresponding values are not the same, return false;
        if(solution[i] != test->val) return false;

        test = test->next;
    }

    // When comparing is done, but there is still solution left, then they are not identical.
    if(test != nullptr) return false;

    return true;
}

void TestMaker(int TestNumber, string memo, const vector<int>& a, const int n, const vector<int>& answer){
    ListNode* l1 = CreateList(a);

    cout << "#" << TestNumber << " " << memo << "           ";
    ListNode* returned = removeNthFromEnd(l1, n);
    if(CompareLinkedListToVector(returned, answer)){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    TestMaker(1, "Removing Middle", vector<int>{1,2,3,4,5}, 2, vector<int>{1,2,3,5});
    TestMaker(2, "Removing Last", vector<int>{1,2,3,4,5}, 1, vector<int>{1,2,3,4});
    TestMaker(3, "Removing First", vector<int>{1,2,3,4,5}, 5, vector<int>{2,3,4,5});
    TestMaker(4, "Removing the Only Element", vector<int>{1}, 1, vector<int>{});
}
