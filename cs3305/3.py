def b(n):
    if n == 0:
        return 5
    else:
        return 2 * b(n - 1) + n - 2**n


def pred(n):
    return -(2**n + 1) * n + 7 * 2**n - 2


for i in range(1000):
    if b(i) != pred(i):
        print(i)
        break
