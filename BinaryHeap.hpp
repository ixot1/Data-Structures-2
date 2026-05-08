//Binary heap priority queue header file
#pragma once
#include "Queues.hpp"

class BinaryHeap : public Queues {
private:

	struct Node {
		int value;
		unsigned int priority;
	};

	Node* heap;
	size_t capacity;
	size_t size;

	void resize();
	void heapify(size_t index);

public:
	
	void insert(int data, unsigned int prio) override;
	int extractMax() override;
	int findMax() const override;
	void modifyKey(int data, unsigned int prio) override;
	size_t returnSize() const override;
	
	BinaryHeap(size_t capacity = 16);
	~BinaryHeap();
};