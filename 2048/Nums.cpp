

#pragma once
#include"Nums.h"
#include"includes.h"

vector<vector<vector<int>>> genNums(int level)
{

	// ������ ������������ ����� ���������� ������, ����� ������� ������ ������������ ����� ���� ������ �� ����, ������ � ���� ���� ��������, �������� �� ����, �������� �� ������
	vector<vector<vector<int>>> nums;
	level = level == 3 ? 1 : level;
	int dist = 0;
	switch (level) {
	case 0: {dist = 198; break; }
	case 1: {dist = 148; break; }
	case 2: {dist = 118; break; }
	default: break;
	}
	int x = 40; int y = 40;
	for (int i = 0; i < level + 3; ++i) {
		vector<vector<int>> temp;
		for (int j = 0; j < level + 3; ++j) {
			vector<int> t;
			t.push_back(0);
			t.push_back(x);
			t.push_back(y);
			x += dist;
			temp.push_back(t);
		}
		x = 40;
		y += dist;

		nums.push_back(temp);
		if (i == level - 1) {
			temp.clear();
		}
	}

	for (int i = 0; i < nums.size(); ++i) {
		for (int j = 0; j < nums[i].size(); ++j) {
			cout << nums[i][j][0] << " ";
		}
		cout << endl;
	}
	return nums;
}

void genFnum(vector<vector<vector<int>>>& nums)
{
	srand(time(NULL));
	for (int i = 0; i < 2; ++i) {
		const int vals[2]{ 2, 4 };
		int x = rand() % (size(nums) - 1);
		int y = rand() % (size(nums[0]) - 1);
		if (nums[x][y][0] == 0) {
			nums[x][y][0] = vals[rand() % 2];
		}
		else {
			--i;
			continue;
		}
	}
}

void newRandNum(vector<vector<vector<int>>>& nums)
{

	srand(time(NULL));
	int x = rand() % (size(nums) - 1);
	int y = rand() & (size(nums) - 1);
	int attempts = 0;
	bool fl = false;
	while (attempts < 100) {
		x = rand() % (size(nums) - 1);
		y = rand() & (size(nums) - 1);
		if (nums[x][y][0] == 0) {
			fl = true;
			break;
		}
		++attempts;
	}
	if (fl)
		nums[x][y][0] = 2;
}

