
#include <iostream>
#include "MergeLists.h"
#include "ListNode.h"

using namespace std;

// Time complexity: Size of l1 + Size of l2.
// This is still a linear time, since we only loop through both linked lists once.

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* MergedList = l1;
    // Two lists will be merged into one to "l1".
    while(l2 != NULL){
        // We will look through all "l2" components comparing with l1.
        // Only way to put l2's component as "Next" of current "l1" is when that number
        // is larger or equal to current value AND smaller than l1's next value.
        if((l1->val <= l2->val) && (l1->next == NULL || (l1->next->val > l2->val))){
            // If there is no "Next" value, then just add it as the largest number.
            // If there is "Next" value, then make sure "l2" value is smaller.
            // Add it.
            ListNode* a = new ListNode(l2->val);
            a->next = l1->next;
            l1->next = a;
            
            // When we successfully added "l2" value into "l1", move to next value of "l2".
            l2 = l2->next;
        }else{
            // If "l1"s Next wasn't null and it wasn't bigger than "l2",
            // then move "l1" to next element.
            // If "l1" value wasn't equal or smaller to "l2" then move to next element.
            l1 = l1->next;
        }
    }
    
    return MergedList;
}

