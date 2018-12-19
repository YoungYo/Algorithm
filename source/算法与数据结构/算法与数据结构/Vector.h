/******************************************************************************************
 * 微信公众号：AProgrammer
 ******************************************************************************************/
#pragma once
typedef int Rank; //秩
#define DEFAULT_CAPACITY 3 //默认初始容量（实际应用中可设置为更大）;
template <typename T> class Vector{ //向量模板类
    private: 
		Rank _size; //规模 
		int _capacity; //容量
		T* _elem; //数据区

    public:
        /* 默认的构造函数 */
        Vector(int c = DEFAULT_CAPACITY);
        /* 数组区间复制 */
        Vector(T const * A, Rank lo, Rank hi);
        /* 向量区间复制 */
        Vector(Vector<T> const& V, Rank lo, Rank hi);
        /* 向量整体复制 */
        Vector(Vector<T> const& V);
        /* 析构函数，释放内部空间 */
        ~Vector();
        
        /* T为基本类型，或已重载赋值操作符“=”。复制内容为A[lo]至A[hi-1]*/
        void copyFrom(T const *A, Rank lo, Rank hi);
        /* 向量空间不足时扩容 */
        void expand();
        /* 重载运算符“[]” 0 <= r < _size */
        T & operator[](Rank r) const ;
        /* 将元素e插入到秩为r的位置，0 <= r <= size */
        Rank insert(Rank r, T const & e);//O(n-r)
        /* 删除区间[lo, hi), 0 <= lo <= hi <= size */
        int remove(Rank lo, Rank hi); //O(n - hi)
        /* 单元素删除
         * 可以视作区间删除操作的特例：[r] = [r, r + 1) */
        T remove(Rank r);
        /* 查找操作
         * 对于无序向量而言：T为可判等的基本类型，或已重载操作符 “==” 或 “!=”
         * 对于有序向量而言：T为可比较的基本类型，或已重载操作符 “<” 或 “>” */
        Rank find(T const & e, Rank lo, Rank hi) const;
		//唯一化，删除向量中的重复元素，返回被删除元素数目
		int deduplicate();

		//对有序向量进行唯一化
        //返回被删除的元素的个数
        //若向量是无序的，则返回 -1
        int uniquify();
		
		/* 
		   查找有序向量中e的位置，若查找失败，返回不大于e的元素的最大秩
		   参数e：查找的目标元素
		   参数low：查找范围的上界
		   参数high：查找范围的下界的下一个位置
		*/
		Rank binSearch(T const& e, Rank low, Rank high);

        //判断向量是否有序
        //有序/无序序列中，任意/总有一对相邻元素顺序/逆序
        //因此，相邻逆序对的数目，可用以度量向量的逆序程度
        int disordered() const;

		/*冒泡排序
		  参数low：排序范围的下界
		  参数high：排序范围的上界的下一个位置*/
		void bubbleSort(Rank low, Rank high);
		Rank bubble(Rank low, Rank high);
		//交换两个元素的值
		void swap(T &a, T &b);

		/*归并排序
		  参数low：排序范围的下界
		  参数high：排序范围的上界的下一个位置*/
		void mergeSort(Rank low, Rank high);
		void merge(Rank low, Rank mid, Rank high);

		//返回两个数中的较大者
		int max(int a, int b);
		//返回向量的规模 _size
		int size();

        //重载 “[]” 操作符，返回引用，这样才可以对返回值赋值
        T& operator[] (int i);

		//判断向量是否为空
		bool empty() {
			return _size > 0 ? false : true;
		}
};

/* 默认的构造函数 */
template<typename T>
Vector<T>::Vector(int c){
    _elem = new T[_capacity = c];
    _size = 0;
}
/* 数组区间复制 */
template<typename T>
Vector<T>::Vector(T const *A, Rank lo, Rank hi){
    copyFrom(A, lo, hi);
}
/* 向量区间复制 */
template<typename T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi){
    copyFrom(V._elem, lo, hi);
}
/* 向量整体复制 */
template<typename T>
Vector<T>::Vector(Vector<T> const& V){
    copyFrom(V._elem, 0, V._size);
}
/* 析构函数，释放内部空间 */
template<typename T>
Vector<T>::~Vector(){
    delete [] _elem;
}

