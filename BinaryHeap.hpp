//Binary heap priority queue header file
#pragma once
#include "Queues.hpp"

class BinaryHeap : public Queues {
private:

	struct Node {
		int value;
		unsigned int priority;
		long long order;
	};

	Node* heap;
	size_t capacity;
	size_t size;
	long long insertionCounter;

	void resize();
	void heapify(size_t index);

public:

	BinaryHeap(size_t capacity = 16);
	~BinaryHeap() override;

	void insert(int data, unsigned int prio) override;
	int extractMax() override;
	int findMax() const override;
	void modifyKey(int data, unsigned int prio) override;
	size_t returnSize() const override;
	
};