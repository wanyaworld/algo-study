#include <iostream>
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
class Solution {
public:
    ListNode* h, *new_head{};
    int arr[500];
    int org[500];
    int rot;
    int n{};
    int n_rot;
    void myInsert(ListNode **head, int val) {
        ListNode* p = new ListNode;
        p->val = val;
        p->next = nullptr;
        if (!(*head)) {
            *head = p;
        }
        else {
            p->next = *head;
						*head = p;
        }
    }
    ListNode* rotateRight(ListNode* head, int k) {
        h = head;
        int i = 0 ;
        for (ListNode *tmp = h ; tmp ; tmp = tmp->next, i++) {
            n++;
            org[i] = tmp->val;
        }
        n_rot = k % n;
        int org_i = n_rot;
        for(int i = 0 ; i < n ; i++) {
            if (org_i > n - 1) org_i = 0;
            arr[i] = org[org_i];
            org_i++;
        }
        for (int i = n - 1 ; i >= 0 ; i--) {
            myInsert(&new_head, arr[i]);
        }
        return new_head;
    }
};

int main () {
	Solution sl;
	ListNode *p = new ListNode[3];	
	p[0].val = 1;
	p[1].val = 2;
	p[2].val = 3;
	
	p[0].next = &(p[1]);
	p[1].next = &(p[2]);
	p[2].next = nullptr;

	sl.rotateRight(&(p[0]), 1);
	return 0;
}

