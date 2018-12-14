#pragma once
#include "ListNode.h" //引入列表节点类

template <typename T> class LinkedList { //列表模板类
private:
	int _size; //规模
	ListNode<T>* header; //头哨兵
	ListNode<T>* trailer; //尾哨兵

protected: /* 内部函数 */
	void init() { //初始化，创建列表对象时统一调用
		header = new ListNode<T>; //创建头哨兵节点
		trailer = new ListNode<T>; //创建尾哨兵节点
		header->succ = trailer; header->pred = NULL; //互联
		trailer->pred = header; trailer->succ = NULL; //互联
		_size = 0; //记录规模
	}

	void copyNodes(ListNode<T>* p, int n) { //O(n)
		init(); //创建头、尾哨兵节点并做初始化
		while (n--) { //将起自p的n项依次作为末节点插入
			insertAsLast(p->data);
			p = p->succ;
		}
	}

    int clear(){ //清除所有节点
        int oldSize = _size;
   	    while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
        return oldSize;
    }

	/*二路归并
	  不仅修改指针指向的内容，而且要对指针本身进行修改，所以参数是引用类型*/
	void merge(ListNode<T>* &p, int n, LinkedList<T> &L, ListNode<T>* q, int m) {
		ListNode<T>* pp = p->pred; //借助前驱（可能是header），以便返回当前节点
		while (0 < m) { //在q尚未移出区间之前
			if ((0 < n) && p->data < q->data) { //若p仍在区间内，且p->data小于等于q->data
				if (q == (p = p->succ))	break; n--; //则p归入合并的链表，并替换为直接后继
			}else { //若p已超出右界，或q->data小于p->data，
				insertBefore(p, L.remove((q = q->succ)->pred)); //则将q转移至p之前
				m--;
			}
		}
		p = pp->succ; //确定归并后区间的（新）起点
	}

	/*链表的归并排序算法，对起始于位置p的n个元素排序*/
	void mergesort(ListNode<T>* &p, int n) {
		//assert(valid(p) && rank(p) + n <= _size);
		if (n < 2) return; //若待排序范围已足够小，则直接返回
		ListNode<T>* pp = p->pred;

		//递归
		int m = n >> 1; //以中点为界
		ListNode<T>* q = p;
		for (int i = 0; i < m; i++) //均分链表
			q = q->succ;
		
		mergesort(p, m); //对前子链表进行排序
		mergesort(q, n - m); //对后子链表进行排序
		merge(p, m, *this, q, n - m);

		p = pp->succ;
	}

public:
// 构造函数
	/*默认构造函数*/
	LinkedList () {
		init();
	}

	//整体复制列表L
    LinkedList ( LinkedList<T> & L ) {  
    	copyNodes ( L.first(), L._size ); 
    }
    
    //复制L中自第r项起的n项（assert: r+n <= L._size）
    LinkedList ( LinkedList<T> const& L, int r, int n ) {
        copyNodes ( L[r], n );
    }
    
    //复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
    LinkedList ( ListNode<T> p, int n ) {
        copyNodes ( p, n );
    }

// 析构函数
    ~LinkedList(){ //释放（包含头、尾哨兵在内的）所有节点
        clear(); 
        delete header; 
        delete trailer;
    }

// 只读访问接口
	int size() const { //规模
		return _size;
	}

	bool empty() const { return _size <= 0; } //判空

	//重载操作符 “[]”，支持循秩访问
	T operator[](int r) const { //O(r)，效率低下，可偶尔为之，却不宜常用
		ListNode<T>* p = first(); //从首节点出发
		while (0 < r--) p = p->succ; //顺数第r个节点即是
		return p->data; //目标节点
	} //任一节点的秩，亦即前驱的总数

	//此函数功能和重载操作符 “[]” 一样，都是返回第 r 个节点的数值
	T get(int r) const { //O(r)
		ListNode<T>* p = first(); //从首节点出发
		while (0 < r--) p = p->succ; //顺数第r个节点即是
		return p->data; //目标节点
	} //任一节点的秩，亦即前驱的总数

	/*返回首节点*/
	ListNode<T>* first() const {
		return _size == 0 ? NULL : header->succ;
	}

	/*返回末节点*/
	ListNode<T>* last() const {
		return _size == 0 ? NULL : trailer->pred;
	}
	//判断位置p是否对外合法
    bool valid ( ListNode<T> p ) { 
		return p && ( trailer != p ) && ( header != p ); 
	} //将头、尾节点等同于NULL

	/*判断所有节点是否是乱序，如果是，返回true，否则返回false
	  要求：T 为基本类型或已实现了对运算符 “>” 的重载*/
	int disordered() const { //统计逆序相邻元素对的总数
		int n = 0; ListNode<T>* p = first();
		for ( int i = 0; i < _size - 1; p = p->succ, i++ )
			if ( p->data > p->succ->data ) n++;
		return n;
	}

	//无序列表查找
	ListNode<T>* find(T const & e) const {
		return find ( e, _size, trailer );
	}

	/*查找
	  在节点p（可能是trailer）的 n 个（真）前驱中，找到等于 e 的最后者
	  要求：T 为基本类型或已实现了对运算符 “==” 的重载*/
	ListNode<T>* find(T const & e, int n, ListNode<T>* p) const{ //顺序查找，O(n)
		while (0 < n-- && p->pred != NULL) //从右向左，逐个将 p 的前驱与 e 比对
			if (e == (p = p->pred)->data)
				return p; //直至命中或范围越界
		return NULL; //若越出左边界，意味着查找失败
	}//header 的存在使得处理更为简洁

	/*在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
	  要求：T 为基本类型或已重载操作符 “<=”*/
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const {
		// assert: 0 <= n <= rank(p) < _size
		while (0 <= n--) //对于p的最近的n个前驱，从右向左逐个比较
			/*DSA*/ {
			if (((p = p->pred)->data) <= e) break; //直至命中、数值越界或范围越界
			/*DSA*/
		}
		// assert: 至此位置p必符合输出语义约定——尽管此前最后一次关键码比较可能没有意义（等效于与-inf比较）
		return p; //返回查找终止的位置
	} //失败时，返回区间左边界的前驱（可能是header）——调用者可通过valid()判断成功与否
	
	//有序列表整体查找
	ListNode<T>* search(T const& e) const {
		return search(e, _size, trailer);
	}

// 可写访问接口
	ListNode<T>* insertAsFirst(T const& e) { //将e作为首节点插入链表
		return insertAfter(header, e); //相当于 e 作为头哨兵header的后继插入
	}

	ListNode<T>* insertAsLast(T const& e) { //将e作为末节点插入链表
		return insertBefore(trailer, e); //相当于 e 作为尾哨兵trailer的前驱插入
	}

	/*e 当做 p 的前驱插入*/
	ListNode<T>* insertBefore(ListNode<T>* p, T const& e) {
		ListNode<T>* x = new ListNode<T>(e, p->pred, p); //创建（耗时100倍）
		p->pred->succ = x; //建立链接，返回新节点的位置
		p->pred = x;
		_size++;
		return x;
	}

	/*e 当做 p 的后继插入*/
	ListNode<T>* insertAfter(ListNode<T>* p, T const& e) {
		ListNode<T>* x = new ListNode<T>(e, p, p->succ); //创建（耗时100倍）
		p->succ->pred = x;
		p->succ = x;
		_size++;
		return x;
	}
	/*删除合法位置p处节点，返回其数值*/
	T remove(ListNode<T> * p) {
		T e = p->data; //备份待删除节点数值（假设类型T可直接赋值）
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p; //释放内存
		_size--;
		return e; //返回备份数值
	}

	/*链表区间排序*/
	void sort(ListNode<T>* p, int n) {
		mergesort ( p, n );  //归并排序
	}

	//链表整体排序
	void sort() {
		sort(first(), _size);
	}

	int deduplicate() { //剔除无序链表中的重复节点
		if (_size < 2) return 0; //平凡链表自然无重复
		int oldSize = _size; //记录原规模
		ListNode<T>* p = header; int r = 0; //p从首节点开始
		while (trailer != (p = p->succ)) { //依次直到末节点
			ListNode<T>* q = find(p->data, r, p); //在p的r个（真）前驱中查找雷同者
			q ? remove(q) : r++; //若的确存在，则删除之；否则秩加一
		} //assert: 循环过程中的任意时刻，p的所有前驱互不相同
		return oldSize - _size; //列表规模变化量，即被删除元素总数
	}

	/*有序链表的去重操作，成批剔除重复元素，效率更高
	  要求：链表中的元素是有序的，且类型 T 是基本类型或已重载操作符 “!=”*/
	int uniquify() { 
		if (_size < 2) return 0; //平凡链表自然无重复
		int oldSize = _size; //记录原规模
		ListNode<T>* p = first(); ListNode<T>* q; //p为各区段起点，q为其后继
		while (trailer != (q = p->succ)) //反复考查紧邻的节点对(p, q)
			if (p->data != q->data) p = q; //若互异，则转向下一区段
			else remove(q); //否则（雷同），删除后者
		return oldSize - _size; //列表规模变化量，即被删除元素总数
	}

	/*若 r 大于等于 0，将第 r 个节点的值改为 e
	  若 r 小于 0，将倒数第 -r 个节点的值改为 e*/
	void set(int r, T e) {
		if (r > 0 && r >= _size) return;
		if (r < 0 && -r > _size) return;

		if (r >= 0) {
			ListNode<T>* p = first(); //从首节点出发
			while (0 < r--) p = p->succ; //顺数第r个节点即是
			p->data = e;
		}
		else {
			ListNode<T>* p = last(); //从首节点出发
			while (0 > ++r) p = p->pred; //顺数第r个节点即是
			p->data = e;
		}
	}
};
