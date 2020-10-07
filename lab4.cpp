#include<iostream>
#include<cstdlib>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 1000  //宏定义后面不允许加分号

template <typename T>class Vector
{
protected:
	Rank _size;
	int _capacity;
	T* _elem;
	void expand();

public:
	Vector(int c, int s = 0, T v = 0);
	~Vector() { delete[] _elem; }
	T& operator[] (Rank r)const;
	Rank insert(Rank r, T const& e);
	void bubble(Rank lo, Rank hi);
	void bubblesort();
	Rank size() const { return _size; }
	void print();
	int remove(Rank lo, Rank hi);
	T remove(Rank r);
	Rank find(T const& e, Rank lo, Rank hi)const;
	Rank find(T const& e)const;
	int uniquify();
	Rank binSearch(T const& e, Rank lo, Rank hi)
	{
		while (lo < hi)
		{
			Rank mi = (lo + hi) >> 1;
			(e < _elem[mi]) ? hi = mi : lo = mi + 1;
		}
		if (_elem[lo - 1] != e)
			cout << "查无此元素" << endl;
		return --lo;
	}
	Rank binSearch_left(T const& e, Rank lo, Rank hi);
};
template<typename T> Vector<T>::Vector(int c, int s, T v)
{
	//c = DEFAULT_CAPACITY;
	_elem = new T[_capacity = c];
	for (_size = 0; _size < c; _elem[_size++] = (rand() % 10 + 1));
}
template<typename T>Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	while ((lo < hi--) && (e != _elem[hi]))
		;
	if (hi < lo)
	{
		cout << "查无此元素" << endl;
		return -1;
	}
	else
		return hi;

}
template<typename T>Rank Vector<T>::find(T const& e)const
{
	int lo = 0;
	int hi = _size;
	while ((lo < hi--) && (e != _elem[hi]))
		;
	if (hi < lo)
	{
		cout << "查无此元素" << endl;
		return -1;
	}
	else
		return hi;

}
template<typename T>void Vector<T>::expand()
{
	if (_capacity < DEFAULT_CAPACITY)
	{
		_capacity = DEFAULT_CAPACITY;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1]; //一个数左移相当于乘以2
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];
	}

}
template<typename T>Rank Vector<T>::insert(Rank r, T const& e)
{

	if (r < 0 || r>_size)
	{
		cout << "位置非法！" << endl;
		return -1;
	}

	else
	{
		expand();
		for (int i = _size; i > r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;
		return r;
	}
}
template<typename T>void Vector<T>::print()
{
	for (int i = 0; i < _size; i++)
	{
		cout << _elem[i] << " ";
	}
	cout << endl;
}
template<typename T>void Vector<T>::bubble(Rank lo, Rank hi)
{
	T temp = _elem[hi];
	_elem[hi] = _elem[lo];
	_elem[lo] = temp;
}
template<typename T>void Vector<T>::bubblesort()
{
	bool sorted = false;
	int n = _size;
	while (!sorted)
	{
		sorted = true;
		for (int i = 1; i < n; i++)
		{
			if (_elem[i - 1] > _elem[i])
			{
				bubble(i - 1, i);// 写代码的时候在这里卡了好久，本来应该传入的是元素的索引，但是自己传入了元素自身的值
				sorted = false;
			}
		}
		n--;
	}
}
template<typename T>int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo < 0)
	{
		cout << "非法输入" << endl;
		return -1;
	}
	if (lo == hi)
		return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	return hi - lo;
}
template<typename T>T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}
template<typename T> T& Vector<T>::operator[](Rank r)const
{
	return _elem[r];
}
template<typename T> int Vector<T>::uniquify()
{
	int oldSize = _size;
	int i = 1;
	while (i < _size)
		_elem[i - 1] == _elem[i] ? remove(i) : i++;
	return oldSize - _size;

}
template<typename T> Rank Vector<T>::binSearch_left(T const& e, Rank lo, Rank hi)
{
	int min = lo;
	int max = hi - 1;
	int mid = 0;
	while (min < max - 1)
	{
		mid = max - (max - min) / 2;
		if (_elem[mid] > e)
		{
			max = mid;
		}
		else if (_elem[mid] < e)
		{
			min = mid;
		}
		else
		{
			max = mid;
		}
	}
	if (_elem[min] == e)
	{
		return min;
	}
	else if (_elem[max] == e)
	{
		return max;
	}
	else
	{
		cout << "查无此元素" << endl;
		return -1;
	}
}
int main()
{
	int rank;
	int n1 = 0;
	int n2 = 0;
	int new_ele = 3;
	Vector<int> myvector(10);
	myvector.bubblesort();      //将有序向量变成无序向量
	cout << "初始化的有序向量为：" << endl;
	myvector.print();
	cout << "有序插入一个新元素后的有序向量为：" << endl;
	n1 = myvector.binSearch(new_ele, 0, 10);   //刚开始测这段代码的时候没有进行排序，所以无法得到正确结果，二分查找适用于有序向量
	myvector.insert(n1 + 1, new_ele);        //利用二分查找的正确结果插入元素
	myvector.print();
	cout << "查找某一个元素并统计其出现的次数:" << endl;
	n1 = myvector.binSearch_left(5, 0, myvector.size());
	n2 = myvector.binSearch(5, 0, myvector.size());
	cout << "第一次出现的位置：" << n1 << endl;
	cout << "第二次出现的位置：" << n2 << endl;
	cout << "统计其出现的次数:" << n2 - n1 + 1 << endl;
	cout << "输出删除这个元素后的向量:" << endl;
	myvector.remove(n1, n2 + 1);
	myvector.print();



	return 0;
}