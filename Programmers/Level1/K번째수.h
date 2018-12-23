#pragma once

/*
	K��° �� [����] (https://programmers.co.kr/learn/courses/30/lessons/42748)
		- �迭 array�� i��° ���ں��� j��° ���ڱ��� �ڸ��� �������� ��, k��°�� �ִ� ���� ���Ϸ� �մϴ�.

		#0. ex) array = [1, 5, 2, 6, 3, 7, 4] , commands = [[2, 5, 3], [4, 4, 1], [1, 7, 3]] , return = [5, 6, 3]
*/

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;
	answer.reserve(commands.size());

	for (auto command = commands.cbegin(); command != commands.cend(); ++command)
	{
		vector<int> candidateCont;

		for (int arrIndex = (*command)[0] - 1; arrIndex <= (*command)[1] - 1; ++arrIndex)
		{
			candidateCont.insert(
				upper_bound(candidateCont.cbegin(), candidateCont.cend(), array[arrIndex]),	
				array[arrIndex]
			);
		}

		answer.emplace_back(candidateCont[(*command)[2] - 1]);
	}
	
	return answer;
}
