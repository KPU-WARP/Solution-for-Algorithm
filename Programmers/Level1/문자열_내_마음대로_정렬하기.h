#pragma once

/*
	���ڿ� �� ������� �����ϱ� [��������] (https://programmers.co.kr/learn/courses/30/lessons/12915)
		- ���ڿ��� ������ ����Ʈ strings��, ���� n�� �־����� ��, �� ���ڿ��� �ε��� n��° ���ڸ� �������� �������� �����Ϸ� �մϴ�

		#0. ex) strings = [sun, bed, car] , n = 1 , return = [car, bed, sun]
		#1. �ε��� 1�� ���ڰ� ���� ���ڿ��� ���� �� ���, ���������� �ռ� ���ڿ��� ���ʿ� ��ġ�մϴ�.
		#2. ��� strings�� ������ ���̴� n���� Ů�ϴ�.

		#3. Sort�� 3��° ���ڿ� ����, �ΰ����� �ַ���� �����մϴ�.
			- 1. �Լ� ��ü�� Ȱ���� ���.
			- 2. ���� �Լ��� Ȱ���� ���.

		!0. ���� �Լ��� Ȱ���ϴ� �����, n�� ���� ������ ���� ���� ������ �ʿ��� �� ���� �����߽��ϴ�.
			(������ ���� ������ �� �Ƿ��� �����ؼ�..)
*/

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

// 1. �Լ� ��ü�� Ȱ���� ���.

class Comp
{
	int compIndex;
public:
	Comp(const int& InCompIndex) noexcept : compIndex(InCompIndex) {}
	~Comp() = default;

	[[nodiscard]] constexpr inline bool operator()(const string& a, const string& b) noexcept
	{
		return a[compIndex] == b[compIndex] ? a < b : a[compIndex] < b[compIndex];
	}
};

vector<string> solution_1(vector<string> strings, int n) 
{
	Comp compFunc(n);
	sort(strings.begin(), strings.end(), compFunc);
	
	return strings;
}


// 2. ���� �Լ��� Ȱ���� ���.

vector<string> solution_2(vector<string> strings, int n) 
{
	sort(strings.begin(), strings.end(), [&n](const string& a, const string& b) noexcept(true) -> bool
	{
		return a[n] == b[n] ? a < b : a[n] < b[n];
	} );
	
	return strings;
}


