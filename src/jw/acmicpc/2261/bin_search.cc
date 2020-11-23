#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class Point {
public:
	Point() = default;
	Point(int p1, int p2) { x = p1; y = p2; }
	~Point() = default;
	void print() { cout << x << " " << y << endl; }
	int x, y;
};

unsigned int N;
vector<Point> v;

struct PointCompare {
	bool operator() (const Point &lhs, const Point &rhs) const {
		if (lhs.x < rhs.x) return true;
		else	return false;
	}
};

struct PointCompareY {
	bool operator() (const Point &lhs, const Point &rhs) const {
		if (lhs.y < rhs.y) return true;
		else	return false;
	}
};

unsigned int getDistSqr(Point a, Point b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

template <typename T>
T MIN(T a, T b) {
	if (a < b) return a;
	return b;
}

unsigned int find_nearest_diff(unsigned int s, unsigned int e, unsigned int cur,
      int direction) {
  unsigned int prv = v[cur].x;
  while(1) {
    if (cur > e || cur < s) return cur - direction;
    if (v[cur].x != prv) return cur - direction; 
    cur += direction;
  }
  assert(0);
  return cur;
}
unsigned int getLeftBoundary(unsigned int f_s, unsigned int f_e,
														unsigned int start, unsigned int end,
 														unsigned int min_dist) {
	if (start == end) {
		if ((v[f_e].x - v[start].x) * (v[f_e].x - v[start].x) >= min_dist)
			return find_nearest_diff(f_s, f_e, start + 1, -1);
		else
			return find_nearest_diff(f_s, f_e, start, -1);
	}
	unsigned int mid = (start + end) / 2;
	if (min_dist == (v[f_e].x - v[mid].x) * (v[f_e].x - v[mid].x))
		return find_nearest_diff(f_s, f_e, mid + 1, -1);
	else if (min_dist > (v[f_e].x - v[mid].x) * (v[f_e].x - v[mid].x))
		return getLeftBoundary(f_s, f_e, start, mid, min_dist);
	else
		return getLeftBoundary(f_s, f_e, mid + 1, end, min_dist);
}

unsigned int getRightBoundary(unsigned int f_s, unsigned int f_e,
														unsigned int start, unsigned int end,
 														unsigned int min_dist) {
	if (start == end) {
		if ((v[f_s].x - v[start].x) * (v[f_s].x - v[start].x) >= min_dist)
		  return find_nearest_diff(f_s, f_e, start - 1, 1);
		else
		  return find_nearest_diff(f_s, f_e, start, 1);
	}
	unsigned int mid = (start + end) / 2;
	if (min_dist == (v[f_s].x - v[mid].x) * (v[f_s].x - v[mid].x))
		return find_nearest_diff(f_s, f_e, mid - 1, 1);
	else if (min_dist < (v[f_s].x - v[mid].x) * (v[f_s].x - v[mid].x))
		return getLeftBoundary(f_s, f_e, start, mid, min_dist);
	else
		return getLeftBoundary(f_s, f_e, mid + 1, end, min_dist);
}
	
unsigned int dnc(unsigned int start, unsigned int end) {
	if (end - start == 0) return 0;
	else if (end - start == 1) return getDistSqr(v[start], v[end]);
	else if (end - start == 2) {
		unsigned int ret = getDistSqr(v[start], v[start + 1]);
		if (ret > getDistSqr(v[start + 1], v[start + 2])) 
			ret = getDistSqr(v[start + 1], v[start + 2]);
		if (ret > getDistSqr(v[start], v[start + 2])) 
			ret = getDistSqr(v[start], v[start + 2]);
		return ret;
	}
	

	unsigned int mid = (start + end) / 2;
	unsigned int l_min = dnc(start, mid);
	unsigned int r_min = dnc(mid + 1, end);
	unsigned int min_dst = MIN(l_min, r_min);

	unsigned int left_boundary = getLeftBoundary(start, mid, start, mid, min_dst);
	unsigned int right_boundary = getRightBoundary(mid, end, mid, end, min_dst);

	vector<Point> cand{};
	for (int i = left_boundary ; i <= right_boundary ; i++)
		cand.push_back(v[i]);
	
	sort(cand.begin(), cand.end(), PointCompareY());

	for (auto it = cand.begin() ; (it+1) != cand.end() ; it++) {
		int cnt = 7;
		for (auto itt = (it+1) ; itt != cand.end() ; itt++) {
			if (getDistSqr(*it, *itt) < min_dst) min_dst = getDistSqr(*it, *itt);
			if ((--cnt) == 0) break;
		}
	}

	return min_dst;
}

int main() {
	cin >> N;

	for (int i = 0 ; i < N ; i++) {
		int x, y;
		cin >> x;
		cin >> y;
		v.push_back(Point(x, y));
	}	

	sort(v.begin(), v.end(), PointCompare());

	cout << dnc(0, N - 1) << endl;

	return 0;
}
