#pragma once

/*
	2019 īī�� ���� ��ä 1�� �ڵ� �׽�Ʈ 4�� ����

	������ �Թ� ���̺� (https://programmers.co.kr/learn/courses/30/lessons/42891)
		- �� ������ ��� �Դµ� �ʿ��� �ð��� ����ִ� �迭 food_times, ��Ʈ��ũ ��ְ� �߻��� �ð� K �ʰ� �Ű������� �־��� �� 
		�� �� ���ĺ��� �ٽ� �����ϸ� �Ǵ��� return �ϵ��� solution �Լ��� �ϼ��϶�.

		#0. ex) food_Times = [3, 1, 2], k = 5, result = 1
		#1. ���� �� �����ؾ� �� ������ ���ٸ� -1�� ��ȯ�ϸ� �ȴ�.
	
		!0. ȿ���� �׽�Ʈ
			- food_times �� ���̴� 1 �̻� 200,000 �����̴�.
			- food_times �� ���Ҵ� 1 �̻� 100,000,000 ������ �ڿ����̴�.
			- k�� 1 �̻� 2 x 10^13 ������ �ڿ����̴�.
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <algorithm>

using namespace std;

class Food
{
	friend class MuziLive;

	int		index;
	int		remainCount;

public:
	Food(int InIndex, int InRemainCount)
		: index(InIndex)
		, remainCount(InRemainCount)
	{}

	~Food() = default;
public:
	inline int GetIndex() const noexcept { return index; }
	inline int GetCount() const noexcept { return remainCount; }
};

class MuziLive
{
	vector<Food>			foods;	// ������ food �������� food����....

public:
	MuziLive(const vector<int>& InFoods)
	{
		for (int i = 0; i < InFoods.size() ; ++i)
		{
			foods.emplace_back(i + 1, InFoods[i]);
		}

		sort(foods.begin(), foods.end(), [](const Food& a, const Food& b) -> bool {
			return a.GetCount() < b.GetCount();
		});
	}
	~MuziLive() = default;

public:
	int operator()(long long InremainTime)
	{
		long long remainTime{ InremainTime };
		long long oldTotal{};
		long long total{};

		const int orginSize = foods.size();

		for (int i = 0; i < orginSize; i++)
		{
			oldTotal = total;
			if (i == 0) 
			{
				if (orginSize * foods[0].remainCount <= remainTime)
				{
					total = (orginSize) * foods[i].remainCount;
					continue;
				}
			}
			else 
			{
				total += (foods[i].remainCount - foods[i - 1].remainCount) * (orginSize - i);
				
				if (total <= remainTime) 
					continue;
			}

			remainTime -= oldTotal;

			sort(foods.begin() + i, foods.end(), 
				[](const Food& a, const Food& b) -> bool {
				return a.GetIndex() < b.GetIndex();
			});

			int nowSize = orginSize - i;
			return foods[i + (remainTime % nowSize)].index;
		}
		return -1;
	}
};

int solution(vector<int> InFoodTimes, long long n)
{
	MuziLive muziLive(InFoodTimes);
	return muziLive(n);
}