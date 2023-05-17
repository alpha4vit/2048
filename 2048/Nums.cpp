#pragma once
#include"Nums.h"
#include"includes.h"

vector<vector<vector<int>>> genNums(int level)
{

	// вектор представляет собой двухмерный массив, самый меньший веткор представляет собой одну клетку на поле, хранит в себе свое значение, значение по иксу, значение по игрику
	vector<vector<vector<int>>> nums; 
	int dist = 0;
	switch (level) {
	case 3: {dist = 198; break; }
	case 4: {dist = 148; break; }
	case 5: {dist = 118; break; }
	default: break;
	}
	int x = 40; int y = 40;
	for (int i = 0; i < level; ++i) {
		vector<vector<int>> temp;
		for (int j = 0; j < level; ++j) {
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

