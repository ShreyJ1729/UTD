#include "VectorTemplate.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void printVector(VectorTemplate<T> *vtemp)
{
    for (int i = 0; i < vtemp->getVector().size(); i++)
    {
        cout << vtemp->getVector().at(i) << endl;
    }
    cout << endl;
}

int main()
{
    // testing with ints
    VectorTemplate<int> *ints = new VectorTemplate<int>();
    ints->setVector(4);
    ints->setVector(2);
    ints->setVector(9);
    ints->setVector(3);
    ints->setVector(1);
    ints->setVector(0);

    printVector(ints);
    ints->InsertionSort();
    cout << "SORTED:" << endl;
    printVector(ints);
    cout << "binary search with 3: " << ints->BinarySearch(3) << endl;
    cout << "binary search with 5: " << ints->BinarySearch(5) << endl;


    cout << endl;

    // testing with doubles
    VectorTemplate<double> *doubles = new VectorTemplate<double>();
    doubles->setVector(4.3);
    doubles->setVector(2.5);
    doubles->setVector(9.1);
    doubles->setVector(3.3);
    doubles->setVector(1.9);
    doubles->setVector(0.4);

    printVector(doubles);
    doubles->InsertionSort();
    cout << "SORTED:" << endl;
    printVector(doubles);
    cout << "binary search with 1.9: " << doubles->BinarySearch(1.9) << endl;
    cout << "binary search with 2.3: " << doubles->BinarySearch(2.3) << endl;

    
    
    // testing with string
    VectorTemplate<string> *strings = new VectorTemplate<string>();
    strings->setVector("Hello");
    strings->setVector("my");
    strings->setVector("name");
    strings->setVector("is");
    strings->setVector("shrey");
    strings->setVector("joshi");

    printVector(strings);
    strings->InsertionSort();
    cout << "SORTED:" << endl;
    printVector(strings);
    cout << "binary search with 1.9: " << strings->BinarySearch("shrey") << endl;
    cout << "binary search with 2.3: " << strings->BinarySearch("hi") << endl;

}