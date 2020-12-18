// copied from https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <vector>
#include "trim.h"

using std::string;
using std::ifstream;
using std::cout;
using std::getline;
using std::endl;
using std::vector;


vector<string> items;

// Utility function to do modular exponentiation.
// It returns (x^y) % p
mpz_class power(mpz_class x, mpz_class y, const mpz_class & p)
{
	mpz_class res(1);      // Initialize result
	x = x % p;  // Update x if it is more than or
	// equal to p
	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y % 2 ==  1)
			res = (res*x) % p;

		// y must be even now
		y = y>>1; // y = y/2
		x = (x*x) % p;
	}
	return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns false if n is
// probably prime.
// d is an odd number such that  d*2<sup>r</sup> = n-1
// for some r >= 1
bool millerTest(mpz_class d, const mpz_class & n, const mpz_class & rand_num)
{
	// Pick a random number in [2..n-2]
	// Corner cases make sure that n > 4

	// Compute a^d % n
	mpz_class x = power(rand_num, d, n);

	if (x == 1  || x == n-1)
		return true;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i)   d does not reach n-1
	// (ii)  (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n-1)
	{
		x = (x * x) % n;
		d *= 2;
		if (x == 1)      return false;
		if (x == n-1)    return true;
	}

	// Return composite
	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(mpz_class & n, int k, gmp_randclass & randclass)
{
	// Corner cases
	if (n <= 1 || n == 4)  return false;
	if (n <= 3) return true;

	bool is_prime = true;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	mpz_class d = n - 1;
	while (d % 2 == 0)
		d /= 2;


	// Iterate given number of 'k' times
#pragma omp parallel for default(none), shared(n, d, k, randclass, is_prime)
	for (int i = 0; i < k; i++) {
		if (!is_prime) {
			continue;
		}
		if (!millerTest(d, n, 2 + randclass.get_z_range(n - 4))) {
			is_prime = false;
		}
	}

	return is_prime;
}

// Driver program
int main()
{
	int k = 10;  // Number of iterations
	int n;

	gmp_randclass r(gmp_randinit_default);
#ifdef READ_FROM_FILE
	ifstream cin("../data.in");
#else
	using std::cin;
#endif
	string str;
	cin >> n;
	while (cin.get()!='\n' && !cin.eof())
		continue;
	for (int i = 0; i < n; i++) {
		getline(cin, str);
		items.emplace_back(trim(str));
	}

#ifndef TEST_SQRT
#pragma omp parallel for default(none), shared(n, items, k, r)
	for (int i = 0; i < n; i++) {
		mpz_class a(0);
		string & item = items[i];
		//printf("num: %lu\n", item.length());
		a.set_str(item.c_str(), 10);
		// RESULT: num length result \n
#ifndef READ_FROM_FILE
		printf("%s %lu %s\n", item.c_str(), item.length(), isPrime(a, k, r) ? "prime" : "composite");
#else
		printf("%lu %s\n", item.length(), isPrime(a, k, r) ? "prime" : "composite");
#endif
		//cout << a << item.length()
	}
#else
	for (int i = 0; i < n; i++) {
		mpz_class a(0);
		string & item = items[i];
		printf("num: %lu\n", item.length());
		a.set_str(item.c_str(), 10);
		cout << sqrt(a);
	}
#endif
#ifdef READ_FROM_FILE
	cin.close();
#endif
}