#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (C) 2020 KunoiSayami
#
# This module is part of 1091-parallel-programming-1216-report and is released under
# the AGPL v3 License: https://www.gnu.org/licenses/agpl-3.0.txt
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
import filecmp
import random
import subprocess
import sys
import numpy as np


def generate_data(n: int, output=None) -> None:
    for _i in range(n):
        for _j in range(n):
            print(random.randint(10, 20), end=' ', file=output)
        print(file=output)


def calc(n: int) -> None:
    matrix_a_, matrix_b_ = [], []
    with open('data.in') as fin:
        fin.readline()
        currn = []
        for _ in range(n):
            currn.extend(map(int, fin.readline().strip().split()))
            matrix_a_.append(currn)
            currn = []
        for _ in range(n):
            currn.extend(map(int, fin.readline().strip().split()))
            matrix_b_.append(currn)
            currn = []
    a = np.array(matrix_a_)
    b = np.array(matrix_b_)
    out = np.matmul(a, b)
    print(out)
    with open('really.out', 'w') as fout:
        for _i in out:
            fout.write(' '.join(map(str, _i)))
            fout.write('\n')


def main(really: bool) -> None:
    file = None
    if really:
        file = open('data.in', 'w')
    n = random.randint(32, 128)
    print(n, file=sys.stderr)
    print(n, n, file=file)
    generate_data(n, file)
    generate_data(n, file)
    if really:
        file.close()
        with open('data.in') as data_in, open('result.out', 'w') as data_out:
            p = subprocess.Popen([sys.argv[1]], stdin=data_in, stdout=data_out, stderr=sys.stdout)
            calc(n)
            p.wait()
        print(filecmp.cmp('really.out', 'result.out'))


if __name__ == '__main__':
    main('run' in sys.argv)