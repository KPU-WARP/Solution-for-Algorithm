#pragma once
/*
	�Ҽ��� �� (https://programmers.co.kr/learn/courses/30/lessons/14406)
		- 2���� N������ ��� �Ҽ��� ���� ���ϼ���.

		#0. N�� 2�̻�, 10,000,000����
		#1. ȿ���� �׽�Ʈ, 1�� �̸����� ����

		#2. �� �ַ���� �����佺�׳׽��� ü Ȱ��.
*/
#include <vector>
#include <cmath>

using namespace std;

long long solution(int N) {
	vector<bool> bitCont(N+1, true);

	{//block for limit "newIndex" scope!
		int newIndex;

		for (int i = 3; i <= sqrt(N); i += 2)
		{
			newIndex = i + i;

			while (newIndex < N + 1)
			{
				bitCont[newIndex] = false;
				newIndex += i;
			}
		}
	}

	long long answer = 2;

	for (int i = 3; i < N + 1; i += 2)
	{
		if (bitCont[i]) answer += i;
	}

	return answer;
}