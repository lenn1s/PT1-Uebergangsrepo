#include "sorting.h"
#include "generator.h"
#include <iostream>
#include <vector>

void compareQSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateWorstCaseQuicksort(n);
    QuickSort qs = QuickSort(data, comp);
    qs.sort();
    std::cout << "QS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

void compareQSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateBestCaseQuicksort(n);
    QuickSort qs = QuickSort(data, comp);
    qs.sort();
    std::cout << "QS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

void compareMSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateWorstCaseMergesort(n);
    MergeSort ms = MergeSort(data, comp);
    ms.sort();
    std::cout << "MS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

void compareMSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateBestCaseMergesort(n);
    MergeSort ms = MergeSort(data, comp);
    ms.sort();
    std::cout << "MS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

void compareBSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateWorstCaseBubblesort(n);
    BubbleSort bs = BubbleSort(data, comp);
    bs.sort();
    std::cout << "BS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

void compareBSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    std::vector<int> data = generateBestCaseBubblesort(n);
    BubbleSort bs = BubbleSort(data, comp);
    bs.sort();
    std::cout << "BS, n=" << n << ", counts= " << comp.getCounter() << "\n";
}

/* main entry point for the program */
int main(int argc, char *argv[]) {
    Comparator comp = Comparator();
    CountingComparator comp2 = CountingComparator(comp);

    std::cout << "Comparing worst cases \n";
    compareBSWorstcase(10, comp2);
    compareBSWorstcase(100, comp2);
    compareBSWorstcase(1000, comp2);

    compareQSWorstcase(10, comp2);
    compareQSWorstcase(100, comp2);
    compareQSWorstcase(1000, comp2);

    compareMSWorstcase(10, comp2);
    compareMSWorstcase(100, comp2);
    compareMSWorstcase(1000, comp2);

    std::cout << "Comparing best cases \n";
    compareBSBestcase(10, comp2);
    compareBSBestcase(100, comp2);
    compareBSBestcase(1000, comp2);

    compareQSBestcase(10, comp2);
    compareQSBestcase(100, comp2);
    compareQSBestcase(1000, comp2);

    compareMSBestcase(10, comp2);
    compareMSBestcase(100, comp2);
    compareMSBestcase(1000, comp2);
}