#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

void swap(std::vector<int>& data, int i, int j);

void merge(std::vector<int>& data, std::vector<int>& left, std::vector<int>& right, int size, int m);
void separate(std::vector<int>& data, int size);
std::vector<int> generateSorted(int n);

std::vector<int> generateWorstCaseMergesort(int n);
std::vector<int> generateWorstCaseQuicksort(int n);
std::vector<int> generateWorstCaseBubblesort(int n);
std::vector<int> generateBestCaseMergesort(int n);
std::vector<int> generateBestCaseQuicksort(int n);
std::vector<int> generateBestCaseBubblesort(int n);

#endif /* GENERATOR_H */