import java.util.ArrayList;

public class Vertex {
    public String name;
    public int indegree;
    public int topNum;
    public ArrayList<String> neighbors;

    public Vertex(String name) {
        this.name = name;
        this.indegree = 0;
        this.topNum = 0;
        this.neighbors = new ArrayList<String>();
    }
}
