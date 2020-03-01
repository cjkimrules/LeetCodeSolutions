#ifndef LIST_NODE
#define LIST_NODE

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

#endif