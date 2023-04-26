import java.io.File;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class TopSortGraph {

    public static void main(String[] args) {
        File infile = new File(args[0]);
        Scanner scanner = null;

        try {
            scanner = new Scanner(infile);
        } catch (Exception e) {
            System.out.println("File not found");
            System.exit(0);
        }

        // build graph from input file
        List<Vertex> graph = buildGraphFromInput(scanner);

        // topologically sort the graph using the algorithm in the slides/textbook
        List<Vertex> sorted = null;
        try {
            sorted = topSort(graph);
        } catch (CycleFoundException e) {
            System.out.println("Cycle found");
            System.exit(0);
        }

        // print out the sorted list
        System.out.println("Topologically sorted list:");
        for (Vertex v : sorted) {
            System.out.print(v.name + " ");
        }
    }

    // given a graph, topologically sorts it
    public static List<Vertex> topSort(List<Vertex> graph) throws CycleFoundException {
        Queue<Vertex> q = new ArrayDeque<Vertex>();
        List<Vertex> sorted = new ArrayList<Vertex>();
        int counter = 0;

        // add all 0-indegree vertices to queue
        for (Vertex v : graph) {
            if (v.indegree == 0) {
                // System.out.println("Adding " + v.name + " to queue");
                q.add(v);
            }
        }

        // while queue is not empty
        while (!q.isEmpty()) {
            // pop 0-indegree vertex from queue and add to sorted list
            // System.out.println("Popping " + q.peek().name + " from queue and adding to
            // sorted list");
            Vertex v = q.remove();
            sorted.add(v);
            counter++;

            // for each neighbor of popped vertex, decrement indegree and add to queue if 0
            for (String neighbor_ : v.neighbors) {

                // get neighbor vertex corresponding to neighbor string
                Vertex neighbor = null;
                for (Vertex vertex : graph) {
                    if (vertex.name.equals(neighbor_)) {
                        neighbor = vertex;
                    }
                }

                // some logs for debugging
                // System.out.println(
                // "Neighbor of " + v.name + " is " + neighbor.name + " with indegree " +
                // neighbor.indegree);
                // System.out.println("Decrementing indegree of " + neighbor.name + " to " +
                // (neighbor.indegree - 1));

                if (--neighbor.indegree == 0) {
                    // System.out.println("Adding " + neighbor.name + " to queue");
                    q.add(neighbor);
                }
            }
        }

        // if counter not equal to number of vertices, then there is a cycle
        if (counter != graph.size()) {
            throw new CycleFoundException();
        }

        return sorted;
    }

    public static List<Vertex> buildGraphFromInput(Scanner scanner) {
        List<Vertex> graph = new ArrayList<Vertex>();

        // we read line by line until EOF
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();

            // split line by space and store first as vertex in graph
            String[] letters = line.split(" ");
            Vertex key = new Vertex(letters[0]);
            graph.add(key);

            // and rest as neighbors to vertex
            for (int i = 1; i < letters.length; i++) {
                key.neighbors.add(letters[i]);
            }
        }

        // for each vertex in graph, set indegree
        for (Vertex key : graph) {
            for (String neighbor : key.neighbors) {
                for (Vertex v : graph) {
                    if (v.name.equals(neighbor)) {
                        v.indegree++;
                    }
                }
            }
        }

        return graph;
    }
}