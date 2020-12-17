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
#include <gmp.h>

using std::string;
using std::cin;
using std::cout;
using std::getline;
using std::endl;


bool check_mod_is_0(mpz_t & tmp, mpz_t & opt, mpz_t & r_opt) {
	mpz_mod(tmp, opt, r_opt);
	return !mpz_cmp_si(tmp, 0);
}

bool is_composite(mpz_t & num) {
	mpz_t sr, i, tmp;
	bool composite = false;
	mpz_inits(sr, tmp, nullptr);

	mpz_sqrt(sr, num);

	mpz_init_set_str(i, "2", 10);
	if (check_mod_is_0(tmp, num, i) ||
		check_mod_is_0(tmp, num, sr))
		composite = true;
	else {
		mpz_add_ui(i, i, 1);
		mpz_add_ui(sr, sr, 1);
	}

	for (;!composite && mpz_cmp(sr, i) >= 0; mpz_add_ui(i, i, 2)) {
		mpz_mod(tmp, num, i);
		//gmp_printf("%Zd\n", i);
		if (mpz_cmp_si(tmp, 0) == 0)
			composite = true;
	}

	mpz_clears(sr, i, tmp, nullptr);
	return composite;
}



int main() {
	freopen("../data.in", "r", stdin);
	//sqrt();
	mpz_t a;
	string str;
	int n;
	cin >> n;
	while (cin.get()!='\n')
		continue;
	for (int i = 0; i < n; i++) {
		getline(cin, str);
		mpz_init_set_str(a, str.c_str(), 10);
		cout << "num: " << str.length() << endl;
		//mpz_init_set_str(b, "0", 10);
		//mpz_init(b);
		//mpz_sqrt(b, a);
		//gmp_printf("%Zd\n", a);
		puts(is_composite(a) ? "composite" : "prime");
		mpz_clear(a);
		//mpz_clears(a, nullptr);
	}
}