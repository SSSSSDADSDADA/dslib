/*
 * Common header file for dslib
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
 * Copyright (C) 2015 by Arun Prakash Jana <engineerarun@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#pragma once
typedef char StackDataType;

typedef struct Stack
{
	StackDataType* St;
	int top;  
	int capacity;
}Stack;

void InitStack(Stack* ps,int capacity);
void DestroyStack(Stack* ps);
void PushStack(Stack* ps, StackDataType x);
void PopStack(Stack* ps);

StackDataType TopStack(Stack* ps);
int SizeStack(Stack* ps);
bool EmptyStack(Stack* ps);
void PrintfStack(Stack* ps);
void swap(int* p1, int* p2);

int GetMidNum(int* a, int left, int right);

void QsortPart1(int* a, int left, int right) ;

void QsortPart2(int* a, int left, int right) ;

void QsortPart3(int* a, int left,int right) ;

void BubbleSort(int* a, int n);

void qsortTest();
void Qsort(int* a, int n);
void QsortTest();
void MergeSort(int* a, int n);
void MergeSortTest();
void BubbleSortTest();
void _MergeSort(int* a, int left, int right, int* tmp);
