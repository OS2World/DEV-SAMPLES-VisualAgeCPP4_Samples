/*
 * IBM VisualAge C++ Professional, Version 4.0
 *
 * Licensed Materials - Property of IBM
 *
 * (C) Copyright IBM Corp. 1998. All Rights Reserved.
 *
 * The following [enclosed] code is sample code created by IBM
 * Corporation.  This sample code is not part of any standard IBM product
 * and is provided to you solely for the purpose of assisting you in the
 * development of your applications.  The code is provided 'AS IS',
 * without warranty of any kind.  IBM shall not be liable for any damages
 * arising out of your use of the sample code, even if they have been
 * advised of the possibility of such damages.
 */

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <class T> class pq {
	vector<T> vec;
public:
	pq(vector<T>& v) : vec(v)
	{
		make_heap(vec.begin(), vec.end());
	}

	vector<T>& toSequence()
	{
		vector<T>* copy = new vector<T>(vec);
		sort_heap(copy->begin(), copy->end());
		return *copy;
	}

	void push(const T& x)
	{
		vec.push_back(x);
		push_heap(vec.begin(), vec.end());
	}

	void pop()
	{
		pop_heap(vec.begin(), vec.end());
		vec.pop_back();
	}

	const T& top()
	{
		return vec.front();
	}

	bool empty()
	{
		return vec.empty();
	}

};

int main()
{
	vector<int> vec;

	vec.push_back(1);
	vec.push_back(17);
	vec.push_back(-3);
	vec.push_back(14);

	pq<int> q(vec);

	q.push(5);

	vector<int> vec2 = q.toSequence();
	for (int i = 0; i < vec2.size(); i++)
		cout << vec2[i] << endl;

	while (!q.empty()) {
		cout << q.top() << endl;
		q.pop();
	}

	return 0;
}