/* T为基本类型，或已重载赋值操作符“=”。复制内容为A[lo]至A[hi-1]*/
template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi){
    _elem = new T[_capacity = 2 * (hi - lo)]; //分配空间
    _size = 0; //规模清零
    while(lo < hi){ //A[lo, hi)内的元素逐一
        _elem[_size++] = A[lo++]; //复制至_elem[0, hi-lo]
    }
}
/* 向量空间不足时扩容 */
template<typename T>
void Vector<T>::expand(){
    if(_size < _capacity) //尚未满员时，不必扩容
      return;
    _capacity = max(_capacity, DEFAULT_CAPACITY); //不低于最小容量
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //容量加倍
    for (int i = 0; i < _size; i++)//复制原向量内容
      _elem[i] = oldElem[i]; //T为基本类型，或已重载运算符“=”
    delete [] oldElem; //释放原空间
}
/* 重载运算符“[]” 0 <= r < _size */
template<typename T>
T & Vector<T>::operator[](Rank r) const {
    return _elem[r];
}
/* 将元素e插入到秩为r的位置，0 <= r <= size */
template<typename T>
Rank Vector<T>::insert(Rank r, T const & e){//O(n-r)
    expand(); //若有必要，扩容
    for(int i = _size; i > r; i--){ //自后向前
        _elem[i] = _elem[i-1]; //后继元素顺次后移一个单元
    }
    _elem[r] = e;
    _size++; //置入新元素，更新容量
    return r; //返回秩
}
/* 删除区间[lo, hi), 0 <= lo <= hi <= size */
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi){ //O(n - hi)
    if(lo == hi) //出于效率考虑，单独处理退化情况
      return 0;
    while (hi < _size) //[hi, _size)顺次前移hi-lo位
      _elem[lo++] = _elem[hi++];
    _size = lo; //更新规模，若有必要则缩容
    return hi - lo; //返回被删除元素的数目
}
/* 单元素删除
 * 可以视作区间删除操作的特例：[r] = [r, r + 1) */
template<typename T>
T Vector<T>::remove(Rank r){
    T e = _elem[r]; //备份被删除的元素
    remove(r, r + 1); //调用区间删除算法
    return e; //返回被删除的元素
}
/* 查找操作
 * 对于无序向量而言：T为可判等的基本类型，或已重载操作符 “==” 或 “!=”
 * 对于有序向量而言：T为可比较的基本类型，或已重载操作符 “<” 或 “>” */
template<typename T>
Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const{
    //O(hi - lo) = O(n)，在命中多个元素时，可返回秩最大者
    while((lo < hi--) && e != _elem[hi]); //逆向查找
    return hi; //hi < lo意味着失败；否则hi即命中元素的秩
}

//唯一化，删除向量中的重复元素，返回被删除元素数目
template<typename T>
inline int Vector<T>::deduplicate()
{
	int oldSize = _size; //记录原始规模
	Rank i = 1; //从 _elem[i] 开始
	while (i < _size) { //自前向后逐一考察各元素 _elem[i]
		find(_elem[i], 0, i) < 0 ? //在前缀中寻找雷同者
			i++ //若无雷同则继续考察其后继
: remove(i); //否则删除雷同者（至多 1 个？！）
	}
	return oldSize - _size; //向量规模变化量，即删除元素总数
}

