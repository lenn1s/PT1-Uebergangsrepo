#ifndef SORTING_H
#define SORTING_H

#include <vector>

class Comparator
{
public:
    int compare(std::vector<int> data, int x, int y) { 
        // TODO
        throw std::logic_error("Not implemented.");
    }
};

class CountingComparator
{
protected:
    Comparator &comp;
    int counter;

public:
    void resetCounter() {
        // TODO
        throw std::logic_error("Not implemented.");
    }
    int getCounter() {
        // TODO
        throw std::logic_error("Not implemented.");
    }
    int compare(std::vector<int> data, int x, int y)
    {
        // TODO
        throw std::logic_error("Not implemented.");
    }
    CountingComparator(Comparator &comp) : comp(comp), counter(0){}
};

class SortingAlgorithm
{
protected:
    std::vector<int>& data;
    CountingComparator &comp;

public:
    void swap(int i, int j);
    virtual void sort(){}
    SortingAlgorithm(std::vector<int>& sortData, CountingComparator &comparator) : data(sortData), comp(comparator){}
    virtual ~SortingAlgorithm() = default;
};

class BubbleSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
};

class MergeSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

protected:
    std::vector<int> aux;

public:
    MergeSort(std::vector<int>& data, CountingComparator& comp) : SortingAlgorithm(data, comp), aux(data.size()) {}
    void sort() override;
    void split(int l, int r);
    void merge(int l, int r, int halfway);
};

class QuickSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
    int divide(int l, int r);
    void qs(int l, int r);
};

#endif /* SORTING_H */