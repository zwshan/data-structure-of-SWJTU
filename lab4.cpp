#include<iostream>
#include<cstdlib>
#include<windows.h>
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
	Vector(int c,bool isrev, int s = 0, T v = 0);
	Vector(Vector<T> const& v);
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
	void merge(Rank lo, Rank mi, Rank hi);
	void mergesort(Rank lo, Rank hi);
};

template<typename T> Vector<T>::Vector(int c, bool isrev ,int s, T v)
{
	//c = DEFAULT_CAPACITY;
	if (!isrev)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < c; _elem[_size++] = (rand() % 200000 + 1));
	}
	else
	{
		_elem = new T[_capacity = c];
		for (int i = 100000; i > 0; i--)
		{
			_elem[_size++] = i;
		}
	}
}
template<typename T> Vector<T>::Vector(Vector<T> const& v)
{
	int size=v.size();
	_elem = new T[size];
	for (_size = 0; _size < size; _size++)   //这里_size前面不可以再加int了 否则会出现局部变量使得全局变量不可见
	{
		_elem[_size] = v[_size];
	}
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
	cout << "===============================================[0,19]==================================================" << endl;
	for (int i = 0; i <= 19; i++)
	{
		cout << _elem[i] << " ";
	}
	cout << endl<<endl;
	cout << "===========================================[50000,50019]===============================================" << endl;
	for (int i = 50000; i <=50019; i++)
	{
		cout << _elem[i] << " ";
	}
	cout << endl<<endl;
	cout << "===========================================[99980,99999]===============================================" << endl;
	for (int i = 99980; i <= 99999; i++)
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
template<typename T>void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;
	int lb = mi - lo; T* B = new T[lb];
	for (int i = 0; i < lb;i++)
	{
		B[i] = A[i];
	}
	int lc = hi - mi;
	T* C = _elem + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
		{
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
		{
			A[i++] = C[k++];
		}
		
	}
	delete[]B;//应该在for循环的外面清空内存
}
template<typename T>void Vector<T>::mergesort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;   //箭头朝向那一边就是哪个方向的移
	mergesort(lo, mi); mergesort(mi, hi);
	merge(lo, mi, hi);
}
int main()
{
	int rank;
	int n1 = 0;
	int n2 = 0;
	int new_ele = 3;
	Vector<int> myvectorA(100000,false);
	Vector<int> myvectorA_copy = myvectorA;
	Vector<int> myvectorB(100000,true);
	Vector<int> myvectorB_copy = myvectorB;
	LARGE_INTEGER nFreqA;             //时钟频率
	LARGE_INTEGER nBeginTimeA;   //起始时间的频率计数
	LARGE_INTEGER nEndTimeA;   //终止时间的频率计数
	double time;         //时间
	QueryPerformanceFrequency(&nFreqA);          //获得系统时钟频率
	QueryPerformanceCounter(&nBeginTimeA);    //获得起始时间的计数
	myvectorA.mergesort(0, 100000);          //归并
	QueryPerformanceCounter(&nEndTimeA);       //获得终止时间的计数
	time = (double)(nEndTimeA.QuadPart - nBeginTimeA.QuadPart) / (double)nFreqA.QuadPart;                           //计算获得高精度时间
	cout <<"本次归并排序消耗的时间是"<< time<<endl;
	myvectorA.print();
	cout << endl;


	LARGE_INTEGER nFreqA_copy;             //时钟频率
	LARGE_INTEGER nBeginTimeA_copy;   //起始时间的频率计数
	LARGE_INTEGER nEndTimeA_copy;   //终止时间的频率计数
	QueryPerformanceFrequency(&nFreqA_copy);          //获得系统时钟频率
	QueryPerformanceCounter(&nBeginTimeA_copy);    //获得起始时间的计数
	myvectorA_copy.bubblesort();
	QueryPerformanceCounter(&nEndTimeA_copy);       //获得终止时间的计数
	time = (double)(nEndTimeA_copy.QuadPart - nBeginTimeA_copy.QuadPart) / (double)nFreqA_copy.QuadPart;                           //计算获得高精度时间
	cout << "本次冒泡排序消耗的时间是" << time << endl;
	myvectorA_copy.print();

	LARGE_INTEGER nFreqB;             //时钟频率
	LARGE_INTEGER nBeginTimeB;   //起始时间的频率计数
	LARGE_INTEGER nEndTimeB;   //终止时间的频率计数
	QueryPerformanceFrequency(&nFreqB);          //获得系统时钟频率
	QueryPerformanceCounter(&nBeginTimeB);    //获得起始时间的计数
	myvectorB.mergesort(0, 100000);          //归并
	QueryPerformanceCounter(&nEndTimeB);       //获得终止时间的计数
	time = (double)(nEndTimeB.QuadPart - nBeginTimeB.QuadPart) / (double)nFreqB.QuadPart;                           //计算获得高精度时间
	cout << "本次逆序元素归并排序消耗的时间是" << time << endl;
	myvectorB.print();
	cout << endl;

	LARGE_INTEGER nFreqB_copy;             //时钟频率
	LARGE_INTEGER nBeginTimeB_copy;   //起始时间的频率计数
	LARGE_INTEGER nEndTimeB_copy;   //终止时间的频率计数
	QueryPerformanceFrequency(&nFreqB_copy);          //获得系统时钟频率
	QueryPerformanceCounter(&nBeginTimeB_copy);    //获得起始时间的计数
	myvectorB_copy.bubblesort();          //逆序冒泡
	QueryPerformanceCounter(&nEndTimeB_copy);       //获得终止时间的计数
	time = (double)(nEndTimeB_copy.QuadPart - nBeginTimeB_copy.QuadPart) / (double)nFreqB_copy.QuadPart;                           //计算获得高精度时间
	cout << "本次逆序元素冒泡排序消耗的时间是" << time << endl;
	myvectorB_copy.print();
	cout << endl;



	return 0;
}