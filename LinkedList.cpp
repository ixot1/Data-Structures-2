#include "LinkedList.hpp"
#include <stdexcept>


LinkedList::LinkedList()
    : head(nullptr), size(0)
{
}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr), size(other.size)
{
    if (other.head == nullptr) return;

    head = new Node(other.head->value, other.head->priority);
    Node* currentNew = head;
    Node* currentOld = other.head->next;

    while (currentOld != nullptr) {
        currentNew->next = new Node(currentOld->value, currentOld->priority);
        currentNew = currentNew->next;
        currentOld = currentOld->next;
    }
}

LinkedList::~LinkedList()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insert(int data, unsigned int prio)
{
    Node* newNode = new Node(data, prio);

    // Insert at beginning if:
    // - list is empty
    // - new priority is smaller (higher priority)
    if (head == nullptr || prio > head->priority)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node* current = head;

        // Find proper position
        while (current->next != nullptr &&
            current->next->priority >= prio)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    ++size;
}

// Find value with maximum priority
int LinkedList::findMax() const
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }

    return head->value;
}

// Remove and return max-priority element
int LinkedList::extractMax()
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }

    Node* maxNode = head;
    int value = maxNode->value;

    head = head->next;
    delete maxNode;
    --size;

    return value;
}

// Modify priority of element data to prio
void LinkedList::modifyKey(int data, unsigned int prio)
{
    if (!head)
        throw std::runtime_error("List is empty");

    Node* prev = nullptr;
    Node* current = head;

    // Find node
    while (current && current->value != data)
    {
        prev = current;
        current = current->next;
    }

    if (!current)
        throw std::runtime_error("Element not found");

    // Remove node from current position
    if (prev)
    {
        prev->next = current->next;
    }
    else
    {
        head = current->next;
    }

    // Update priority
    current->priority = prio;

    // Reinsert node in sorted position
    if (!head || prio > head->priority)
    {
        current->next = head;
        head = current;
    }
    else
    {
        Node* temp = head;

        while (temp->next &&
            temp->next->priority >= prio)
        {
            temp = temp->next;
        }

        current->next = temp->next;
        temp->next = current;
    }
}

// Return current size
size_t LinkedList::returnSize() const
{
    return size;
}