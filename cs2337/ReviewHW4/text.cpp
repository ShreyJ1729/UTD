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

int getHash(int key, int size)
{
    return key % size;
}

int getEmptySpaces(int table[], int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
        if (table[i] == 0)
            count++;
    return count;
}

void printHashTable(int table[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << ((table[i] == 0) ? "_" : to_string(table[i])) << ((i == size - 1) ? "" : " ");
    }
    cout << endl;
}


void addWithoutResize(int key, int size, int table[], int LOAD_FACTOR)
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
}

void resize(int size, int table[])
{
        cout << "resizing!" << endl;
        printHashTable(table, size);
        // resize hashtable to smallest prime number more than double old size
        int newSize = getNextPrime(size * 2);
        int *newTable = new int[newSize];

        // rehash here
        for (int i = 0; i < size; i++)
        {
            if (table[i] != 0)
            {
                addWithoutResize(table[i], newSize, newTable, 0.5);
            }
        }

        table = newTable;
        size = newSize;
        cout << "resized!" << endl;
        printHashTable(table, size);
}

void add(int key, int size, int table[], int LOAD_FACTOR)
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
    if (getEmptySpaces(table, size) < size * LOAD_FACTOR) {
        table = resize(size, table);
    }
}

int main()
{
    int numvals;
    int val;
    cout << "enter number of values: ";
    cin >> numvals;

    const double LOAD_FACTOR = 0.5;
    int *table = new int[11];
    int size = 11;

    for (int i = 0; i < numvals; i++)
    {
        cin >> val;
        add(val, size, table, LOAD_FACTOR);
    }

    cout << "HashTable: ";
    printHashTable(table, size);
}