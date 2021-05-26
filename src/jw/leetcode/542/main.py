class Solution:
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        m = len(mat)
        n = len(mat[0])
        visited = set()
        q = collections.deque()
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 0:
                    q.append((i, j))
                    visited.add((i, j))
        depth = 0        
        directions = [[1,0], [-1,0], [0,1], [0,-1]]
        
        def isValid(grid, row, col):
            if (row < 0 or row >= len(grid) or col < 0 or col >= len(grid[0])):
                return False
            return True
        
        while len(q) > 0:
            cur_size = len(q)
            for nbr in range(cur_size):
                depth += 1
                i, j = q.popleft()
                
                for d in directions:
                    ii = i + d[0]
                    jj = j + d[1]
                
                    if isValid(mat, ii, jj) and (ii, jj) not in visited:
                        mat[ii][jj] = mat[i][j] + 1
                        q.append((ii, jj))
                        visited.add((ii, jj))
        return mat
            
