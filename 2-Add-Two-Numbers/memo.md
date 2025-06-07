# 問題
https://leetcode.com/problems/add-two-numbers/

# Step1
- 下の桁から順に繋がっているLinked List二つが与えられて，これら二つを足した数を表現するLinked Listを返す
- 基本的には同じ桁についての和と下の桁からの繰り上がりとの和を結果に繋げていく
- 同じ桁数とは限らなそうなので，両方のリストについて，桁を下から順に足し合わせていく作業を進めていって，片方の数が最上桁に達したら，あとは繰り上げとの和について考えて，桁数が多い方を結果Listに移していく作業
- このやり方だと，毎桁結果リストように新しいノードを動的に生成しないといけないので，与えられているリストのノードを再利用したい
```C++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        int carry = 0;
        while (l1 || l2) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = x + y + carry;
            carry = sum / 10;
            sum = sum % 10;
            result->next = l1 ? l1 : l2;
            result->next->val = sum;
            result = result->next;
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        if (carry) {
            ListNode *last_node = new ListNode(carry);
            result->next = last_node;
        }
        return dummy.next;
    }
};
```

# Step2
## Step2-1
- 再帰の方法
    - c.f. https://github.com/fuga-98/arai60/pull/6/files
- ヒープ領域にノードを新しく作らない再帰パターンを思いつかなかったのだが，メモリ解放がどうなされるのかわからない．実装上新しくヒープ領域常に作られたノードは結果まで残っていないといけないので実行側で解放しないといけない．LeetCodeでは気にしなくていいのだろうけど
    - c.f. https://github.com/kazukiii/leetcode/pull/6/files#r1633568781
    - スマートポインタを使えば良いという話もある
        - c.f. https://github.com/Ryotaro25/leetcode_first60/pull/5/files#r1611955050

## Step2-2
- ダミーなしバージョンは結構好みだったので真似してみる
    - https://github.com/kazukiii/leetcode/pull/6/files
- 加えて，l1 || l2 || carryの方法もシンプルで見やすいなと思ったので真似してみる
- Step1でやっていたすでにあるl1やl2のノードを結果用に再利用する方法は書く側にとっても読む側にとってもあまり嬉しくない気がしたのでやめる
- 値を置いておくようの変数名をx, yからv1, v2に変更
```C++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* node = nullptr;
        int carry = 0;
        while (l1 || l2 || carry) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            int sum = v1 + v2 + carry;
            carry = sum / 10;
            if (head) {
                node->next = new ListNode(sum % 10);
                node = node->next;
            } else {
                head = new ListNode(sum % 10);
                node = head;
            }
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        return head;
    }
};
```

# Step3
```C++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* node = nullptr;
        int carry = 0;
        while (l1 || l2 || carry) {
            int v1 = l1 ? l1->val : 0;
            int v2 = l2 ? l2->val : 0;
            int sum = v1 + v2 + carry;
            carry = sum / 10;
            if (head) {
                node->next = new ListNode(sum % 10);
                node = node->next;
            } else {
                head = new ListNode(sum % 10);
                node = head;
            }
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        return head;
    }
};
```
