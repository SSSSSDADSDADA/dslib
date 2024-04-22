/*
 * Sort implementation
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
 * Copyright (C) 2014 by Arun Prakash Jana <engineerarun@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dslib.  If not, see <http://www.gnu.org/licenses/>.
 */
 #include "sort.h"
 // 初始化栈
void InitStack(Stack* ps, int capacity) {
    ps->St = (StackDataType*)malloc(sizeof(StackDataType) * capacity);
    ps->top = -1;
    ps->capacity = capacity;
}

// 销毁栈
void DestroyStack(Stack* ps) {
    free(ps->St);
    ps->St = NULL;
    ps->top = -1;
    ps->capacity = 0;
}

// 入栈
void PushStack(Stack* ps, StackDataType x) {
    if (ps->top == ps->capacity - 1) {
        return;
    }
    ps->St[++ps->top] = x;
}

// 出栈
void PopStack(Stack* ps) {
    if (ps->top == -1) {
        return;
    }
    ps->top--;
}

// 返回栈顶元素
StackDataType TopStack(Stack* ps) {
    if (ps->top == -1) {
        exit(EXIT_FAILURE);
    }
    return ps->St[ps->top];
}

// 返回栈大小
int SizeStack(Stack* ps) {
    return ps->top + 1;
}

// 检查栈是否为空
bool EmptyStack(Stack* ps) {
    return ps->top == -1;
}
void swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int GetMidNum(int* a, int left, int right)   //Three numbers are taken in the middle
{
	int mid = (left + right) >> 1;
	if (a[left] > a[right])
	{
		if (a[right] > a[mid])
		{
			return right;
		}
		else if (a[mid] > a[left])
		{
			return left;
		}
		else
		{
			return mid;
		}
	}
	else
	{
		if (a[left] > a[mid])
		{
			return left;
		}
		else if (a[mid] > a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
}
void QsortPart1(int* a, int left, int right)   //Digging method
{
	if (left >= right)
	{
		return;
	}

	int mid = GetMidNum(a, left, right);

	int begin = left;
	int end = right;
	swap(&a[mid], &a[left]);
	int key = a[left];
	int hole = left;

	while (begin < end)
	{
		while(begin < end && a[end] >= key)
		{
			end--;
		}
		a[hole] = a[end];
		hole = end;
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		a[hole] = a[begin];
		hole = begin;
	}
	hole = begin;
	a[hole] = key;

	QsortPart1(a, left, hole - 1);
	QsortPart1(a, hole + 1, right);
}

void QsortPart2(int* a, int left, int right)   //Left and right method
{
	if (left >= right)
	{
		return;
	}
	int end = right;
	int mid = GetMidNum(a, left, right);
	int begin = left;

	swap(&a[left], &a[mid]);
	int key = left;

	while (begin < end)
	{
		while (end > begin && a[end] >= a[key])
		{
			end--;
		}
		while (end > begin && a[begin] <= a[key])
		{
			begin++;
		}
		swap(&a[begin], &a[end]);

		/*if (begin == end)
		{
			swap(&a[begin], &a[key]);
		}*/
	}
	swap(&a[begin], &a[key]);

	QsortPart2(a, left, begin - 1);
	QsortPart2(a, begin + 1, right);
}

void QsortPart3(int* a, int left,int right)  // Before and after method
{

	if (left >= right)
	{
		return;
	}

	int mid = GetMidNum(a, left, right);
	swap(&a[left], &a[mid]);

	int prev = left;
	int cur = prev + 1;

	int key = left;

	while (cur <= right)
	{
		/*if (a[cur] >= a[key])
		{
			cur++;
		}
		else
		{
			prev++;
			swap(&a[prev], &a[cur]);
			cur++;
		}*/
		if (a[cur] < a[key] && prev++ != cur)    //If the value of prev++ is the same as the current value of cur, it will not be swapped
		{
			swap(&a[prev], &a[cur]);
		}
		cur++;
	}
	swap(&a[key], &a[prev]);

	QsortPart3(a, left, prev - 1);
	QsortPart3(a, prev + 1, right);
}

void BubbleSort(int* a, int n)
{
	int end = 1;
	while (end < n)
	{
		for (int i = 0; i < n - end; i++)
		{
			if (a[i] > a[i + 1])
			{
				swap(&a[i], &a[i + 1]);
			}
		}
		end++;
	}
}
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}
	//1.
	int mid = (left + right) >> 1;
	// [left,mid]  [mid+1,right];
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	int index = left;
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;

	//鲢
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
		
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}

	//
	for (int i = left; i <= right; i++)
	{
		a[i] = tmp[i];
	}
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	assert(tmp);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
	tmp = NULL;
}



int _Qsort(int* a, int left,int right)
{
	int prev = left;
	int cur = left + 1;
	int key = left;

	while (cur <= right)
	{
		if (a[cur] < a[key])
		{
			prev++;
			swap(&a[cur], &a[prev]);
		}
		cur++;
	}
	
	swap(&a[prev], &a[key]);

	return prev;
}

void Qsort(int* a, int n)
{
	Stack St;
	InitStack(&St,n);

	PushStack(&St, n-1);
	PushStack(&St, 0);

	while (!EmptyStack(&St))
	{
		int left = TopStack(&St);
		PopStack(&St);

		int right = TopStack(&St);
		PopStack(&St);

		int indexkey = _Qsort(a, left, right);
		//  [left,indexkey-1] indexkey  [indexkey+1,right]


		if (indexkey + 1 < right)
		{
			PushStack(&St, right);
			PushStack(&St, indexkey + 1);
		}
		if (left < indexkey - 1)
		{
			PushStack(&St, indexkey - 1);
			PushStack(&St, left);
		}
	}

	DestroyStack(&St);
}

void QsortTest()
{
	int a[] = { 6,2,3,1,4,8,5,9,7};
	Qsort(a, sizeof(a)/sizeof(a[0]));
}

void MergeSortTest()
{
	int a[] = { 10, 6, 7, 1, 3, 9, 4, 2 };
	MergeSort(a, sizeof(a) / sizeof(a[0]));
}
void qsortTest()
{
	int a[] = { 6,1,2,7,9,3,4,5,10,8 };

	//QsortPart1(a, 0 ,sizeof(a) / sizeof(a[0]) - 1);
	//QsortPart2(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	QsortPart3(a, 0, sizeof(a) / sizeof(a[0]) - 1);
}

void BubbleSortTest()
{
	int a[] = { 6,1,2,7,9,3,4,5,10,8 };
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
}



