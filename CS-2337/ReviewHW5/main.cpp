#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Node
{
    int data;
    Node *next;
};

int getRandomNumber()
{
    return std::rand();
}

Node *generateLinkedList()
{
    Node *head = new Node;
    head->data = getRandomNumber();
    head->next = nullptr;

    Node *cur = head;

    for (int i = 0; i < 4999; i++)
    {
        Node *newNode = new Node;
        newNode->data = getRandomNumber();
        newNode->next = nullptr;

        cur->next = newNode;
        cur = cur->next;
    }

    return head;
}

#include <iostream>

void bubbleSort(int arr[], int n)
{
    int comparisons = 0;

    int swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swaps++;
            }
        }
    }

    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Number of swaps: " << swaps << std::endl;
}

void selectionSort(int arr[], int n)
{
    int comparisons = 0;

    int swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            comparisons++;

            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;

            swaps++;
        }
    }

    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Number of swaps: " << swaps << std::endl;
}

#include <iostream>

void insertionSort(int arr[], int n)
{
    int comparisons = 0;

    int swaps = 0;

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            comparisons++;
            swaps++;

            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Number of swaps: " << swaps << std::endl;
}

#include <iostream>

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high, int &comparisons, int &swaps)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        comparisons += high - low;
        swaps++;

        quickSort(arr, low, pivot - 1, comparisons, swaps);
        quickSort(arr, pivot + 1, high, comparisons, swaps);
    }
}
void quickSort(int arr[], int n)
{
    int comparisons = 0;

    int swaps = 0;

    quickSort(arr, 0, n - 1, comparisons, swaps);

    std::cout << "Number of comparisons: " << comparisons << std::endl;
    std::cout << "Number of swaps: " << swaps << std::endl;
}
#include <iostream>

std::pair<Node *, Node *> split(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    Node *secondHalf = slow->next;
    slow->next = nullptr;

    return std::make_pair(head, secondHalf);
}

Node *merge(Node *firstHalf, Node *secondHalf, int &comparisons)
{
    Node *head = new Node;
    head->next = nullptr;

    Node *cur = head;

    while (firstHalf != nullptr && secondHalf != nullptr)
    {
        if (firstHalf->data <= secondHalf->data)
        {
            cur->next = firstHalf;
            firstHalf = firstHalf->next;
        }
        else
        {
            cur->next = secondHalf;
            secondHalf = secondHalf->next;
        }
        cur = cur->next;

        comparisons++;
    }

    if (firstHalf != nullptr)
    {
        cur->next = firstHalf;
    }
    else
    {
        cur->next = secondHalf;
    }

    return head->next;
}

Node *mergeSort(Node *head, int &comparisons)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    std::pair<Node *, Node *> halves = split(head);

    Node *firstHalf = mergeSort(halves.first, comparisons);
    Node *secondHalf = mergeSort(halves.second, comparisons);

    return merge(firstHalf, secondHalf, comparisons);
}

void mergeSort(Node *head)
{
    int comparisons = 0;

    head = mergeSort(head, comparisons);

    std::cout << "Number of comparisons: " << comparisons << std::endl;
}

int main()
{
    Node *head = generateLinkedList();

    int arr1[5000], arr2[5000], arr3[5000], arr4[5000];

    Node *cur = head;
    for (int i = 0; i < 5000; i++)
    {
        arr1[i] = cur->data;
        arr2[i] = cur->data;
        arr3[i] = cur->data;
        arr4[i] = cur->data;
        cur = cur->next;
    }

    std::cout << "-----Bubble Sort-----" << std::endl;
    bubbleSort(arr1, 5000);
    std::cout << "-----Selection Sort-----" << std::endl;
    selectionSort(arr2, 5000);
    std::cout << "-----Insertion Sort-----" << std::endl;
    insertionSort(arr3, 5000);
    std::cout << "-----Quick Sort-----" << std::endl;
    quickSort(arr4, 5000);
    std::cout << "-----Merge Sort-----" << std::endl;
    mergeSort(head);

    return 0;
}
