//Linked list priority queue header file
#pragma once
#include "Queues.hpp"

class LinkedList : public Queues {

private:
	struct Node {
		int value;
		unsigned int priority;
		Node* next;

		Node(int e, unsigned int p, Node* n = nullptr) : value(e), priority(p), next(n) {}
	};
	Node* head;
	size_t size;

public:
	LinkedList();
	LinkedList(const LinkedList& other);	//copy constructor for easy creation of copies during benchmarking
	~LinkedList() override;

	void insert(int data, unsigned int prio) override;
	int extractMax() override;
	int findMax() const override;
	void modifyKey(int data, unsigned int prio) override;
	size_t returnSize() const override;
};