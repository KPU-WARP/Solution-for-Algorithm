#pragma once

/*
	2019 īī�� ���� ��ä 1�� �ڵ� �׽�Ʈ 1�� ����

	����ä�ù� [] (https://programmers.co.kr/learn/courses/30/lessons/42888)
		- ä�ù濡 ������ �����ų�, �г����� ������ ����� ��� ���ڿ� �迭 record�� �Ű������� �־��� ��, 
		��� ����� ó���� ��, ���������� ���� ������ ����� ���� �Ǵ� �޽����� ���ڿ� �迭 ���·� return �ϵ��� solution �Լ��� �ϼ��϶�.

		#0. ex) 
				input - ["Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"]
				output - ["Prodo���� ���Խ��ϴ�.", "Ryan���� ���Խ��ϴ�.", "Prodo���� �������ϴ�.", "Prodo���� ���Խ��ϴ�."]
		#1. record�� ������ ���� ���ڿ��� ��� �迭�̸�, ���̴� 1 �̻� 100,000 �����̴�.
		#2. ��� ������ [���� ���̵�]�� �����Ѵ�.
		#3. �� �ܾ�� �������� ���еǾ� ������, ���ĺ� �빮��, �ҹ���, ���ڷθ� �̷�����ִ�.
		#4. ä�ù濡�� ���� ������ �г����� �����ϴ� �� �߸� �� �Է��� �־����� �ʴ´�.
		#5. ù �ܾ�� Enter, Leave, Change �� �ϳ��̴�.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using _ID = basic_string<char, char_traits<char>, allocator<char>>;;
using _Nickname = basic_string<char, char_traits<char>, allocator<char>>;;
using _Iter = std::map<_ID, _Nickname>::iterator;

class UserDataManager
{
	std::map<_ID, _Nickname> userDataCont;

public:
	UserDataManager() = default;
	~UserDataManager() = default;

	_Iter EnterUser(const _ID& InUserId, const _Nickname& InNickName)
	{
		_Iter iter = userDataCont.find(InUserId);
		if (/*_Iter iter = userDataCont.find(InUserId);*/ iter == userDataCont.end())
		{
			return userDataCont.insert(pair<_ID, _Nickname>(InUserId, InNickName)).first;
		}
		iter->second = InNickName;
		return iter;
	}

	_Iter LeaveUser(const string& InUserId)
	{
		// �ش� ���̵��� ������ ���� ����� ���� ������� ����.(����)
		return userDataCont.find(InUserId);
	}

	void ChangeNickName(const string& InUserId, const string& InNickName)
	{
		// �ش� ���̵��� ������ ���� ����� ���� ������� ����.(����)
		userDataCont.find(InUserId)->second = InNickName;
	}
};

class UserLog
{
	friend class UserLogManager;
private:
	_Iter			userIter; 
	bool			isEnter;  

public:
	UserLog(const _Iter& InUserIter, const bool InIsEnter) noexcept :
		userIter(InUserIter),
		isEnter(InIsEnter)
	{};

	UserLog() = delete;
	~UserLog() = default;
};

class UserLogManager
{
	vector<UserLog> userLogCont;
	const string CONST_ENTER_STRING;
	const string CONST_LEAVE_STRING;

public:
	UserLogManager(const int InSize) noexcept : 
		CONST_ENTER_STRING("���� ���Խ��ϴ�."), 
		CONST_LEAVE_STRING("���� �������ϴ�.")
	{
		userLogCont.reserve(InSize);
	}

	~UserLogManager() = default;

public:
	void AddLog(const _Iter& InIter, const bool InIsEnter)
	{
		userLogCont.emplace_back(InIter, InIsEnter);
	}

	// ��Ʈ���� ���� �����ϴ�.
	string GetLogForAnswerWithIndex(const int InIndex)
	{
		if (userLogCont[InIndex].isEnter == true)
			return userLogCont[InIndex].userIter->second + CONST_ENTER_STRING;
		else /* == if (userLogCont[InIndex].isEnter == false) */
			return userLogCont[InIndex].userIter->second + CONST_LEAVE_STRING;
	}

public:
	inline int GetContSize() const noexcept { return userLogCont.size(); }
};

namespace GLOBAL_FUNCTION {
	enum class START_INDEX : int
	{
		ENTER = 6,
		LEAVE = 6,
		CHANGE = 7
	};
	
	string ReturnIDString(const string& InString, const int InStartIndex)
	{
		int indexBuffer{ 0 };

		while (InString[InStartIndex + ++indexBuffer] != ' ')
		{}
		
		return InString.substr(InStartIndex, indexBuffer);
	}

	void HandleRecordString(const vector<string>& InRecords, UserDataManager* const userDataManager, UserLogManager* const userLogManager)
	{
		for (const auto& record : InRecords)
		{
			if (record[0] == 'E') // Enter
			{
				string idStringBuffer = ReturnIDString(record, static_cast<int>(START_INDEX::ENTER));
				
				userLogManager->AddLog(userDataManager->EnterUser( idStringBuffer, 
					string(record, idStringBuffer.size() + static_cast<int>(START_INDEX::ENTER) + 1)),
					true );
			}
			else if (record[0] == 'L') // Leave
			{
				userLogManager->AddLog(userDataManager->LeaveUser(string(record, static_cast<int>(START_INDEX::LEAVE))), false);
			}
			else /* else if (InString[0] == 'C') */ // change nickName!
			{
				string idStringBuffer = ReturnIDString(record, static_cast<int>(START_INDEX::CHANGE));
				
				userDataManager->ChangeNickName(idStringBuffer, string(record, idStringBuffer.size() + static_cast<int>(START_INDEX::CHANGE) + 1));
			}
		}
	}

	vector<string> MakeAnswerFromLog(UserLogManager* const userLogManager)
	{
		vector<string> answer;

		const int contSize = userLogManager->GetContSize();
		answer.reserve(contSize);

		for (int i = 0; i < contSize; ++i)
		{
			answer.emplace_back(userLogManager->GetLogForAnswerWithIndex(i));
		}

		return answer;
	}
}

vector<string> solution(vector<string> records)
{
	UserDataManager userDataManager;
	UserLogManager userLogManager(records.size());
	
	GLOBAL_FUNCTION::HandleRecordString(records, &userDataManager, &userLogManager);
	
	return GLOBAL_FUNCTION::MakeAnswerFromLog(&userLogManager);
}

