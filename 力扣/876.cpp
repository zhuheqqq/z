/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* ptr=head;
        int size=1;
        int middle=0;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
            size++;
        }
        middle=size/2;
        while(middle--)
        {
            head=head->next;
        }
        return head;

    }
};