template <typename T>
int Vector<T>::uniquify() {
	if (disordered())
		return -1;
	Rank i = 0, j = 0; //各对互异“相邻”元素的秩
	while (++j < _size) { //逐一扫描，直至末元素
		if (_elem[i] != _elem[j]) { //跳过雷同者，发现不同元素时，向前移至紧邻于前者右侧
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	return j - i; //向量规模变化量，即被删除元素总数
}

template<typename T>
inline Rank Vector<T>::binSearch(T const & e, Rank lo, Rank hi)
{
	while (lo < hi) { //不变性：A[0, lo) <= e < A[hi, n)
		Rank mid = (lo + hi) >> 1; //以中点为轴点，经比较后确定深入
		(e < _elem[mid]) ? hi = mid : lo = mid + 1; //[lo, mid)或(mid, hi)
	}//出口时，A[lo = hi]为大于e的最小元素
	return --lo; //即lo-1即不大于e的元素的最大秩
}

template<typename T>
int Vector<T>::disordered() const {
	int n = 0; //计数器
	for (int i = 1; i < _size; i++) //逐一检查各对相邻元素
		n += (_elem[i - 1] > _elem[i]); //逆序则计数
	return n; //返回值n是向量中逆序对的个数，当且仅当 n = 0 时向量有序
}//若只需判断是否有序，则首次遇到逆序对之后，即可立即终止

//冒泡排序
template<typename T>
void Vector<T>::bubbleSort(Rank low, Rank high) {
	while (low < (high = bubble(low, high))); //逐趟扫描交换，直至全序
}
template<typename T>
Rank Vector<T>::bubble(Rank low, Rank high) {
	Rank last = low; //最右侧的逆序对初始化为[low - 1, low]
	while (++low < high) { //自左向右，逐一检查各对相邻元素
		if (_elem[low - 1] > _elem[low]) { //若逆序，则更新最右侧逆序对位置记录，并交换
			last = low;
			swap(_elem[low - 1], _elem[low]);
		}
	}
	return last; //返回最右侧的逆序对位置
}
//交换a、b两个元素的值
template<typename T>
void Vector<T>::swap(T &a, T &b) {
	if (typeid(T) == typeid(int)) {
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	else {
		T temp = a;
		a = b;
		b = a;
	}
}
template<typename T>
inline void Vector<T>::mergeSort(Rank low, Rank high)
{
	Rank step = 1;
	while (step < high) {
		for (Rank i = low; i < high; i += step << 1) {
			Rank lo = i, hi = (i + (step << 1)) <= high ? (i + (step << 1)) : high; //定义二路归并的上界与下界 
			Rank mid = i + step <= high ? (i + step) : high;
			merge(lo, mid, hi);
		}

		//将i和i+step这两个有序序列进行合并
		//序列长度为step
		//当i以后的长度小于或者等于step时，退出
		step <<= 1;//在按某一步长归并序列之后，步长加倍
	}
}
template<typename T>
inline void Vector<T>::merge(Rank low, Rank mid, Rank high){
	T* A = _elem + low; //合并后的向量A[0, high - low) = _elem[low, high)
	int lb = mid - low;
	T* B = new T[lb]; //前子向量B[0, lb) = _elem[low, mid)
	for (Rank i = 0; i < lb; B[i] = A[i++]); //复制前子向量B
	int lc = high - mid;
	T* C = _elem + mid; //后子向量C[0, lc) = _elem[mid, high)

	//第一种处理方式
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) { //B[j]和C[k]中小者转至A的末尾
		if (j < lb && k < lc) //如果j和k都没有越界，那么就选择B[j]和C[k]中的较小者放入A[i]
			A[i++] = B[j] < C[k] ? B[j++] : C[k++];
		if (j < lb && lc <= k) //如果j没有越界而k越界了，那么就将B[j]放入A[i]
			A[i++] = B[j++];
		if (lb <= j && k < lc) //如果k没有越界而j越界了，那么就将C[k]放入A[i]
			A[i++] = C[k++];
	}

	//第二种处理方式
	//for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) { //B[j]和C[k]中小者转至A的末尾
	//	if ((j < lb) && (lc <= k || B[j] <= C[k])) //C[k]已无或不小
	//		A[i++] = B[j++];
	//	if ((k < lc) && (lb <= j || C[k] < B[j])) //B[j]已无或更大
	//		A[i++] = C[k++];
	//}//该循环实现紧凑，但就效率而言，不如拆分处理
	delete[] B; //释放临时空间B
}

template<typename T>
int Vector<T>::max(int a, int b) {
	return a > b ? a : b;
}

template<typename T>
inline int Vector<T>::size()
{
	return _size;
}

template<typename T>
T& Vector<T>::operator[] (int i){
    return _elem[i];
}
