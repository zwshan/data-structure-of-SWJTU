#include<iostream>
#include<cstdlib>
using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 1000  //�궨����治����ӷֺ�

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
			cout << "���޴�Ԫ��" << endl;
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
		cout << "���޴�Ԫ��" << endl;
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
		cout << "���޴�Ԫ��" << endl;
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
	_elem = new T[_capacity <<= 1]; //һ���������൱�ڳ���2
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];
	}

}
template<typename T>Rank Vector<T>::insert(Rank r, T const& e)
{

	if (r < 0 || r>_size)
	{
		cout << "λ�÷Ƿ���" << endl;
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
				bubble(i - 1, i);// д�����ʱ�������￨�˺þã�����Ӧ�ô������Ԫ�ص������������Լ�������Ԫ�������ֵ
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
		cout << "�Ƿ�����" << endl;
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
		cout << "���޴�Ԫ��" << endl;
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
	myvector.bubblesort();      //���������������������
	cout << "��ʼ������������Ϊ��" << endl;
	myvector.print();
	cout << "�������һ����Ԫ�غ����������Ϊ��" << endl;
	n1 = myvector.binSearch(new_ele, 0, 10);   //�տ�ʼ����δ����ʱ��û�н������������޷��õ���ȷ��������ֲ�����������������
	myvector.insert(n1 + 1, new_ele);        //���ö��ֲ��ҵ���ȷ�������Ԫ��
	myvector.print();
	cout << "����ĳһ��Ԫ�ز�ͳ������ֵĴ���:" << endl;
	n1 = myvector.binSearch_left(5, 0, myvector.size());
	n2 = myvector.binSearch(5, 0, myvector.size());
	cout << "��һ�γ��ֵ�λ�ã�" << n1 << endl;
	cout << "�ڶ��γ��ֵ�λ�ã�" << n2 << endl;
	cout << "ͳ������ֵĴ���:" << n2 - n1 + 1 << endl;
	cout << "���ɾ�����Ԫ�غ������:" << endl;
	myvector.remove(n1, n2 + 1);
	myvector.print();



	return 0;
}