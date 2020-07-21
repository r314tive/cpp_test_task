import matplotlib.pyplot as plt

out = []
f = open('output.txt', 'r')
for line in f:
    out.append(line)
out.sort()

inp = []
f = open('Test.txt', 'r')
for line in f:
    inp.append(line)
#out.sort()

plt.plot(out)
plt.plot(inp)
plt.show()