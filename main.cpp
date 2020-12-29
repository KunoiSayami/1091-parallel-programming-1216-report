#include <cstdio>
#include <cmath>
#include <omp.h>
#include <cstring>
#include <chrono>

using namespace std::chrono;

constexpr size_t default_sz = 500000 + 10;
//constexpr size_t LNG = default_sz - 1;
constexpr size_t STRING_SIZE = 20;
constexpr int MAX_NUM = 10000;
int printing = 0;

int changed = 0;    // the global variable
int use_changed = 1;  // flag to decide whether go recording whether has exchanged
void comp_exchange2(char **key, int *t, int a, int b, int len) {
	int tmp;
	if (b > len) return;   // b is out of original_n, so key[t[a]] is smaller
	if (strcmp(key[t[a]], key[t[b]]) > 0) {
		// exchange
		tmp = t[a];
		t[a] = t[b];
		t[b] = tmp;
#pragma omp atomic // record the exchange counts
		changed++;
	}
}

void comp_exchange(char **key, int *t, int a, int b) {
	int tmp;
	if (strcmp(key[t[a]], key[t[b]]) > 0) {
		// exchange
		tmp = t[a];
		t[a] = t[b];
		t[b] = tmp;
#pragma omp atomic // record the exchange counts
		changed++;
	}
}

void trsort(int n, char **key, int *t, int para) {
	int i, j;
	changed = 0;
	for (i = 1; i <= n; i++) {
		//printf("\niteration %d", i);
		if (i % 2) {  // i is odd
#pragma omp parallel for default(none) shared(n, key, t), private(j) if(para)
			for (j = 0; j <= n / 2 - 1; j++) {
				comp_exchange(key, t, 2 * j + 1, 2 * j + 2);
			}
		} else {  // i is even
			// add following three lines to cope the problem of n is odd
			int m;
			if (n % 2) m = n / 2;
			else m = n / 2 - 1;
#pragma omp parallel for default(none) shared(m, t, key), private(j) if(para)
			for (j = 1; j <= m; j++) {
				comp_exchange(key, t, 2 * j, 2 * j + 1);
			}
			if (use_changed) {
				if (!changed) break;
				else changed = 0;
			}
		}
	}
}

void shsort(int n, char **key, int *t, int para) {
	int R, i, j, j2, pi, offset, pi2;
	int a, original_n;
	// length consideration
	for (a = 0; ; a++) if (pow(2.0, (double) a) >= n) break;
	original_n = n;
	n = pow(2.0, (double) a);
	R = n;
	while (R >= 2) {
		//#pragma omp parallel for private(i, pi, offset, pi2, j, j2) if(para) num_threads(8)
		for (i = 0; i < n / 2; i++) {
			pi = i % (R / 2);
			offset = (int) (i / (R / 2)) * R;
			pi2 = R - pi - 1;
			j = pi + offset;
			j2 = pi2 + offset;
#ifdef PRINT_PROCESS
			if (printing) printf("\ncomp %d %d ", j, j2);
#endif
			comp_exchange2(key, t, j + 1, j2 + 1, original_n);
		}
#ifdef PRINT_PROCESS
		if (printing) printf("\n----");
#endif
		R /= 2;
	}
	trsort(original_n, key, t, para);
}


void showTimeSpan(const high_resolution_clock::time_point & start_time) {
	duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - start_time);
#ifdef TESTING
	printf("used time: %.4lf seconds\n", time_span.count());
#else
	printf("%.4lf ", time_span.count());
#endif
}

int main(int argc, char const * argv[]) {
	using namespace std::chrono;
	size_t LNG = default_sz - 1;
	if (argc > 1) {
		LNG = strtol(argv[1], nullptr, 10);
		// sscanf(argv[1], "%zd", &LNG);
		if (LNG > default_sz) {
			fprintf(stderr, "LNG > default_sz, Please check.\n");
		}
	}
	char **ar;//, tmp[default_sz];
	int t[default_sz];
	int maxNum = MAX_NUM;
	ar = new char *[default_sz];
	for (auto i = 1ul; i <= LNG + 1; i++)
		ar[i] = new char[STRING_SIZE];
	for (auto i = 1ul; i <= LNG; i++) {
#ifdef TESTING
		printf("\rcurrent i: %d", i);
#endif
		auto tmp_ = rand() % maxNum + 1;
		while (tmp_ < maxNum / 10 - 1)
			tmp_ *= 10;
		sprintf(ar[i], "%d", tmp_);
	}
#ifdef TESTING
	puts("");
#else
	printf("%ld ", LNG);
#endif

	for (auto i = 1ul; i <= LNG; i++)
		t[i] = i;
#ifdef TESTING
	if (printing) {
		printf("Befor sort:");
		for (auto i = 1ul; i <= LNG; i++)
			printf("%s ", ar[t[i]]);
	}
#endif
	high_resolution_clock::time_point start_time = high_resolution_clock::now();

	shsort(LNG, ar, t, 0);
	showTimeSpan(start_time);
#ifdef TESTING
	printf("First sort, shell sort sequential:");
	if (printing) {
		for (auto i = 1ul; i <= LNG; i++)
			printf("%s ", ar[t[i]]);
	}
	puts("");
#endif

	// second sort
	for (auto i = 1ul; i <= LNG; i++)
		t[i] = i;
	start_time = high_resolution_clock::now();
	shsort(LNG, ar, t, 1);
	showTimeSpan(start_time);
#ifdef TESTING
	printf("Second sort, shell sort parallel:");
	if (printing) {
		for (auto i = 1ul; i <= LNG; i++)
			printf("%s ", ar[t[i]]);
	}
	puts("");
#endif

	// third sort
	for (auto i = 1ul; i <= LNG; i++) t[i] = i;
	start_time = high_resolution_clock::now();
	trsort(LNG, ar, t, 0);
	showTimeSpan(start_time);
#ifdef TESTING
	printf("Third sort, transposition sort sequential:");
	if (printing) {
		for (auto i = 1ul; i <= LNG; i++)
			printf("%s ", ar[t[i]]);
	}
	puts("");
#endif

	// fourth sort
	for (auto i = 1ul; i <= LNG; i++) t[i] = i;
	start_time = high_resolution_clock::now();
	trsort(LNG, ar, t, 1);
	showTimeSpan(start_time);
#ifdef TESTING
	printf("Fourth sort, transposition sort parallel:");
	if (printing)
		for (auto i = 1ul; i <= LNG; i++)
			printf("%s ", ar[t[i]]);
	//getchar();
#endif
	puts("");
	for (auto i = 1ul; i <= LNG + 1; i++)
		delete [] ar[i];
	delete [] ar;
}
