#include <cstdlib>
#include <vector>
#include <iostream>


int count_paths(const std::vector<std::vector<char>> &mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    std::vector<std::vector<int>> paths_to(mat.size(), std::vector<int>(mat[0].size(), 0));
    for (int i = 0; i < rows; ++i)
    {
        if (mat[0][i] == '*')
            break;
        paths_to[0][i] = 1;
    }
    for (int i = 0; i < cols; ++i)
    {
        if (mat[i][0] == '*')
            break;
        paths_to[i][0] = 1;
    }

    for (int row = 1; row < rows; ++row)
    {
        for (int col = 1; col < cols; ++col)
        {
            if (mat[row][col] == '*')
                continue;

            paths_to[row][col] = paths_to[row - 1][col] + paths_to[row][col - 1];
        }
    }

    return paths_to[rows - 1][cols - 1];
}


int count_paths_rec(int row, int col, const std::vector<std::vector<char>> &mat, std::vector<std::vector<int>> &path_counts)
{
    if (row >= mat.size() || col >= mat[0].size() || mat[row][col] == '*')
        return 0;

    if (path_counts[row][col] == -1)
        path_counts[row][col] = count_paths_rec(row + 1, col, mat, path_counts) + count_paths_rec(row, col + 1, mat, path_counts);
    return path_counts[row][col];
}

int count_paths_rec(const std::vector<std::vector<char>> &mat)
{
    std::vector<std::vector<int>> paths_to(mat.size(), std::vector<int>(mat[0].size(), -1));
    paths_to[mat.size() - 1][mat[0].size() - 1] = 1;
    return count_paths_rec(0, 0, mat, paths_to);
}




int main()
{
    int rows = 10;
    int cols = 12;

    std::vector<std::vector<char>> mat{};
    for (int i = 0; i < rows; ++i)
    {
        mat.push_back(std::vector<char>());
        for (int j = 0; j < cols; ++j)
        {
            bool is_wall = std::rand() % 100 < 15;
            mat[i].push_back(is_wall ? '*' : ' ');
        }
    }

    for (auto& row : mat)
    {
        for (auto c : row)
            std::cout << c;
        std::cout << "|" << std::endl;
    }
    std::cout << count_paths(mat) << std::endl;
    std::cout << count_paths_rec(mat) << std::endl;
}