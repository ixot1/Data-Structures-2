#pragma once
#include <vector>
#include <string>
#include <functional>

class Benchmark {

public:
    static const int REPETITIONS;
    static const int SEED;
    static const std::vector<int> SIZES;

    static void testInsertHeap();
    static void testExtractMaxHeap();
    static void testFindMaxHeap();
    static void testModifyKeyHeap();
    static void testReturnSizeHeap();

    static void testInsertList();
    static void testExtractMaxList();
    static void testFindMaxList();
    static void testModifyKeyList();
    static void testReturnSizeList();
};