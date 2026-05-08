// BinaryHeap.cpp
#include "BinaryHeap.hpp"
#include <stdexcept>
#include <utility> // for std::swap

BinaryHeap::BinaryHeap(size_t capacity)    : capacity(capacity), size(0)
{
    heap = new Node[capacity];
}

BinaryHeap::~BinaryHeap()
{
    delete[] heap;
}

// Resize heap when full
void BinaryHeap::resize()
{
    capacity *= 2;

    // Handle case when capacity is 0 to avoid multiplying by 2 and still having 0
    if (capacity == 0) 
    { 
        capacity = 1; 
    }

    Node* newHeap = new Node[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        newHeap[i] = heap[i];
    }

    delete[] heap;
    heap = newHeap;
}

// Restore heap downward
void BinaryHeap::heapify(size_t index)
{
    size_t largest = index;

    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < size && heap[left].priority > heap[largest].priority)
    {
        largest = left;
    }

    if (right < size && heap[right].priority > heap[largest].priority)
    {
        largest = right;
    }

    if (largest != index)
    {
        std::swap(heap[index], heap[largest]);
        heapify(largest);
    }
}

// Insert new element
void BinaryHeap::insert(int data, unsigned int prio)
{
    if (size == capacity)
    {
        resize();
    }

    size_t index = size;

    heap[index].value = data;
    heap[index].priority = prio;

    ++size;

    // Bubble up
    while (index > 0)
    {
        size_t parent = (index - 1) / 2;

        if (heap[parent].priority >= heap[index].priority)
        {
            break;
        }

        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

// Remove and return max value
int BinaryHeap::extractMax()
{
    if (size == 0)
    {
        throw std::out_of_range("Heap is empty");
    }

    int maxValue = heap[0].value;

    heap[0] = heap[size - 1];
    --size;

    if (size > 0)
    {
        heapify(0);
    }

    return maxValue;
}

// Return max value without removing
int BinaryHeap::findMax() const
{
    if (size == 0)
    {
        throw std::out_of_range("Heap is empty");
    }

    return heap[0].value;
}

// Change priority of a node with given data
void BinaryHeap::modifyKey(int data, unsigned int prio)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (heap[i].value == data)
        {
            unsigned int oldPriority = heap[i].priority;
            heap[i].priority = prio;

            // Bubble up if priority increased
            if (prio > oldPriority)
            {
                size_t index = i;

                while (index > 0)
                {
                    size_t parent = (index - 1) / 2;

                    if (heap[parent].priority >= heap[index].priority)
                    {
                        break;
                    }

                    std::swap(heap[parent], heap[index]);
                    index = parent;
                }
            }
            else
            {
                // Heapify down if priority decreased
                heapify(i);
            }

            return;
        }
    }

    throw std::invalid_argument("Element not found in heap");
}

// Return current size
size_t BinaryHeap::returnSize() const
{
    return size;
}