#include <iostream>
#include <unordered_map>

using namespace std;
 
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    unordered_map<int, unsigned int> dict{};
    void myDelete(ListNode *head, ListNode* prv, ListNode *p) {
        if (p == head) {
            head = head->next;
        }
        else  {
            if (prv)
                prv->next = p->next;
        }
    }
    ListNode* deleteDuplicates(ListNode* head) {
        for (ListNode* p = head ; p ; p = p->next) {
           if (dict.find(p->val) == dict.end()) {
               dict[p->val] = 1;           
           }
            else {
                dict[p->val]++;
            }
        }
        
        for (ListNode* p = head, *prv = nullptr ; p ; p = p ->next) {
            if (dict.find(p->val) != dict.end() && dict[p->val] > 1) {
                myDelete(head, prv, p);
            }
            else {
                prv = p;
            }
        }
        return head;
    }
};

int main() {
	ListNode* p = new ListNode[3];
	ListNode* p2 = new ListNode[3];
	p[0].val = 1;
	p[1].val = 1;
	p[2].val = 2;

	p[0].next = &p[1];
	p[1].next = &p[2];
	p[2].next = nullptr;

	Solution sl;
	sl.deleteDuplicates(&p[0]);
	return 0;
}
