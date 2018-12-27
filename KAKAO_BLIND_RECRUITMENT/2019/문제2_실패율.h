#pragma once

/*
	2019 īī�� ���� ��ä 1�� �ڵ� �׽�Ʈ 2�� ����

	������ [����] (https://programmers.co.kr/learn/courses/30/lessons/42889#)
		- ��ü ���������� ���� N, ������ �̿��ϴ� ����ڰ� ���� �����ִ� ���������� ��ȣ�� ��� �迭 stages�� �Ű������� �־��� ��, 
		�������� ���� ������������ ������������ ���������� ��ȣ�� ����ִ� �迭�� return �ϵ��� solution �Լ��� �ϼ��϶�.

		#0. ex) N = 5, stages = [2, 1, 2, 6, 2, 4, 3, 3], result = [3,4,2,1,5]
		#1. N + 1 �� ������ ��������(N ��° ��������) ���� Ŭ���� �� ����ڸ� ��Ÿ����.
		#2. ���� �������� ���� ���������� �ִٸ� ���� ��ȣ�� ���������� ���� ������ �ϸ� �ȴ�.
		#3. ���������� ������ ������ ���� ��� �ش� ���������� �������� 0 ���� �����Ѵ�.
*/

#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

using namespace std;

class GameLog
{
	friend class GameLogManager;

	int			stageIndex;
	int			failCount;
	int			allCount;
	double		failRate;

public:
	GameLog(const int InStageIndex) noexcept
		: stageIndex(InStageIndex)
		, failCount(0)
		, allCount(0)
		, failRate(0.0f)
	{}
	~GameLog() = default;

public:
	inline bool operator>(const GameLog& other) const noexcept
	{
		return failRate == other.failRate 
			? !(stageIndex > other.stageIndex)
			: failRate > other.failRate;
	}
};

class GameLogManager
{
	vector<GameLog> logCont;

	const int stageNumber;
	const int playerNumber;

public:
	GameLogManager(const int InStageNumber, const int InPlayerNumber)
		: stageNumber(InStageNumber), playerNumber(InPlayerNumber)
		/*, logCont(InStageNumber, { 0, 0, 0.0f })*/
	{
		logCont.reserve(stageNumber + 2);	// 0 -> for Index Hash, stageNumber + 1 -> for All clear UserCount

		for (int i = 0; i < stageNumber + 2; ++i)
		{
			logCont.emplace_back(i);
		}
	}

	~GameLogManager() = default;

public:
	void CountFailCount(const vector<int>& InPlayerScores)
	{
		for (auto i : InPlayerScores)
		{
			++logCont[i].failCount;
		}
	}

	void ProcessCountAndRate()
	{
		logCont[stageNumber + 1].allCount = logCont[stageNumber + 1].failCount;

		for (int i = stageNumber + 1; i > 0; --i)
		{
			logCont[i - 1].allCount = logCont[i].allCount + logCont[i - 1].failCount;

			if (logCont[i - 1].allCount == 0)
				logCont[i - 1].failRate = 0;
			else 
			logCont[i - 1].failRate = static_cast<double>(logCont[i - 1].failCount) / logCont[i - 1].allCount;
		}
	}

	void SortResult()
	{
		// 0�� �ε��� ����.
		logCont.erase(logCont.begin());

		// ��� ���������� Ŭ������ ����� ������ �ʿ����.
		logCont.erase(logCont.end() - 1);

		sort(logCont.begin(), logCont.end(), [](const GameLog& a, const GameLog& b)->bool
		{
			return a > b;
		});
	}

	vector<int> GetAnswer()
	{
		vector<int> answer(logCont.size(), 0);

		for (int i = 0; i < logCont.size(); ++i)
		{
			answer[i] = logCont[i].stageIndex;
		}

		return answer;
	}
};

vector<int> solution(int n, vector<int> InPlayerScores)
{
	GameLogManager logManager(n, InPlayerScores.size());

	logManager.CountFailCount(InPlayerScores);
	logManager.ProcessCountAndRate();
	logManager.SortResult();

	return logManager.GetAnswer();
}
