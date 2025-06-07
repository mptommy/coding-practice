# 問題
https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

# Step1
- ソート済みのlinked listが与えられて，valに重複があるノードを全て削除したものを返す
- 現在見ているノードが重複していないかは，前から順番に見ていく場合，次のノードと重複してないかを確認するだけで決まる
- 返すように別の先頭ノードを持っていた方が実装しやすいかもしれない
	- return_list_headとか名付ける
- 重複ノードを全て消すので，headも消される可能性がある
	- 結果用のリストが別に必要
		- 初期値はheadノードの保持している値より小さければなんでもいい
		- ここで，headがNULLだとエラーになるので，validation
	- 結果用リストの先頭ノードへのリンクとしてListNode*型変数を用意するので，最後にこれの次を返す
- 現在のノードと次のノードの値を見比べて，一致していたら次のノードを無視することを繰り返す
	- この場合，現在のノードも無視する必要があるので，「現在のノードと次のノードの値を見比べて一致しない」場合を考える
	- 一致しない場合，現在のノードは結果に残していいので，結果リストの最後尾に加える
		- 注目ノードも次に進める
		- ただし，現在のノードの値だけが欲しいのであって，次のノードへのリンクはいらない&現在のノードの次のノードの情報は上の処理で用済みになったので，結果リストの末尾の次ノードはNULLにしておく
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        ListNode *node = head;
        while (node) {
            if (node->next && node->next->val == node->val) {
                while (node->next && node->next->val == node->val) {
                    node->next = node->next->next;
                }
                node = node->next;
            } else {
                result->next = node;
                result = result->next;
                node = node->next;
                result->next = nullptr;
            }
        }
        return dummy.next;
    }
};
```

# Step2
# Step2-1
- 再帰で解くパターンをやっている方がいたので，やってみる
	- c.f. https://github.com/fuga-98/arai60/pull/5
	- 遥かに書きやすい
	- 気にすることの個数がだいぶ少ない感じがする
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* pre_result = deleteDuplicates(head->next);
        if (head->val == head->next->val) {
            if (pre_result == head->next) {
                return pre_result->next;
            } else {
                return pre_result;
            }
        } else {
            head->next = pre_result;
            return head;
        }
    }
};
```
# Step2-2
- こちらの方のコードを参考にStep1のコードを修正
	- https://github.com/olsen-blue/Arai60/pull/4/files
	- これをみるとnode->nextを次に更新していくやり方ではなくてnodeを次に更新していくことにしている
		- 現在のノードを固定して次を変えて比較すると，現在のノードは変わらないので，更新し尽くした次のノードがさらにその次のノードと比較したときにどうなっているかはわからない
		- 一方で現在のノードを更新していくことにすると，常に現在のノードを次のノードと比較し続けるので，更新し尽くしたときに現在のノードに入っているノードは次のノードと異なる値を持っている（が，最初の条件分岐で少なくとも一回はwhileの条件がtrueになることがわかっているので，最終的な現在のノードは前のノードとは同じ値を持っている）
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        ListNode *node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                while (node->next &&  node->val == node->next->val) {
                    node = node->next;
                }
                node = node->next;
            } else {
                result->next = node;
                result = result->next;
                node = node->next;
                result->next = nullptr;
            }
        }
        return dummy.next;
    }
};
```

# Step3
# Step3-1
- 再帰の方法
- elseの部分を外に出したり，ノード同士の比較を値同士の比較に変えたりした
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* pre_result = deleteDuplicates(head->next);
        if (head->val == head->next->val) {
            if (pre_result == head->next) {
                return pre_result->next;
            } else {
                return pre_result;
            }
        } else {
            head->next = pre_result;
            return head;
        }
    }
};
```

# Step3-2
- 次と比較することを繰り返すやり方
- 条件分岐をどう分けるかこんがらがっていたが，各分岐の終了状態が定義できていればわかりやすいことに気づいた
	- whileの中のifの場合の話
	- 今回の実装では，if(node->next && node->val == node->next->val)内の終了状態はnode->valがその直前のnodeの値と異なるという状態になっていて，これはelseの方も同じなので，ループの次のステップで前ステップの状況をリフレッシュして考えられる
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        ListNode *node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                while (node->next && node->val == node->next->val) {
                    node = node->next;
                }
                node = node->next;
            } else {
                result->next = node;
                node = node->next;
                result = result->next;
                result->next = nullptr;
            }
        }
        return dummy.next;
    }
};
```

# Step3-3
- Step3-2に時間がかかったのでもう一度
- result->nextに最後に追加したノードの後のリストがついてしまっているのを無効化する処理をループを全て抜けた後に設定することで冗長な処理をまとめられた
```C++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        ListNode *node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                while (node->next && node->val == node->next->val) {
                    node = node->next;
                }
            }
            else {
                result->next = node;
                result = result->next;
            }
            node = node->next;
        }
        result->next = nullptr;
        return dummy.next;
    }
};
```
