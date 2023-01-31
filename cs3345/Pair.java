public class Pair<T> {
    private T first;
    private T second;

    public Pair(T first, T second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public T getSecond() {
        return second;
    }

    public void swap() {
        T temp = first;
        first = second;
        second = temp;
    }

    public static void main(String[] args) {
        Pair<String> pair = new Pair<>("Hello", "World");
        System.out.println(pair.getFirst() + " " + pair.getSecond());
        pair.swap();
        System.out.println(pair.getFirst() + " " + pair.getSecond());
    }
}