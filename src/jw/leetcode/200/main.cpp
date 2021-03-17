class Solution {
public:
    int dfs(vector<vector<char>>& grid, int y, int x) {
        if (y > m - 1 || y < 0 || x > n - 1 || x < 0) return 0;
        if (grid[y][x] == '0') return 0;
        
        grid[y][x] = '0';
        
        dfs(grid, y - 1, x);
        dfs(grid, y + 1, x);
        dfs(grid, y, x - 1);
        dfs(grid, y, x + 1);
        
        return 1;
    }
    int m, n, ret{};
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        for (int i = 0 ; i < m ; i++) {
            for (int j = 0 ; j < n ; j++) {
                ret += dfs(grid, i, j);
            }
        }
        return ret;
    }
};
