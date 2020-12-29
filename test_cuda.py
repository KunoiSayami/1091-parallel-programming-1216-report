import random


def generate_data(n: int) -> None:
    for _i in range(n):
        for _j in range(n):
            print(random.randint(10, 20), end=' ')
        print()


def main():
    n = random.randint(32, 8192)
    print(n, n)
    generate_data(n)
    generate_data(n)


if __name__ == '__main__':
    main()