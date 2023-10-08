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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true; // 空链表或只有一个节点时认为是回文
        }

        // 使用快慢指针找到链表的中间节点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 反转后半部分链表
        ListNode* secondHalf = reverseList(slow->next);
        
        // 比较前半部分和反转后的后半部分链表
        while (secondHalf != nullptr) {
            if (head->val != secondHalf->val) {
                return false;
            }
            head = head->next;
            secondHalf = secondHalf->next;
        }

        return true;
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head != nullptr) {
            ListNode* nextNode = head->next;
            head->next = prev;
            prev = head;
            head = nextNode;
        }
        return prev;
    }
};
