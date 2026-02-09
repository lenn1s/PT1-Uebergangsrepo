#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "../src/sorting.h"
#include "../src/generator.h"
#include <memory>

TEST_CASE("A1: Comparator") {
    Comparator* origComp = new Comparator();
    std::vector<int> data = {1, 2, 3, 4};
    CHECK(origComp->compare(data, 0, 1) < 0);
}

TEST_CASE("A1: Counting Comparator") {
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    std::vector<int> data = {1, 2, 3, 4};
    CHECK(comp->compare(data, 0, 1) < 0);
    CHECK(comp->compare(data, 2, 1) > 0);
    CHECK(comp->compare(data, 3, 2) > 0);
    CHECK(comp->compare(data, 3, 3) == 0);
    CHECK(comp->getCounter() == 4);
    comp->resetCounter();
    CHECK(comp->getCounter() == 0);
}

TEST_CASE("A2: BubbleSort") {
    std::vector<int> data = {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    BubbleSort* sort = new BubbleSort(data, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 45);
    data[0] = 2;
    data[1] = 1;
    comp->resetCounter();
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 17);
}

TEST_CASE("A2: QuickSort") {
    std::vector<int> data = {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    QuickSort* sort = new QuickSort(data, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 41);
}

TEST_CASE("A2: MergeSort") {
    std::vector<int> data = {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    MergeSort* sort = new MergeSort(data, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 25);
}

TEST_CASE("A3: Generator") {
    std::vector<int> data = generateSorted(10);
    std::vector<int> validation = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == validation[i]);
    }  
}

static int runBubbleCount(std::vector<int> (*gen)(int), int n)
{
    std::vector<int> data = gen(n);
    Comparator orig;
    CountingComparator comp(orig);
    BubbleSort sort(data, comp);
    sort.sort();
    return comp.getCounter();
}

static int runQuickCount(std::vector<int> (*gen)(int), int n) {
    std::vector<int> data = gen(n);
    Comparator orig;
    CountingComparator comp(orig);
    QuickSort sort(data, comp);
    sort.sort();
    return comp.getCounter();
}

static int runMergeCount(std::vector<int> (*gen)(int), int n) {
    std::vector<int> data = gen(n);
    Comparator orig;
    CountingComparator comp(orig);
    MergeSort sort(data, comp);
    sort.sort();
    return comp.getCounter();
}

TEST_CASE("A3: Comparison counts (worst cases) - allow >= reference") {
    struct Case { int n; int ref; };

    SUBCASE("BubbleSort worst-case generator") {
        Case cases[] = {{10, 45}, {100, 4950}, {1000, 499500}};
        for (auto c : cases) {
            int cnt = runBubbleCount(generateWorstCaseBubblesort, c.n);
            CHECK(cnt >= c.ref);
        }
    }

    SUBCASE("QuickSort worst-case generator") {
        Case cases[] = {{10, 54}, {100, 5049}, {1000, 500499}};
        for (auto c : cases) {
            int cnt = runQuickCount(generateWorstCaseQuicksort, c.n);
            CHECK(cnt >= c.ref);
        }
    }

    SUBCASE("MergeSort worst-case generator") {
        Case cases[] = {{10, 34}, {100, 672}, {1000, 9976}};
        for (auto c : cases) {
            int cnt = runMergeCount(generateWorstCaseMergesort, c.n);
            CHECK(cnt >= c.ref);
        }
    }
}

TEST_CASE("A3: Comparison counts (best cases) - allow <= reference") {
    struct Case { int n; int ref; };

    SUBCASE("BubbleSort best-case generator") {
        Case cases[] = {{10, 9}, {100, 99}, {1000, 999}};
        for (auto c : cases) {
            int cnt = runBubbleCount(generateBestCaseBubblesort, c.n);
            CHECK(cnt <= c.ref);
        }
    }

    SUBCASE("QuickSort best-case generator") {
        Case cases[] = {{10, 25}, {100, 543}, {1000, 8498}};
        for (auto c : cases) {
            int cnt = runQuickCount(generateBestCaseQuicksort, c.n);
            CHECK(cnt <= c.ref);
        }
    }

    SUBCASE("MergeSort best-case generator") {
        Case cases[] = {{10, 9}, {100, 99}, {1000, 999}};
        for (auto c : cases) {
            int cnt = runMergeCount(generateBestCaseMergesort, c.n);
            CHECK(cnt <= c.ref);
        }
    }
}