# Step1
## Step1-1
- Setを用いてみたかどうかを確認する方法をとれば，みたものに初めて再来訪したらそのノードがループの最初
- ループ開始ノードのindexを返さないといけないので，Setではだめで，Mapを使う
	- Mapはkeyが順序比較できる必要がある（oprerator<() が定義されていないとコンパイルエラー）
	- ListNode*をkeyとすればok
	- Mapで所属性判定はdefined_map.find(target) < defined_map.end()でできる
	- と思ったらindexを返す問題じゃなかったので，普通にSetで良さそう
- よって，Setにみたノードを貯めて行って，みたものに当たったらそれを返し，先に終端についたらnullptrを返すように
```C++
#include <set>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node){
			if(seen.contains(cur_node)) {
				return cur_node;
			}
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		return nullptr;
    }
};
```

# Step2
## Step2-1
- フロイドのアルゴリズムならどうやるのか
	- fastとslowが一致するのは周回差ついた時
	- slowは1ずつ動いていたので，headからslowまでの距離がループ長
	- よってfastとslowが一致している時にslowをheadまで戻せばfastとslowの間はループ長だけ離れていて，これを維持したまま両者が一つずつ動いた結果再び一致した位置がループの開始位置
	- fast == slowの比較をwhileループの冒頭でやるミスをしていた．ループ冒頭で比較すると初期化したものそのものを比較することになるので当然失敗する．
```C++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
		ListNode *slow = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
            if(fast == slow) {
				break;
			}
		}
		if(!fast || !fast->next) {
			return nullptr;
		}
		slow = head;
		while(fast != slow) {
			fast = fast->next;
			slow = slow->next;
		}
		return fast;
    }
};
```

## Step2-2
- Setの方
- 特に前回から変わっていない
```C++
#include <set>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node) {
			if(seen.contains(cur_node)){
				return cur_node;
			}
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		return nullptr;
    }
};
```
# Step3
- これまでと同じ
```C++
#include <set>
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		std::set<ListNode*> seen;
		ListNode *cur_node;
		while(cur_node) {
			if(seen.contains(cur_node)) {
				return cur_node;
		}
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		return nullptr;
	}
};
```
