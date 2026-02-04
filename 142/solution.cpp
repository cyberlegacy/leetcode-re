class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        bool isArrived = true;
        while (slow != fast || isArrived){
            if (fast==nullptr || fast->next == nullptr){
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
            isArrived = false;
        }
        slow = head;
        while (slow != fast){
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};