class Solution {
public:
    int dict[21][21];
    
    vector<vector<int>> generateMatrix(int n) {
        unsigned int rem = n * n;
        vector<int> dx{1, 0, -1, 0};
        vector<int> dy{0, -1, 0, 1};
        int y{}, x{};
        vector<vector<int>> ret(n);
        for (int i = 0 ; i < n ; i++){
            ret[i].resize(n);
        }
        
        int walk{};
        for (int i = 0 ; rem ; i++ ) {
            while (rem) {
                /* not visited */
                if (!dict[y][x]) {
                    rem--;
                    dict[y][x] = 1;
                    ret[y][x] = (walk++) + 1;
                }
                
                int new_y = y + dy[i % 4];
                int new_x = x + dx[i % 4];

                if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= n || dict[new_y][new_x]) break;
                
                y = new_y;
                x = new_x;
            }
        }
        return ret;
    }
};
