#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename K, typename V>
class GenericHashMap
{
private:
    vector<pair<K, V> > data;
    int size;
    hash<K> hf;

public:
    // Constructor
    GenericHashMap(int s) : size(s), data(s) {}

    // Insert a key-value pair into the hashtable
    void insert(K key, V value)
    {
        // get hash value
        int h = hf(key) % size;
        // Quadratic probing
        int i = 1;
        while (data[h].first != key && data[h].first != "")
        {
            h = (h + i * i) % size;
            i++;
        }
        // Insert the key-value pair
        data[h] = make_pair(key, value);
    }

    // Search for a key in the hashtable
    V search(K key)
    {
        // Compute the hash value
        int h = hf(key) % size;
        // Quadratic probing
        int i = 1;
        while (data[h].first != key)
        {
            h = (h + i * i) % size;
            i++;
        }
        // Return the value associated with the key
        return data[h].second;
    }

    // Delete a key from the hashtable

    void erase(K key)
    {
        // Compute the hash value
        int h = hf(key) % size;
        // Quadratic probing
        int i = 1;
        while (data[h].first != key)
        {
            h = (h + i * i) % size;
            i++;
        }
        // Mark the key-value pair as deleted
        data[h].first = "";
        data[h].second = 0;
    }

    // Rehash the hashtable
    void rehash()
    {
        // Create a new hashtable with double the size
        GenericHashMap<K, V> ht(size * 2);
        // Insert all non-deleted key-value pairs into the new hashtable
        for (auto &p : data)
        {
            if (p.first!="")
            {
                ht.insert(p.first, p.second);
            }
        }
        // Update the size and data of the current hashtable
        size = ht.size;
        data = ht.data;
    }
};

int main()
{
    // Create a hashtable
    GenericHashMap<string, int> ht(10);
    // Insert some key-value pairs
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    ht.insert("key3", 3);
    // Search for a key
    cout << ht.search("key2") << endl;
    // Delete a key
    ht.erase("key1");
    // Rehash the hashtable
    ht.rehash();
}