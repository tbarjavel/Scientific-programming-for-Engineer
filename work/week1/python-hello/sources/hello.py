import sys


# 1
print("Hello World")
print(len(sys.argv))
print(type(sys.argv))  # sys.argv is a list

# 2
n = int(sys.argv[1])
print("Hello {}".format(n))

# 3
n = int(sys.argv[1])
s = 0
for k in range(1, n + 1):  # n additions are necessary
    s += k
print("Hello {}".format(s))
# overhead?

# 4
n = int(sys.argv[1])
s = 0
for k in range(1, n + 1):
    s += k
print("Hello {}".format(s))
