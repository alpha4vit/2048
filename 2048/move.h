#pragma once
#include"includes.h"

bool MoveRight(vector<vector<vector<int>>>& nums, int & CURRENT_RESULT);

bool MoveLeft(vector<vector<vector<int>>>& nums, int & CURRENT_RESULT);

bool MoveDown(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT);

bool MoveUp(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT);

bool checkGameOver(vector<vector<vector<int>>> nums);

bool checkIsWinner(vector<vector<vector<int>>>& nums, int state);