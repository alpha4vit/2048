#include "move.h"
#include"includes.h"
#include"Nums.h"

void MoveRight(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
	for (int row = 0; row < nums.size(); ++row){
		int i = nums[row].size() - 1;
		while (i >= 0) {
			if (nums[row][i][0] != 0) {
				int j = i + 1;

				while (j < nums[row].size() && nums[row][j][0] == 0)
					++j;

                if (j < nums[row].size() && nums[row][j][0] == nums[row][i][0]) {
                    // Если найдено одинаковое значение, складываем их
                    nums[row][j][0] += nums[row][i][0];
                    CURRENT_RESULT += nums[row][i][0]*2;
                    nums[row][i][0] = 0;
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
}

void MoveLeft(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    for (int row = 0; row < nums.size(); ++row) {

        int index = 0;

        while (index < nums[row].size()) {
            if (nums[row][index][0] != 0) {
                int j = index-1;
                while (j >= 0 && nums[row][j][0] == 0) {
                    --j;
                }

                if (j >= 0 && nums[row][index][0] == nums[row][j][0]) {
                    nums[row][j][0] *= 2;
                    CURRENT_RESULT += nums[row][index][0]*2;
                    nums[row][index][0] = 0;
                }
                else {
                    ++j;
                    nums[row][j][0] = nums[row][index][0];
                    if (index != j)
                        nums[row][index][0] = 0;
                }

            }
            ++index;
        }
    }
}

void MoveDown(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    for (int col = 0; col < nums.size(); ++col) {
        int i = nums[col].size() - 1;
        while (i >= 0) {
            if (nums[i][col][0] != 0) {
                int j = i + 1;

                while (j < nums[col].size() && nums[j][col][0] == 0)
                    ++j;

                if (j < nums[col].size() && nums[j][col][0] == nums[i][col][0]) {
                    // Если найдено одинаковое значение, складываем их
                    nums[j][col][0] += nums[i][col][0];
                    CURRENT_RESULT += nums[i][col][0]*2;
                    nums[i][col][0] = 0;
                }
                else {
                    // В противном случае перемещаем элемент вправо
                    j--;
                    nums[j][col][0] = nums[i][col][0];

                    if (j != i) {
                        nums[i][col][0] = 0;
                    }
                }
            }
            i--;
        }
    }
}

void MoveUp(vector<vector<vector<int>>>& nums, int& CURRENT_RESULT)
{
    for (int col = 0; col < nums.size(); ++col) {

        int index = 0;

        while (index < nums[col].size()) {
            if (nums[index][col][0] != 0) {
                int j = index - 1;
                while (j >= 0 && nums[j][col][0] == 0) {
                    --j;
                }

                if (j >= 0 && nums[index][col][0] == nums[j][col][0]) {
                    nums[j][col][0] *= 2;
                    CURRENT_RESULT += nums[index][col][0]*2;
                    nums[index][col][0] = 0;
                }
                else {
                    ++j;
                    nums[j][col][0] = nums[index][col][0];
                    if (index != j)
                        nums[index][col][0] = 0;
                }

            }
            ++index;
        }
    }
}


