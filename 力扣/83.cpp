class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return nullptr; // 如果链表为空，直接返回空指针
        }

        ListNode* ptr = head;
        ListNode* pre = head;
        int flag = -200;

        while (ptr) {
            if (flag == ptr->val) {
                pre->next = ptr->next;
            } else {
                flag = ptr->val;
                pre = ptr;
            }
            ptr = ptr->next;
        }

        return head;
    }
};
