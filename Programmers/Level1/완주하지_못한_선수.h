#pragma once

/*
	�������� ���� ���� [�ؽ�] (https://programmers.co.kr/learn/courses/30/lessons/42576)
		- ������ ���� ���� ��ϰ�, ���� ���� ����� �־��� ��, �������� ���� ������ �̸��� �����϶�.

		#0. ������ 1�� �̻�, 100, 000����
		#1. �������� �̸��� 1�� �̻�, 20�� ������ ���ĺ� �ҹ���
		#2. ���������� ���� �� ���� (�ߺ� ����)

		!0. �� �˰����� �з��� "�ؽ�"���� �ַ���� �������� �ʾұ� ������, 
			�ؽ����ε� �ַ��(==BestSolution)�� �ϴܿ� �߰��Ͽ����ϴ�.
*/

#include <string>
#include <vector>

#include <algorithm>
#include <map>	// for BestSolution

using namespace std;

string solution(vector<string> participant, vector<string> completion) {

	sort(participant.begin(), participant.end(),
		[/* void */](string& a, string& b) 
		noexcept(true) -> bool 
	{
		if (a.compare(b) < 0)
			return true;
		else  /* == else if (a.compare(b) > 0) */
			return false;
	});

	sort(completion.begin(), completion.end(), 
		[/* void */](string& a, string& b) 
		noexcept(true) -> bool
	{
		if (a.compare(b) < 0)
			return true;
		else /* == else if (a.compare(b) > 0) */
			return false;
	});

	for (int i = 0; i < completion.size(); ++i)
	{
		if (completion[i].compare(participant[i]) != 0)
		{
			return std::move(participant[i]);
		}
	}
	
	return std::move(participant[participant.size() - 1]);
}


/* 
	�ٸ� ����� Ǯ�̿� �ִ� Bestsolution�Դϴ�.
*/

string BestSolution(vector<string> participant, vector<string> completion) {
	string answer = "";
	map<string, int> strMap;
	for (auto elem : completion)
	{
		if (strMap.end() == strMap.find(elem))
			strMap.insert(make_pair(elem, 1));
		else
			strMap[elem]++;
	}

	for (auto elem : participant)
	{
		if (strMap.end() == strMap.find(elem))
		{
			answer = elem;
			break;
		}
		else
		{
			strMap[elem]--;
			if (strMap[elem] < 0)
			{
				answer = elem;
				break;
			}
		}
	}
	return answer;
}
