public class LinearProbingHashtable<K, V> {
    private int size;
    private int capacity;
    private double loadFactor;
    private Entry[] table;

    // default constructor
    public LinearProbingHashtable() {
        this(10, 0.5);
    }

    public LinearProbingHashtable(int capacity, double loadFactor) {
        if (loadFactor <= 0 || loadFactor >= 1) {
            throw new IllegalArgumentException("Invalid load factor: " + loadFactor);
        }

        if (capacity <= 0) {
            throw new IllegalArgumentException("Invalid capacity: " + capacity);
        }

        this.capacity = capacity;
        this.loadFactor = loadFactor;
        this.table = new Entry[capacity];
    }

    public boolean insert(K key, V value) {
        if (key == null) {
            throw new NullPointerException("Null key not allowed");
        }
        int hash = getHash(key);
        int index = findIndex(hash, key);
        if (index >= 0) {
            return false;
        }
        index = -index - 1;
        table[index] = new Entry<>(hash, key, value);

        size++;
        if (size > loadFactor * capacity) {
            rehash();
        }
        return true;
    }

    public V find(K key) {
        int index = getHashLocation(key);
        if (index < 0)
            return null;
        Entry<K, V> entry = (Entry<K, V>) table[index];
        return entry.value;
    }

    public boolean delete(K key) {
        int index = getHashLocation(key);
        if (index < 0)
            return false;
        Entry<K, V> entry = (Entry<K, V>) table[index];
        entry.deleted = true;
        size--;
        return true;
    }

    private void rehash() {
        int newCapacity = capacity * 2;
        Entry[] newTable = new Entry[newCapacity];
        int newSize = 0;
        for (Entry entry : table) {
            if (entry != null) {
                Entry<K, V> entry_casted = (Entry<K, V>) entry;
                if (!entry_casted.deleted) {
                    int newIndex = findIndex(newTable, entry_casted.hash, entry_casted.key);
                    newTable[newIndex] = entry;
                    newSize++;
                }
            }
        }
        table = newTable;
        capacity = newCapacity;
        size = newSize;
    }

    public int getHashTarget(K key) {
        int hash = key.hashCode();
        return hash & (capacity - 1);
    }

    public int getHashLocation(K key) {
        int hash = getHash(key);
        int index = findIndex(hash, key);
        return index >= 0 ? index : -1;
    }

    private int getHash(K key) {
        int hash = key.hashCode();
        return hash & (capacity - 1);
    }

    private int findIndex(int hash, K key) {
        int index = hash & (capacity - 1);
        int delta = 1;
        while (true) {
            Object obj = table[index];
            if (obj == null) {
                return -index - 1; // Not found
            } else if (!isDeleted(obj) && ((Entry<K, V>) obj).hash == hash && ((Entry<K, V>) obj).key.equals(key)) {
                return index; // Found
            }

            index = (index + delta) & (capacity - 1); // Linear probing
            delta++;
        }
    }

    private int findIndex(Object[] table, int hash, K key) {
        int index = hash & (table.length - 1);
        int delta = 1;
        while (true) {
            Object obj = table[index];
            if (obj == null) {
                return index; // Found
            } else if (!isDeleted(obj) && ((Entry<K, V>) obj).hash == hash && ((Entry<K, V>) obj).key.equals(key)) {
                return index; // Found
            }
            index = (index + delta) & (table.length - 1); // Linear probing
            delta++;
        }
    }

    private boolean isDeleted(Object obj) {
        return obj instanceof Entry && ((Entry<K, V>) obj).deleted;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < capacity; i++) {
            Object obj = table[i];
            if (obj == null) {
                sb.append(String.format("%d\n", i));
            } else if (isDeleted(obj)) {
                sb.append(String.format("%d  deleted\n", i));
            } else {
                Entry<K, V> entry = (Entry<K, V>) obj;
                sb.append(String.format("%d  %s, %s\n", i, entry.key, entry.value));
            }
        }
        return sb.toString();
    }

    private static class Entry<K, V> {
        int hash;
        K key;
        V value;
        boolean deleted;

        Entry(int hash, K key, V value) {
            this.hash = hash;
            this.key = key;
            this.value = value;
        }
    }

    public static void main(String[] args) {
        LinearProbingHashtable<String, Integer> table = new LinearProbingHashtable<>(4, 0.5);
        System.out.println(table.insert("apple", 1)); // true
        System.out.println(table.insert("banana", 2)); // true
        System.out.println(table.insert("cherry", 3)); // true
        System.out.println(table.insert("pear", 4)); // true
        System.out.println(table.insert("cherry", 5)); // duplicate - false
        System.out.println(table);
        System.out.println(table.find("banana")); // 2
        System.out.println(table.find("pine")); // null
        System.out.println(table.delete("apple")); // true
        System.out.println(table.delete("cone")); // false
        System.out.println(table.find("apple")); // null since apple was deleted
        System.out.println(table.getHashTarget("apple"));
        System.out.println(table.getHashLocation("apple")); // -1 since apple was deleted
    }

}