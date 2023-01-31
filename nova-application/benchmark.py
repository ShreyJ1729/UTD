from downsample import *
import time
from tqdm import tqdm
import matplotlib.pyplot as plt

xyz = csv_to_numpy("input.csv")

sizes = []
times = []

arr = [i for i in range(20, 10000, 10)]

for grid_size in tqdm(arr):
    grid_size = int(grid_size)
    start = time.time()
    xyz = process_points(xyz, grid_size)
    end = time.time()
    taken = end-start
    sizes.append(grid_size)
    times.append(taken)

print(sizes)
print(times)
plt.scatter(sizes[1:], times[1:])
plt.show()