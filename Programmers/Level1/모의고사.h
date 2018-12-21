#pragma once

/*
	���ǰ�� [����Ž��] (https://programmers.co.kr/learn/courses/30/lessons/42840)
		- ������ 3���, ��� ����, ���� �迭�� �־��� ��, ���� ���� ���� �������� �ε����� �����϶�.

		#0. ������ �ִ� 10,000 ������ �����Ǿ��ֽ��ϴ�.
		#1. ���� ���� ������ ���� ����� ������ ���, return�ϴ� ���� �������� �������ּ���.
		
		!0. �� �˰����� �з��� "�ؽ�"���� �ַ���� �������� �ʾұ� ������,
		�ؽ����ε� �ַ��(==BestSolution)�� �ϴܿ� �߰��Ͽ����ϴ�.
*/

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {

	vector<vector<int>> studentCont	{ 
		{ 1, 2, 3, 4, 5}
	,	{ 2, 1, 2, 3, 2, 4, 2, 5 }
	,	{ 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 } 
	};
	
	std::vector<int> scoreCont(3, 0);

	for (int i = 0; i < answers.size(); ++i)
	{
		if (answers[i] == studentCont[0][i % studentCont[0].size()]) scoreCont[0]++;
		if (answers[i] == studentCont[1][i % studentCont[1].size()]) scoreCont[1]++;
		if (answers[i] == studentCont[2][i % studentCont[2].size()]) scoreCont[2]++;
	}

	int maxScore{ *max_element(scoreCont.begin(), scoreCont.end()) };

	std::vector<int> answer{};
	for (int i = 0; i < 3; ++i)
	{
		if (scoreCont[i] == maxScore) answer.emplace_back(i + 1);
	}

	return answer;
}