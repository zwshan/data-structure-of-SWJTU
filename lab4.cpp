#include<iostream>
#include<cstdlib>
#include<windows.h>
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
			cout << "���޴�Ԫ��" << endl;
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
	for (_size = 0; _size < size; _size++)   //����_sizeǰ�治�����ټ�int�� �������־ֲ�����ʹ��ȫ�ֱ������ɼ�
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
	delete[]B;//Ӧ����forѭ������������ڴ�
}
template<typename T>void Vector<T>::mergesort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;   //��ͷ������һ�߾����ĸ��������
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
	LARGE_INTEGER nFreqA;             //ʱ��Ƶ��
	LARGE_INTEGER nBeginTimeA;   //��ʼʱ���Ƶ�ʼ���
	LARGE_INTEGER nEndTimeA;   //��ֹʱ���Ƶ�ʼ���
	double time;         //ʱ��
	QueryPerformanceFrequency(&nFreqA);          //���ϵͳʱ��Ƶ��
	QueryPerformanceCounter(&nBeginTimeA);    //�����ʼʱ��ļ���
	myvectorA.mergesort(0, 100000);          //�鲢
	QueryPerformanceCounter(&nEndTimeA);       //�����ֹʱ��ļ���
	time = (double)(nEndTimeA.QuadPart - nBeginTimeA.QuadPart) / (double)nFreqA.QuadPart;                           //�����ø߾���ʱ��
	cout <<"���ι鲢�������ĵ�ʱ����"<< time<<endl;
	myvectorA.print();
	cout << endl;


	LARGE_INTEGER nFreqA_copy;             //ʱ��Ƶ��
	LARGE_INTEGER nBeginTimeA_copy;   //��ʼʱ���Ƶ�ʼ���
	LARGE_INTEGER nEndTimeA_copy;   //��ֹʱ���Ƶ�ʼ���
	QueryPerformanceFrequency(&nFreqA_copy);          //���ϵͳʱ��Ƶ��
	QueryPerformanceCounter(&nBeginTimeA_copy);    //�����ʼʱ��ļ���
	myvectorA_copy.bubblesort();
	QueryPerformanceCounter(&nEndTimeA_copy);       //�����ֹʱ��ļ���
	time = (double)(nEndTimeA_copy.QuadPart - nBeginTimeA_copy.QuadPart) / (double)nFreqA_copy.QuadPart;                           //�����ø߾���ʱ��
	cout << "����ð���������ĵ�ʱ����" << time << endl;
	myvectorA_copy.print();

	LARGE_INTEGER nFreqB;             //ʱ��Ƶ��
	LARGE_INTEGER nBeginTimeB;   //��ʼʱ���Ƶ�ʼ���
	LARGE_INTEGER nEndTimeB;   //��ֹʱ���Ƶ�ʼ���
	QueryPerformanceFrequency(&nFreqB);          //���ϵͳʱ��Ƶ��
	QueryPerformanceCounter(&nBeginTimeB);    //�����ʼʱ��ļ���
	myvectorB.mergesort(0, 100000);          //�鲢
	QueryPerformanceCounter(&nEndTimeB);       //�����ֹʱ��ļ���
	time = (double)(nEndTimeB.QuadPart - nBeginTimeB.QuadPart) / (double)nFreqB.QuadPart;                           //�����ø߾���ʱ��
	cout << "��������Ԫ�ع鲢�������ĵ�ʱ����" << time << endl;
	myvectorB.print();
	cout << endl;

	LARGE_INTEGER nFreqB_copy;             //ʱ��Ƶ��
	LARGE_INTEGER nBeginTimeB_copy;   //��ʼʱ���Ƶ�ʼ���
	LARGE_INTEGER nEndTimeB_copy;   //��ֹʱ���Ƶ�ʼ���
	QueryPerformanceFrequency(&nFreqB_copy);          //���ϵͳʱ��Ƶ��
	QueryPerformanceCounter(&nBeginTimeB_copy);    //�����ʼʱ��ļ���
	myvectorB_copy.bubblesort();          //����ð��
	QueryPerformanceCounter(&nEndTimeB_copy);       //�����ֹʱ��ļ���
	time = (double)(nEndTimeB_copy.QuadPart - nBeginTimeB_copy.QuadPart) / (double)nFreqB_copy.QuadPart;                           //�����ø߾���ʱ��
	cout << "��������Ԫ��ð���������ĵ�ʱ����" << time << endl;
	myvectorB_copy.print();
	cout << endl;



	return 0;
}