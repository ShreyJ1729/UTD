import numpy as np

class Octree:
    # Initialize an octree with a bounding box
    def __init__(self, bounds):
        self.bounds = bounds
        self.points = []
        self.children = []

    # Add a point to the octree
    def add_point(self, point):
        # If the point is outside the bounding box, do nothing
        if not self.bounds.contains(point):
            return

        # If the octree is a leaf node (i.e., has no children),
        # and the number of points is less than the maximum capacity,
        # add the point to this octree
        if len(self.children) == 0 and len(self.points) < 8:
            self.points.append(point)
            return

        # If the octree is at capacity, subdivide the space
        # and add the point to the appropriate child octree
        if len(self.children) == 0:
            self.subdivide()

        for child in self.children:
            child.add_point(point)

    # Subdivide the space into eight octants
    def subdivide(self):
        min_x, min_y, min_z = self.bounds.min
        max_x, max_y, max_z = self.bounds.max

        x_mid = (min_x + max_x) / 2
        y_mid = (min_y + max_y) / 2
        z_mid = (min_z + max_z) / 2

        # Create eight child octrees
        octant1 = Octree(Box(min_x, min_y, min_z, x_mid, y_mid, z_mid))
        octant2 = Octree(Box(x_mid, min_y, min_z, max_x, y_mid, z_mid))
        octant3 = Octree(Box(min_x, y_mid, min_z, x_mid, max_y, z_mid))
        octant4 = Octree(Box(x_mid, y_mid, min_z, max_x, max_y, z_mid))
        octant5 = Octree(Box(min_x, min_y, z_mid, x_mid, y_mid, max_z))
        octant6 = Octree(Box(x_mid, min_y, z_mid, max_x, y_mid, max_z))
        octant7 = Octree(Box(min_x, y_mid, z_mid, x_mid, max_y, max_z))
        octant8 = Octree(Box(x_mid, y_mid, z_mid, max_x, max_y, max_z))

        self.children = [octant1, octant2, octant3, octant4,
                         octant5, octant6, octant7, octant8]

        # Add the points in this octree to the appropriate child octree
        for point in self.points:
            for child in self.children:
                child.add_point(point)

        self.points = []

    # Query the octree for points within a given region
    def query(self, bounds):
        # If the query region does not intersect with the bounding box
        # of this octree, return an empty list
        if not bounds.intersects(self.bounds):
            return []

        # If the octree is a leaf node (i.e., has no children),
        # return the points in this octree
        if len(self.children) == 0:
            return self.points

        # Otherwise, query the child octrees and return the results
        points = []
        for child in self.children:
            points += child.query(bounds)
        return points
