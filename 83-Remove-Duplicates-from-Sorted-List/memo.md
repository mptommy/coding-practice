# Step1
- ソートはされているが，値の重複はあるリストが与えられて，値の重複がないソート済みリストを返す問題
    - ソートはされているので，重複している値をもつノードは必ず連続している
    - 「前ノードの値の先頭ノード」と「現在見ているノード」を持っておいて，「現在見ているノード」が初めて「前ノードの値」と異なる値をもつとき，そのノードをnextに設定することを繰り返せば良さそう
    - これで時間計算量はリスト長に線形
    - headから始まるリストを直接編集していってheadを返すことにする
    - 上記の処理だと，最後の同値連続だけremoveされないので，そこだけ追加処理
        - 上と同じ更新処理だが，くっつけるノードはNULL
        - ただし，最初のheadがNULLだったりするとエラーになるので，くっつけられる側がNULLでないことの確認は必要
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *leader_node = head;
        ListNode *current_node = head;
        while (current_node) {
            if (leader_node->val != current_node->val) {
                leader_node->next = current_node;
                leader_node = current_node;
            }
            current_node = current_node->next;
        }
        if (leader_node) {
            leader_node->next = nullptr;
        }
        return head;
    }
};
```

# Step2
## Step2-1
- 自分のStep1は今までに見てきたものの「連続ノード列の先頭ノード」の列を保持したまま先を見進めていって，連続ノード列が切り替わったら「連続ノード列の先頭ノード」の列に新入り先頭ノードを付け加えるというやり方だった
    - このやり方は二つの注目ノードを見るノードと要求されているリストの最後尾ノードという形で役割を分けている
- 先に解かれた方々には，注目しているノード変数を一つにして，代わりに注目しているノードに「要求されているリストの最後尾ノード」，そのノードの次ノードに「見るノード」の役割を課すやり方をしている方もいた
    - 今見ているノードの値と次のノードの値が同じなら，次のノードは飛ばしてその次に行こうというロジック
    - このやり方は注目ノードの次ノードが「見るノード」専門ではなく，要求されているリストの編集の役割も担っている
    - 二重ループの方法で実装
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node = head;
        while (node && node->next) {
            while (node->next && node->val == node->next->val) {
                node->next = node->next->next;
            }
            node = node->next;
        }
        return head;
    }
};
```

## Step2-2
- If-Continueの方法
  - 二重ループの内側のループをifによる条件分岐にした上で，ループ内の処理の最後にcontinueを入れて外側のループのノード更新処理を行わないことで内側のループも実現する
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                node->next = node->next->next;
                continue;
            }
            node = node->next;
        }
        return head;
    }
};
```

## Step2-3
- 再帰で書く
- Base Caseは，headがNULLかhead->nextがNULLの時で，このときはheadをそのまま返す
- Induction Caseでは，
  - headとhead->nextがvalが同じなら，head->nextをheadとしてdeleteDuplicatesを実行したものをそのまま返す
  - そうでないなら，head->nextをheadとしてdeleteDuplicatesを実行したものの先頭にheadをつけたもの，つまり現状のheadを返す
- 毎回Base Caseのチェックを行うので少し遅くなる
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) { // Base Case
            return head;
        }
        if (head->val == head->next->val) {
            return deleteDuplicates(head->next);
        } else {
            head->next = deleteDuplicates(head->next);
            return head;
        }
    }
};
```

## Step2-4
- 元々考えていた，二つノード変数を置くやり方
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* current_node = head;
        ListNode* leader_node = head;
        while (current_node) {
            if (current_node->val != leader_node->val) {
                leader_node->next = current_node;
                leader_node = current_node;
            }
            current_node = current_node->next;
        }
        if (leader_node) {
            leader_node->next = nullptr;
        }
        return head;
    }
};
```

# Step3
- 今までの4パターンを復習
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *node = head;
        while (node) {
            while (node->next && node->val == node->next->val) {
                node->next = node->next->next;
            }
            node = node->next;
        }
        return head;
    }
};
```
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                node->next = node->next->next;
                continue;
            }
            node = node->next;
        }
        return head;
    }
};
```
- まだ上の二重ループの回答を頭に思い浮かべながらでないとIf-Continueの形で書けない
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        if (head->val == head->next->val) {
            return deleteDuplicates(head->next);
        } else {
            head->next = deleteDuplicates(head->next);
            return head;
        }
    }
};
```
- 読みやすいかというと微妙かもしれないが，書きやすい
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *current_node = head;
        ListNode *leader_node = head;
        while (current_node) {
            if (current_node->val != leader_node->val) {
                leader_node->next = current_node;
                leader_node = current_node;
            }
            current_node = current_node->next;
        }
        if (leader_node) {
            leader_node->next = nullptr;
        }
        return head;
    }
};
```
