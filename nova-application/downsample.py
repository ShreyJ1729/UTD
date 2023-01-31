import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm
import math

"""
Note: this is a rough implementation of pointcloud downsampling that was done in < 1 hour
A better implementation would average all points in a voxel to obtain a new unique point or use an octree structure to
ensure better efficiency for sparser areas in the pointcloud.

Be sure to have the csv file in the same dir level as this file and renamed to "input.csv"
Change the below variable to change the grid size
"""
GRID_SIZE = 100

# helper function: given a sorted array and a value, finds the nearest number to the given value in the given array
def find_nearest(array,value):
    idx = np.searchsorted(array, value, side="left")
    if idx > 0 and (idx == len(array) or math.fabs(value - array[idx-1]) < math.fabs(value - array[idx])):
        return array[idx-1]
    else:
        return array[idx]

def csv_to_numpy(name):
    df = pd.read_csv(name)
    xyz = np.array(df[['x', 'y', 'z']])
    return xyz

def process_points(xyz, grid_size):
    # get min and max values for each of three dimensions
    xyzmin = np.min(xyz, axis=0)
    xyzmax = np.max(xyz, axis=0)

    # create NxNxN voxel grid:
    x_grid = np.linspace(xyzmin[0], xyzmax[0], grid_size)
    y_grid = np.linspace(xyzmin[1], xyzmax[1], grid_size)
    z_grid = np.linspace(xyzmin[2], xyzmax[2], grid_size)

    # iterate over each point in the pointcloud (tqdm is for progress bar)
    for i in tqdm(range(len(xyz))):
        point = xyz[i]
        x = point[0]
        y = point[1]
        z = point[2]

        # fit the pointcloud point to nearest point on voxel grid
        x_new = find_nearest(x_grid, x)
        y_new = find_nearest(y_grid, y)
        z_new = find_nearest(z_grid, z)

        # update pointcloud as we iterate over it (instead of creating a new output np.array to save memory for large pointclouds)
        xyz[i] = [x_new, y_new, z_new]

    # remove duplicate points
    xyz = np.unique(xyz, axis=0)
    
    print("new number of points: ", len(xyz))
    return xyz

def vizualize(xyz):
    fig = plt.figure(figsize=(12, 12))
    ax = fig.add_subplot(projection='3d')
    ax.scatter(xyz[:, 0], xyz[:, 1], xyz[:, 2])
    plt.show()

def save_output(xyz):
    # save filtered pointcloud down to a csv file
    output = pd.DataFrame({'x': xyz[:, 0], 'y': xyz[:, 1], 'z': xyz[:, 2]})
    output.to_csv('output.csv', index=False)

def main():
    xyz = csv_to_numpy("input.csv")
    xyz = process_points(xyz, GRID_SIZE)
    vizualize(xyz)
    save_output(xyz)

if __name__ == "__main__":
    main()