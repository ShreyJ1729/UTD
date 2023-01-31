// Shrey Joshi
// Net ID: SXJ210081

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
    for (int i = 2; i < sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}

// gets next prime after the inputted start value
int getNextPrime(int start)
{
    int curr = start;
    while (true)
    {
        if (isPrime(curr))
            break;
        curr++;
    }
    return curr;
}

int getRehashedIndex(int key, int size, int table[])
{
    // add to hashtable, using quadratic probing
    int index = key % size;
    bool available = (table[index] == 0);
    int i = 0;
    while (true)
    {
        // quadratic probing to update index
        index = (key + i * i) % size;
        available = (table[index] == 0);
        if (available)
            break;
        // cout << "rehash: index " << index << " not available, val is " << table[index] << ". trying again" << endl;
        i++;
    }
    // cout << "rehash: available at index " << index << endl;
    // cout << "rehash: size: " << size << endl;
    return index;
}

class HashTable
{
private:
    const double LOAD_FACTOR = 0.5;
    int *table = new int[11];
    int size = 11;

public:
    HashTable() {}

    int getHash(int key)
    {
        return key % size;
    }

    void add(int key)
    {
        // add to hashtable, using quadratic probing
        int index = key % size;
        bool available = (table[index] == 0);
        int i = 0;
        while (true)
        {
            // quadratic probing to update index
            index = (key + i * i) % size;
            available = (table[index] == 0);
            if (available)
                break;
            cout << "index " << index << " not available, val is " << table[index] << ". trying again" << endl;
            i++;
        }
        cout << "available at index " << index << endl;
        cout << "size: " << size << endl;

        table[index] = key;

        // resize if needed
        if (getEmptySpaces() < size * LOAD_FACTOR)
        {
            cout << "resizing!" << endl;
            this->print();
            // resize hashtable to smallest prime number more than double old size
            int newSize = getNextPrime(size * 2);
            int *newTable = new int[newSize];

            for (int i = 0; i < size; i++)
            {
                if (table[i] == 0)
                {
                    int rehashedIndex = getRehashedIndex(key, newSize, newTable);
                    cout << "rehashed index is " << rehashedIndex << endl;
                    newTable[rehashedIndex] = table[i];
                }
            }

            table = newTable;
            size = newSize;
            cout << "resized!" << endl;
            this->print();
        }
    }

    int getEmptySpaces()
    {
        int count = 0;
        for (int i = 0; i < size; i++)
            if (table[i] == 0)
                count++;
        return count;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << ((table[i] == 0) ? "_" : to_string(table[i])) << ((i == size - 1) ? "" : " ");
        }
        cout << endl;
    }
};

int main()
{
    int numvals;
    int val;
    cout << "enter number of values: ";
    cin >> numvals;

    HashTable table = HashTable();

    for (int i = 0; i < numvals; i++)
    {
        cin >> val;
        table.add(val);
    }

    cout << "HashTable: ";
    table.print();
}