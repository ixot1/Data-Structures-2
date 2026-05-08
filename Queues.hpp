//interface for queue implementations
#pragma once

class Queues {

public:

	virtual void insert(int data, unsigned int prio) = 0;			// adds "data" with priority "prio"
	virtual int extractMax() = 0;									// extracts and returns an element with max priority
	virtual int findMax() const = 0;								// finds and returns an element with max priority
	virtual void modifyKey(int data, unsigned int prio) = 0;		// changes priority of element "data" to "prio"  
	virtual size_t returnSize() const = 0;							// returns the size of a queue
	virtual ~Queues() {};											// destructor
};