import java.util.ArrayList;
import java.util.List;

public class MySearchTree<T extends Comparable<T>> {

    private Node root;
    private int size;

    private class Node {
        T value;
        Node left;
        Node right;

        public Node(T value) {
            this.value = value;
        }
    }

    public void add(T value) {
        root = add(root, value);
        size++;
    }

    private Node add(Node node, T value) {
        if (node == null) {
            return new Node(value);
        } else if (value.compareTo(node.value) < 0) {
            node.left = add(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            node.right = add(node.right, value);
        }
        return node;
    }

    public boolean find(T value) {
        return find(root, value);
    }

    private boolean find(Node node, T value) {
        if (node == null) {
            return false;
        } else if (value.compareTo(node.value) < 0) {
            return find(node.left, value);
        } else if (value.compareTo(node.value) > 0) {
            return find(node.right, value);
        } else {
            return true;
        }
    }

    public int leafCount() {
        return leafCount(root);
    }

    private int leafCount(Node node) {
        if (node == null) {
            return 0;
        } else if (node.left == null && node.right == null) {
            return 1;
        } else {
            return leafCount(node.left) + leafCount(node.right);
        }
    }

    public int parentCount() {
        return parentCount(root);
    }

    private int parentCount(Node node) {
        if (node == null || (node.left == null && node.right == null)) {
            return 0;
        } else {
            return 1 + parentCount(node.left) + parentCount(node.right);
        }
    }

    public int height() {
        return height(root);
    }

    private int height(Node node) {
        if (node == null) {
            return -1;
        } else {
            int leftHeight = height(node.left);
            int rightHeight = height(node.right);
            return 1 + Math.max(leftHeight, rightHeight);
        }
    }

    public boolean isPerfect() {
        int height = height();
        return size == (1 << (height + 1)) - 1;
    }

    public List<T> ancestors(T value) {
        List<T> ancestors = new ArrayList<>();
        ancestors(root, value, ancestors);
        return ancestors;
    }

    private boolean ancestors(Node node, T value, List<T> ancestors) {
        if (node == null) {
            return false;
        } else if (value.compareTo(node.value) == 0) {
            return true;
        } else {
            if (ancestors(node.left, value, ancestors) || ancestors(node.right, value, ancestors)) {
                ancestors.add(node.value);
                return true;
            } else {
                return false;
            }
        }
    }

    public void inOrderPrint() {
        inOrderPrint(root);
    }

    private void inOrderPrint(Node node) {
        if (node != null) {
            inOrderPrint(node.left);
            System.out.print(node.value + " ");
            inOrderPrint(node.right);
        }
    }

    public void preOrderPrint() {
        preOrderPrint(root);
    }

    private void preOrderPrint(Node node) {
        if (node != null) {
            System.out.print(node.value + " ");
            preOrderPrint(node.left);
            preOrderPrint(node.right);
        }
    }

    public static void main(String[] args) {
        MySearchTree<Integer> tree = new MySearchTree<>();

        tree.add(5);
        tree.add(3);
        tree.add(7);
        tree.add(2);
        tree.add(4);
        tree.add(6);
        tree.add(8);

        System.out.println("Inorder traversal:");
        tree.inOrderPrint(); // should print "2 3 4 5 6 7 8"

        System.out.println("\nPreorder traversal:");
        tree.preOrderPrint(); // should print "5 3 2 4 7 6 8"

        System.out.println("\nHeight: " + tree.height()); // should print "2"

        System.out.println("Is perfect? " + tree.isPerfect()); // should print "false"

        System.out.println("Leaf count: " + tree.leafCount()); // should print "4"

        System.out.println("Parent count: " + tree.parentCount()); // should print "3"

        System.out.println("Ancestors of 8: " + tree.ancestors(8)); // should print "[7, 5]"

        System.out.println("Is 3 in the tree? " + tree.find(3)); // should print "true"
        System.out.println("Is 9 in the tree? " + tree.find(9)); // should print "false"
    }
}
