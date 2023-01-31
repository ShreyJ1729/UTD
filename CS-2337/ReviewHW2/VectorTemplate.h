#include <vector>
using namespace std;

#ifndef VECTOR_TEMPLATE

template <class T>
class VectorTemplate
{
public:
    vector<T> data;

    VectorTemplate() {};
    VectorTemplate(vector<T> data)
    {
        this->data = data;
    };

    void setVector(T element)
    {
        this->data.push_back(element);
    };

    vector<T> getVector()
    {
        return data;
    };

    void InsertionSort()
    {
        int i, j;
        T key;
        for (i = 1; i < this->data.size(); i++)
        {
            key = this->data.at(i);
            j = i - 1;

            // Move elements of this->data(0..i-1],
            // that are greater than key, to one
            // position ahead of their
            // current position
            while (j >= 0 && this->data.at(j) > key)
            {
                this->data.at(j + 1) = this->data.at(j);
                j = j - 1;
            }
            this->data.at(j + 1) = key;
        }
    };

    bool BinarySearch(T element)
    {
        int index = 0;
        int low = 0;
        int high = this->data.size()-1;
        int mid;

        while (high - low > 1)
        {
            mid = (high + low) / 2;
            if (this->data.at(mid) < element)
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
        };

        return (this->data.at(low) == element || this->data.at(mid) == element);
    };
};

#define VECTOR_TEMPLATE
#endif