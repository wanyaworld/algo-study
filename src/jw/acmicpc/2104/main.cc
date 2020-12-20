#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define if_debug 0

typedef unsigned long long int li;

int arr[100001];
int n;

li eval(int s, int e) {
	li sum = 0;
	int min = -1;
	for (int i = s ; i <= e ; i++) {
		if (min == -1 || arr[i] < min) min = arr[i];
		sum += arr[i];
	}
	return sum * min;
}

li bf(int s, int e) {
	li max = -1;
	for (int i = s ; i < e ; i++) {
		for (int j = s ; j < e ; j++) {
			li ret = eval(i, j);
			if (ret > max) max = ret;
		}
	}
	return max;
}

li solve(int s, int e) {
	if (s == e)  return eval(s, e);
	int mid = (s + e) / 2;
	li l_max = solve(s, mid);
	li r_max = solve(mid + 1, e);
	li max;
	if (l_max > r_max) max = l_max;
	else max = r_max;
	int l_i = mid, r_i = mid;

	li sum = arr[mid], min = arr[mid];
	while(1) {
		if (l_i < s && r_i > e) {
			printf("exception!!\n");
		}
		if (l_i <= s && r_i >= e) break;
		if (l_i <= s || (arr[l_i - 1] <= arr[r_i + 1] && r_i < e)) {
			sum += arr[r_i + 1];
			if (arr[r_i + 1] < min) min = arr[r_i + 1];
			r_i++;
		}
		else if (r_i >= e || (arr[l_i - 1] >= arr[r_i + 1] && l_i > s)) {
			sum += arr[l_i - 1];
			if (arr[l_i - 1] < min) min = arr[l_i - 1];
			l_i--;
		}
		else{
			printf("exception!!\n");
		}
		li tmp = sum * min;
		if (tmp > max) max = tmp;
	}
	return max;
}

int main() {
	scanf("%d\n", &n);
	for (int i = 0 ; i < n ; i++)
		scanf("%d", &(arr[i]));
#if if_debug
	srand(time(NULL));
	n = 1000;
	for (int i = 0 ; i < n ; i++) {
		//arr[i] = rand() % 1000001;
		arr[i] = rand() % 10;
	}
#endif
	printf("%llu\n", solve(0, n - 1));
	//printf("%llu\n", bf(0, n - 1));
	return 0;
}
