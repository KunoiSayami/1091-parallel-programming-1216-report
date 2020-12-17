/*
 ** Copyright (C) 2020 KunoiSayami
 **
 ** This file is part of 1091-parallel-programming-1216-report and is released under
 ** the AGPL v3 License: https://www.gnu.org/licenses/agpl-3.0.txt
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Affero General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 ** GNU Affero General Public License for more details.
 **
 ** You should have received a copy of the GNU Affero General Public License
 ** along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include <string>
#include <cstdio>
#include <iostream>
#include <gmpxx.h>

using std::string;
using std::cin;
using std::cout;
using std::getline;
using std::endl;


bool is_composite(mpz_class & num) {
	mpz_class sr("0"), i("2"), tmp("0");
	bool composite = false;

	sr = sqrt(num);

	if (num % 2 == 0 || num % sr == 0)
		composite = true;
	else {
		i += 1;
		sr += 1;
	}

	for (;!composite && sr >= i ; i+=2) {
		if (num % i == 0)
			composite = true;
	}
	return composite;
}


int main() {
	freopen("../data.in", "r", stdin);
	mpz_class a = mpz_class(0);
	string str;
	int n;
	cin >> n;
	while (cin.get()!='\n')
		continue;
	for (int i = 0; i < n; i++) {
		getline(cin, str);
		a.set_str(str.c_str(), 10);
		cout << "num: " << str.length() << endl;
		puts(is_composite(a) ? "composite" : "prime");
	}
}