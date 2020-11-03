#include <vector>
#include <iostream>
#include <algorithm>

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

unsigned int getLeftBoundary(unsigned int start, unsigned int end,
 														unsigned int min_dist) {
	for (int i = start ; i < end ; i++)
		if ((v[end].x - v[i].x) * (v[end].x - v[i].x) <= min_dist) return i;
	return end;
}

unsigned int getRightBoundary(unsigned int start, unsigned int end,
 														unsigned int min_dist) {
	for (int i = end ; i > start ; i--)
		if ((v[i].x - v[start].x) * (v[i].x - v[start].x) <= min_dist) return i;
	return start;
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

	unsigned int left_boundary = getLeftBoundary(start, mid, min_dst);
	unsigned int right_boundary = getRightBoundary(mid, end, min_dst);

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
