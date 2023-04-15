package project1;

// Shrey Joshi
// CS 3345.501
// Project 1
// NET ID: SXJ210081

class Node {
    public Node() {
        this.next = null;
        this.data = null;
    }

    public Node(String data) {
        this.next = null;
        this.data = data;
    }

    Node next;
    String data;
}

class NameList {
    private Node head;

    public NameList() {
        this.head = new Node();
    }

    public void add(String name) {
        // add first letter of name to list if not already present
        if (name.length() > 1) {
            String firstLetter = name.substring(0, 1).toUpperCase();
            if (!this.find(firstLetter)) {
                this.add(firstLetter);
            }
        }

        // if list is empty, add name to list
        if (this.head.next == null) {
            this.head.next = new Node(name);
            return;
        }

        // otherwise alphabetically insert name into list
        // if name is less than first element, insert at head
        if (name.toLowerCase().compareTo(this.head.next.data.toLowerCase()) < 0) {
            Node temp = new Node(name);
            temp.next = this.head.next;
            this.head.next = temp;
            return;
        }

        // otherwise, iterate through list and add name
        Node iter = this.head.next;
        while (iter != null) {
            if (name.toLowerCase().compareTo(iter.data.toLowerCase()) > 0) {
                // name is greater than current element
                if (iter.next == null) {
                    // current element is last element, add name to end of list
                    iter.next = new Node(name);
                    return;
                } else if (name.toLowerCase().compareTo(iter.next.data.toLowerCase()) < 0) {
                    // name is less than next element, insert name between current and next
                    Node temp = new Node(name);
                    temp.next = iter.next;
                    iter.next = temp;
                    return;
                }
            }
            iter = iter.next;
        }
    }

    public void remove(String name) {
        Node iter = this.head.next;
        // if list is empty, return
        if (iter == null) {
            return;
        }

        // iterate through list and remove name
        while (iter != null && iter.next != null) {
            if (iter.next.data.equals(name)) {
                iter.next = iter.next.next;
            }
            iter = iter.next;
        }

        // if removed was the last one of its letter, remove the letter
        if (name.length() > 1) {
            this.removeLetter(name.substring(0, 1).toUpperCase());
        }
    }

    public void removeLetter(String letter) {
        Node iter = this.head.next;
        // if list is empty, return
        if (iter == null) {
            return;
        }

        // iterate through list and remove all strings starting with that letter
        while (iter != null && iter.next != null) {
            if (iter.next.data.substring(0, 1).toUpperCase().equals(letter)) {
                iter.next = iter.next.next;
            } else {
                iter = iter.next;
            }
        }
    }

    public Node findNode(String name) {
        Node iter = this.head.next;
        while (iter != null) {
            if (iter.data.equals(name)) {
                return iter;
            }
            iter = iter.next;
        }
        return null;
    }

    public boolean find(String name) {
        Node iter = this.head.next;
        while (iter != null) {
            if (iter.data.equals(name)) {
                return true;
            }
            iter = iter.next;
        }
        return false;
    }

    public String toString() {
        Node iter = this.head.next;
        String output = "";
        while (iter != null) {
            if (iter.data.length() == 1) {
                output += iter.data + "\n";
            } else {
                output += "\t" + iter.data + "\n";
            }
            iter = iter.next;
        }
        return output;
    }

    public static void main(String[] args) {
        NameList list = new NameList();
        list.add("Bob");
        list.add("Dan");
        list.add("ben");
        list.add("Zack");
        System.out.println("Added Bob, Dan, Ben, Zack\n");
        System.out.println(list.toString() + "\n");
        list.add("Debbie");
        list.add("Sarah");
        list.add("zoey");
        System.out.println("Added Debbie, Sarah\n");
        System.out.println(list.toString() + "\n");
        list.remove("Dan");
        list.remove("Sarah");
        list.remove("Debbie");
        System.out.println("Removed Dan, Sarah, Debbie\n");
        System.out.println(list.toString() + "\n");
        list.removeLetter("Z");
        System.out.println("Removed all names starting with Z\n");
        System.out.println(list.toString() + "\n");
    }
}