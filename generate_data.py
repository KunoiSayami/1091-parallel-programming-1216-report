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
import os
import random

if __name__ == '__main__':
    n = random.randint(50, 100)
    with open('data.in', 'w') as fout:
        fout.write(f'{n + 3}\n')
        fout.write(f'{2**23209 - 1}\n')
        for _i in range(n):
            sz = [random.randint(0, 9) for _ in range(random.randint(6000, 10000))]
            sz.append(random.choice(range(1, 10, 2)))
            print(''.join(map(str, sz)), file=fout)
        fout.write(f'{2**21701 - 1}\n')
        fout.write(f'{2**19937 - 1}\n')

