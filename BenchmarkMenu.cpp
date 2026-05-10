#include "BenchmarkMenu.hpp"
#include "Benchmark.hpp"
#include <iostream>

//helper function for cleaning std::cin buffer
static void clearInput() {
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

//get and return a choice from the user 
static int getUserChoice() {
	int choice;
	while (!(std::cin >> choice)) {
		clearInput();
		std::cout << "Incorrect choice, please try again. \n";
	}
	return choice;
}

static void methodMenu(int queueType) {
	while (true) {
		std::cout << "\n--- Choose the method for benchmarking. ---\n";
		std::cout << "1. insert (add an element with random priority)\n";
		std::cout << "2. extractMax (delete and return an element with highest priority)\n";
		std::cout << "3. findMax (return an element with highest priority)\n";
		std::cout << "4. modifyKey (change priority of element)\n";
		std::cout << "5. returnSize (return size of the queue)\n";
		std::cout << "6. RUN ALL TESTS FOR THIS QUEUE\n";
		std::cout << "0. GO BACK\n";

		int methodChoice = getUserChoice();

		if (methodChoice == 0) break;

		std::cout << "\n Executing the benchmark... \n";

		switch (queueType) {
		case 1: //BinaryHeap
			switch (methodChoice) {
			case 1:	Benchmark::testInsertHeap();
				break;
			case 2:	Benchmark::testExtractMaxHeap();
				break;
			case 3:	Benchmark::testFindMaxHeap();
				break;
			case 4:	Benchmark::testModifyKeyHeap();
				break;
			case 5:	Benchmark::testReturnSizeHeap();
				break;
			case 6:
				Benchmark::testInsertHeap();
				Benchmark::testExtractMaxHeap();
				Benchmark::testFindMaxHeap();
				Benchmark::testModifyKeyHeap();
				Benchmark::testReturnSizeHeap();
				break;
			default: std::cout << "Incorrect choice, please try again \n"; break;
			}
			break;
		case 2: //SinglyLinkedList
			switch (methodChoice) {
			case 1:	Benchmark::testInsertList();
				break;
			case 2:	Benchmark::testExtractMaxList();
				break;
			case 3:	Benchmark::testFindMaxList();
				break;
			case 4:	Benchmark::testModifyKeyList();
				break;
			case 5:	Benchmark::testReturnSizeList();
				break;
			case 6:
				Benchmark::testInsertList();
				Benchmark::testExtractMaxList();
				Benchmark::testFindMaxList();
				Benchmark::testModifyKeyList();
				Benchmark::testReturnSizeList();
				break;
			default: std::cout << "Incorrect choice, please try again \n"; break;
			}
			break;
		}
	}
}


void runMainMenu() {
	while (true) {
		std::cout << "\n====== Choose the queue variant for benchmarking ======\n";
		std::cout << "1. Binary Heap\n";
		std::cout << "2. Singly Linked List\n";
		std::cout << "0. EXIT\n";

		int structureChoice = getUserChoice();

		if (structureChoice == 0) {
			std::cout << "Closing program...\n";
			break;
		}

		if (structureChoice >= 1 && structureChoice <= 2) {
			methodMenu(structureChoice);
		}
		else {
			std::cout << "Invalid choice. Try 1 or 2.\n";
		}
	}
}