#include "move.h"
#include"includes.h"
#include"Nums.h"

bool MoveRight(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    int moves = 0;
	for (int row = 0; row < nums.size(); ++row){
		int i = nums[row].size() - 1;
		while (i >= 0) {
			if (nums[row][i][0] != 0) {
				int j = i + 1;

				while (j < nums[row].size() && nums[row][j][0] == 0)
					++j;
                if (j != i + 1) {
                    moves++;
                }
                if (j < nums[row].size() && nums[row][j][0] == nums[row][i][0]) {
                    // Если найдено одинаковое значение, складываем их
                    nums[row][j][0] += nums[row][i][0];
                    CURRENT_RESULT += nums[row][i][0]*2;
                    nums[row][i][0] = 0;
                    moves++;
                }
                else {
                    // В противном случае перемещаем элемент вправо
                    j--;
                    nums[row][j][0] = nums[row][i][0];

                    if (j != i) {
                        nums[row][i][0] = 0;
                    }
                    
                }
            }
            i--;
		}
	}
    return moves > 0;
}

bool MoveLeft(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    int moves = 0;
    for (int row = 0; row < nums.size(); ++row) {

        int index = 0;

        while (index < nums[row].size()) {
            if (nums[row][index][0] != 0) {
                int j = index-1;
                while (j >= 0 && nums[row][j][0] == 0) {
                    --j;
                }
                if (j != index - 1) {
                    moves++;
                }
                if (j >= 0 && nums[row][index][0] == nums[row][j][0]) {
                    nums[row][j][0] *= 2;
                    CURRENT_RESULT += nums[row][index][0]*2;
                    nums[row][index][0] = 0;
                    moves++;
                }
                else {
                    ++j;
                    nums[row][j][0] = nums[row][index][0];
                    if (index != j)
                        nums[row][index][0] = 0;
                    //moves++;
                }

            }
            ++index;
        }
    }
    return moves>0;
}

bool MoveDown(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    int moves = 0;
    for (int col = 0; col < nums.size(); ++col) {
        int i = nums[col].size() - 1;
        while (i >= 0) {
            if (nums[i][col][0] != 0) {
                int j = i + 1;

                while (j < nums[col].size() && nums[j][col][0] == 0)
                    ++j;
                if (j != i + 1) {
                    moves++;
                }
                if (j < nums[col].size() && nums[j][col][0] == nums[i][col][0]) {
                    // Если найдено одинаковое значение, складываем их
                    nums[j][col][0] += nums[i][col][0];
                    CURRENT_RESULT += nums[i][col][0]*2;
                    nums[i][col][0] = 0;
                    moves++;
                }
                else {
                    // В противном случае перемещаем элемент вправо
                    j--;
                    nums[j][col][0] = nums[i][col][0];

                    if (j != i) {
                        nums[i][col][0] = 0;
                    }
                    //moves++;
                }
            }
            i--;
        }
    }
    return moves>0;
}

bool MoveUp(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    int moves = 0;
    for (int col = 0; col < nums.size(); ++col) {

        int index = 0;

        while (index < nums[col].size()) {
            if (nums[index][col][0] != 0) {
                int j = index - 1;
                while (j >= 0 && nums[j][col][0] == 0) {
                    --j;
                }
                if (j != index - 1) {
                    moves++;
                }
                if (j >= 0 && nums[index][col][0] == nums[j][col][0]) {
                    nums[j][col][0] *= 2;
                    CURRENT_RESULT += nums[index][col][0]*2;
                    nums[index][col][0] = 0;
                    moves++;
                }
                else {
                    ++j;
                    nums[j][col][0] = nums[index][col][0];
                    if (index != j)
                        nums[index][col][0] = 0;
                    //moves++;
                }

            }
            ++index;
        }
    }
    return moves>0;
}

bool checkGameOver(vector<vector<vector<int>>> nums)
{
    int a = 0;
    bool isEmpty = false;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums[i].size(); ++j) {
            if (nums[i][j][0] == 0) {
                return false;
            }
        }
    }
    return !(MoveDown(nums, a) || MoveUp(nums, a) || MoveLeft(nums, a) || MoveRight(nums, a));
}

bool checkIsWinner(vector<vector<vector<int>>>& nums, int state)
{
    if (state == 3 || state == 4 || state == 6) {
        state = 0;
        cout << state << endl;
    }
        
    else if (state == 5)
        state = 1;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums[i].size(); ++j) {
            if (state == 1 && nums[i][j][0] >= 4096 || state == 0 && nums[i][j][0] >= 2048) {
                return true;
            }
        }
    }
    return false;
}


