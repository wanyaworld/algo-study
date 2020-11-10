#include <memory>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

class Solver {
	public:
		Solver() : cheez(0), epoch(0) {}
		int N, M;
		int data[100][100];
		int sur[100][100];
		int cheez;
		int epoch;
		int solve();
		bool dfs(int y, int x, vector<tuple<int ,int>> &v, map<tuple<int, int>, bool> &visited);
		void update_sur();
		bool can_melt(int y, int x);
		void melt();
};

bool Solver::dfs(int y, int x, vector<tuple<int ,int>> &v, map<tuple<int, int>, bool> &visited){
	if (y < 0 || x < 0 || y >= N || x >= M) return false;
	if (data[y][x]) return true;
	if (y <= 0 || x <= 0 || y >= N - 1 || x >= M - 1) return false;
	if (visited.find(tuple<int, int>(y, x)) != visited.end()) return true;
	visited[tuple<int, int>(y, x)] = true;
	v.push_back(tuple<int, int>(y, x));
	
	int y_disp[] = {-1, 0, 1};
	int x_disp[] = {-1, 0, 1};

	for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
		for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
			if (*dy + *dx != 1 && *dy + *dx != -1) continue;
			if (dfs(y + *dy , x + *dx, v, visited) == false) return false;
		}
	}
	return true;
}
void Solver::update_sur() {
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			if (data[i][j]) sur[i][j] = 1;
			else sur[i][j] = 0;
		}
	}

	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			vector<tuple<int, int>> v;
			map<tuple<int, int>, bool> visited;
			if (dfs(i, j, v, visited)) {
				for (auto it = v.begin() ; it != v.end() ; it++)
					sur[get<0>(*it)][get<1>(*it)] = 1;
			}
		}
	}
}

bool Solver::can_melt(int y, int x) { 
	int y_disp[] = {-1, 0, 1};
	int x_disp[] = {-1, 0, 1};
	int cnt = 0;

	for (int *dy = &y_disp[0] ; dy < &y_disp[2] + 1 ; dy++) {
		for (int *dx = &x_disp[0] ; dx < &x_disp[2] + 1 ; dx++) {
			if ( *dy + *dx != 1  && *dy + *dx != -1) continue;
			int new_y = y + *dy;
			int new_x = x + *dx;
			if (new_y < 0 || new_x < 0 || new_y >= N || new_x >= M) continue;
			if (!data[new_y][new_x] && !sur[new_y][new_x]) cnt++;
		}
	}
	if (cnt >= 2) return true;
	return false;
}

void Solver::melt() {
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			if (!data[i][j]) continue; // no cheese
			if (can_melt(i, j)) {
				data[i][j] = 0;
				cheez--;
			}
		}
	}
}


int Solver::solve() {
	while (1) {
		if (cheez == 0) return epoch;
		update_sur();
		melt();
		epoch++;
		#if 0
		for (int i = 0 ; i < N ; i++) {
			for (int j = 0 ; j < M ; j++) {
				printf("%d", data[i][j]);
			}
		printf("\n");
		}
		printf("\n");
		#endif
	}
}

Solver sv;

int main() {
	scanf("%d %d", &sv.N, &sv.M);
	for (int i = 0 ; i < sv.N ; i++) {
		for (int j = 0 ; j < sv.M ; j++) {
			scanf("%d", &sv.data[i][j]);
			if (sv.data[i][j]) { 
				sv.cheez++;	
			}
		}
	}
	cout << sv.solve() << endl;
	return 0;
}
