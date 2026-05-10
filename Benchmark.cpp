#include "Benchmark.hpp"
#include "BinaryHeap.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>

const int Benchmark::REPETITIONS = 10;
const int Benchmark::SEED = 12345;
const std::vector<int> Benchmark::SIZES = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

// Helper class for random number generation
class RandomGenerator {
private:
    std::default_random_engine generator;
    std::uniform_int_distribution<> distribution;
public:
    RandomGenerator(int seed, int min, int max) : generator(seed), distribution(min, max) {}
    int getNext() { return distribution(generator); }
};

// ============================================================================
// MAIN BENCHMARK ENGINE 
// ============================================================================
template <typename StructureType>
static void runBenchmark(const std::string& testName, const std::string& fileName, int numCopies,
    std::function<void(StructureType&, RandomGenerator&, RandomGenerator&, int)> operation)
{
    std::cout << "\n[ Starting benchmark: " << testName << " ]\n";
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    file << "Size_N;Avg_Time_ns\n";

    for (int n : Benchmark::SIZES) {
        double totalTimeNs = 0.0;

        for (int r = 0; r < Benchmark::REPETITIONS; ++r) {

            RandomGenerator prepDataRng(Benchmark::SEED + r, 1, 2000000);
            RandomGenerator prepPrioRng(Benchmark::SEED + 999 + r, 1, 5000000);

            // Preparation phase, filling initial data into a single prototype
            StructureType prototype{};
            for (int j = 0; j < n; ++j) {
                prototype.insert(prepDataRng.getNext(), prepPrioRng.getNext());
            }

            // Create copies using the copy constructor
            std::vector<StructureType> copies;
            copies.reserve(numCopies);
            for (int i = 0; i < numCopies; ++i) {
                copies.push_back(prototype);
            }

            // RNGs to be used during the actual time measurement
            RandomGenerator testDataRng(Benchmark::SEED + 777 + r, 2000001, 4000000);
            RandomGenerator testPrioRng(Benchmark::SEED + 888 + r, 1, 5000000);

            // Measurement phase
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) {
                operation(copies[i], testDataRng, testPrioRng, n);
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            totalTimeNs += (static_cast<double>(duration) / numCopies);
        }

        double avgTimeNs = totalTimeNs / Benchmark::REPETITIONS;
        file << n << ";" << avgTimeNs << "\n";
        std::cout << "   N = " << n << " \tfinished. Avg: " << avgTimeNs << " ns\n";
    }
    file.close();
}

// ==========================================================================================================================
// BENCHMARK FOR MODIFY-KEY (ADDS VECTOR STORING INSERTED VALUES ENSURING THAT <EXISTING> VALUE GETS PICKED FOR MODIFICATION)
// ==========================================================================================================================
template <typename StructureType>
static void runModifyBenchmark(const std::string& testName, const std::string& fileName, int numCopies,
    std::function<void(StructureType&, int, unsigned int)> operation)
{
    std::cout << "\n[ Starting benchmark: " << testName << " ]\n";
    std::ofstream file(fileName);
    if (!file.is_open()) return;
    file << "Size_N;Avg_Time_ns\n";

    for (int n : Benchmark::SIZES) {
        double totalTimeNs = 0.0;

        for (int r = 0; r < Benchmark::REPETITIONS; ++r) {

            std::vector<int> insertedDataHistory; // Store inserted values to ensure valid lookup

            RandomGenerator prepDataRng(Benchmark::SEED + r, 1, 2000000);
            RandomGenerator prepPrioRng(Benchmark::SEED + 999 + r, 1, 5000000);

            // Preparation phase into a single prototype
            StructureType prototype{};
            for (int j = 0; j < n; ++j) {
                int data = prepDataRng.getNext();
                unsigned int prio = prepPrioRng.getNext();
                insertedDataHistory.push_back(data);
                prototype.insert(data, prio);
            }

            // Create copies using the copy constructor
            std::vector<StructureType> copies;
            copies.reserve(numCopies);
            for (int i = 0; i < numCopies; ++i) {
                copies.push_back(prototype);
            }

            // Choose an element to modify (guaranteed to exist)
            RandomGenerator idxRng(Benchmark::SEED + r + 123, 0, n - 1);
            int targetData = insertedDataHistory[idxRng.getNext() % n];

            // Generate a completely new priority
            RandomGenerator newPrioRng(Benchmark::SEED + r + 456, 1, 5000000);
            unsigned int newPriority = newPrioRng.getNext();

            // Measurement phase
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) {
                operation(copies[i], targetData, newPriority);
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            totalTimeNs += (static_cast<double>(duration) / numCopies);
        }

        double avgTimeNs = totalTimeNs / Benchmark::REPETITIONS;
        file << n << ";" << avgTimeNs << "\n";
        std::cout << "   N = " << n << " \tfinished. Avg: " << avgTimeNs << " ns\n";
    }
    file.close();
}

// ============================================================================
// TESTS: BINARY HEAP
// ============================================================================

void Benchmark::testInsertHeap() {
    runBenchmark<BinaryHeap>("Heap::insert", "Heap_insert.csv", 50,
        [](BinaryHeap& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.insert(dRng.getNext(), pRng.getNext()); });
}

void Benchmark::testExtractMaxHeap() {
    runBenchmark<BinaryHeap>("Heap::extractMax", "Heap_extractMax.csv", 50,
        [](BinaryHeap& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.extractMax(); });
}

void Benchmark::testFindMaxHeap() {
    runBenchmark<BinaryHeap>("Heap::findMax", "Heap_findMax.csv", 50,
        [](BinaryHeap& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.findMax(); });
}

void Benchmark::testModifyKeyHeap() {
    runModifyBenchmark<BinaryHeap>("Heap::modifyKey", "Heap_modifyKey.csv", 50,
        [](BinaryHeap& q, int targetData, unsigned int newPrio) { q.modifyKey(targetData, newPrio); });
}

void Benchmark::testReturnSizeHeap() {
    runBenchmark<BinaryHeap>("Heap::returnSize", "Heap_returnSize.csv", 50,
        [](BinaryHeap& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.returnSize(); });
}

// ============================================================================
// TESTS: LINKED LIST
// ============================================================================

void Benchmark::testInsertList() {
    runBenchmark<LinkedList>("List::insert", "List_insert.csv", 50,
        [](LinkedList& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.insert(dRng.getNext(), pRng.getNext()); });
}

void Benchmark::testExtractMaxList() {
    runBenchmark<LinkedList>("List::extractMax", "List_extractMax.csv", 50,
        [](LinkedList& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.extractMax(); });
}

void Benchmark::testFindMaxList() {
    runBenchmark<LinkedList>("List::findMax", "List_findMax.csv", 50,
        [](LinkedList& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.findMax(); });
}

void Benchmark::testModifyKeyList() {
    runModifyBenchmark<LinkedList>("List::modifyKey", "List_modifyKey.csv", 50,
        [](LinkedList& q, int targetData, unsigned int newPrio) { q.modifyKey(targetData, newPrio); });
}

void Benchmark::testReturnSizeList() {
    runBenchmark<LinkedList>("List::returnSize", "List_returnSize.csv", 50,
        [](LinkedList& q, RandomGenerator& dRng, RandomGenerator& pRng, int n) { q.returnSize(); });
}