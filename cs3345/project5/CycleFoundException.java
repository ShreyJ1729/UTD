public class CycleFoundException extends Exception {
    public CycleFoundException() {
        super("Cycle found in graph");
    }
}