"""
This file is used to visualize the result of Line Fitting problem.
"""
import matplotlib.pyplot as plt
import numpy as np

with open('equations.txt', 'r') as f:
    equations = f.readlines()

for equation in equations:
    x = np.linspace(-5, 10, 2)
    y = eval(equation)
    plt.plot(x, y, label=equation)

with open('points.txt', 'r') as f:
    points = f.readlines()

for point in points:
    x, y = point.split()
    plt.plot(x, y, 'ro')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Line Fitting')
plt.legend()
plt.show()

