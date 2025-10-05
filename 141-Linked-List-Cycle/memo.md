# Step1
## Step1-1
- Follow up messageが空間計算量を定数にする方法を問うていたので，その方向を考えてみる．
	- ノード数の上限が制限で与えられているので，その回数以上ノードをみるならそれは巡回している
	- 逆にその回数以内で終端に達するなら巡回していない
```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
		int num_visit_nodes = 0;
		ListNode *cur_node = head;
		while(!cur_node->val){
			num_visit_nodes++;
			cur_node = cur_node->next;
			if(num_visit_nodes >= 105){
				return true;
			}
		}
		return false;
    }
};
```

## Step1-2
- 上記の方法ではどのノードに立ち寄ったのかを使っていないので，そちらも考える
- どのノードを見たかに順序は必要ないのでSetにみたノードを入れて行って，ノードを訪れるたびに過去に訪れていないか検索
	- Setは主要操作の計算量がO(log N)
	- setはListNode*のsetとした
```C++
#include <set>
class Solution {
public:
    bool hasCycle(ListNode *head) {
		std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node && !seen.contains(cur_node)){
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		if(cur_node){
			return true;
		}else{
			return false;
		}
    }
};
```

# Step2
## Step2-1
- フロイドのアルゴリズムというのもあるらしい．
	- fastとslowで2つのノードを見ていく
	- 1ステップでfastは2つ，slowは1つ動く
	- どちらも終端に達することなくfastとslowが同じノードに止まることがあれば，fastが周回差をつけてflowに追いついていて，つまりそれはループしているということ
- Setを持たなくていいので，空間計算量を定数にできる
- Setへのinsertとcontainsがないので，時間計算量もLinked Listの要素数に線形
```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
		ListNode *fast = head;
		ListNode *slow = head;
		while(fast && fast->next && slow){
			fast = fast->next->next;
			slow = slow->next;
			if(fast == slow){
				return true;
			}
		}
		return false;
    }
};
```

## Step2-2
- Setの方を復習
- 前回と同じ
```C++
#include <set>
class Solution {
public:
    bool hasCycle(ListNode *head) {
		std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node && !seen.contains(cur_node)){
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		if(cur_node){
			return true;
		}else{
			return false;
		}
    }
};
```

# Step3
## Step3-1
- フロイドのアルゴリズムの方
- 同じ
```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
		ListNode *fast = head;
		ListNode *slow = head;
		while(fast && fast->next && slow){
			fast = fast->next->next;
			slow = slow->next;
			if(fast == slow){
				return true;
			}
		}
		return false;
    }
};
```

## Step3-2
- Set使う方
- 既に見たノード集合に含まれることの条件判定を2回していたので，1回でできるようにした
```C++
#include <set>
class Solution {
public:
    bool hasCycle(ListNode *head) {
		std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node){
			if(seen.contains(cur_node)){
				return true;
			}
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		return false;
    }
};
```

# 先人のコメントを読み漁る
- headが最初からNULLのケースもありうる
	- 考えていなかったが確かにそう

