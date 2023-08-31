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
class Solution
{
    static bool Compare(ListNode* a, ListNode* b)
    {
        return(a->val < b->val);
    }

public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        vector<ListNode*> ans;

        while (list1 != NULL)
        {
            ans.push_back(list1);
            list1 = list1->next;
        }

        while (list2 != NULL)
        {
            ans.push_back(list2);
            list2 = list2->next;
        }

        if (ans.empty()) return NULL;

        sort(ans.begin(), ans.end(), Compare);

        int i = 0;
        for (i = 0; i < ans.size() - 1; i++)
        {
            ans[i]->next = ans[i + 1];
        }

        ans[i]->next = NULL;

        return ans[0];

    }
};