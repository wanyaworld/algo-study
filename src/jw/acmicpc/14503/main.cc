#include <stdio.h>

enum tile {WALL, DIRTY, CLEANED};

int N, M, ret{};
tile map[51][51];


bool go(int *y, int *x, int dir, int backward) { 
	int new_y = *y, new_x = *x;
	switch (dir) {
		case 0:
		new_y += backward;
		break;
	
		case 1:
		new_x -= backward;
		break;
	
		case 2:
		new_y -= backward;
		break;
	
		case 3:
		new_x += backward;
		break;

		default:
		printf("bug\n");
		break;
	}
	if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) return false;
	*y = new_y;
	*x = new_x;
	return true;
}
bool go_back(int *y, int *x, int dir) { 
  return go(y, x, dir, 1);
}

bool go_forward(int *y, int *x, int dir) { 
  return go(y, x, dir, -1);
}

void turn_left(int *y, int *x, int *dir) {
	(*dir)--;
	if (*dir < 0) *dir = 3;
}

bool get_left(int y, int x, int dir, int *new_y, int *new_x){
	*new_y = y;
	*new_x = x;
	int new_dir = dir;
	turn_left(new_y, new_x, &new_dir);
	bool rett = go_forward(new_y, new_x, new_dir);
	if (!rett) return false;
	return true;
}

bool can_sweep(int y, int x) {
	int dir = 0;
	for (int i = 0 ; i < 4 ; i++) {
		int new_y, new_x;
		bool rett = get_left(y, x, dir, &new_y, &new_x);
		if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;
		if (map[new_y][new_x] == DIRTY) return true;
		turn_left(&y, &x, &dir);
	}
	return false;
}

void dfs(int y, int x, int dir) {
	if (x < 0 || x >= M || y < 0 || y >=N || map[y][x] == WALL || map[y][x] == CLEANED) return;
	map[y][x] = CLEANED;
	ret++;
	printf("%d %d\n", y, x);
/*
	if (!can_sweep(y, x)) {
		if (!go_back(&y, &x, dir, 1)) return;
		dfs(y, x, dir);
		return;
	}
*/
	
	for (int i = 0 ; i < 4 ; i++) {
		if (!can_sweep(y, x)) {  goto back; }
		int new_y, new_x;
		if (get_left(y, x, dir, &new_y, &new_x)) {
			turn_left(&y, &x, &dir);
			if (map[new_y][new_x] == CLEANED) continue;
			go_forward(&y, &x, dir);
			dfs(y, x, dir);
			go_back(&y, &x, dir);
		}
	}
	return;

back:
		if (!go_back(&y, &x, dir)) return;
		dfs(y, x, dir);
}
int main() {
	int y, x, dir;
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &y, &x, &dir);
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			int tmp;
			scanf("%d\n", &tmp);
			if (tmp) map[i][j] = WALL;
			else map[i][j] = DIRTY;
		}
	}
	dfs(y, x, dir);
	printf("%d\n", ret);
	return 0;
}
