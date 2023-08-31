class Solution
{
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int swapNum;

        for (int i = 0; i < matrix.size() / 2; i++)      //swap UpsideDown
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                swapNum = matrix[i][j];
                matrix[i][j] = matrix[matrix.size() - 1 - i][j];
                matrix[matrix.size() - 1 - i][j] = swapNum;
            }
        }

        for (int i = 1; i < matrix.size(); i++)         //swap y = -x
        {
            for (int j = 0; j < i; j++)
            {
                swapNum = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = swapNum;
            }
        }

    }
};