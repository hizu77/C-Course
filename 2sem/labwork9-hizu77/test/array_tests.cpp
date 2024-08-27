#include "lib/Adapters.h"
#include "lib/TransformAdapter.h"
#include "lib/FilterAdapter.h"
#include "lib/TakeAdapter.h"
#include "lib/ReverseAdapter.h"
#include "lib/KeysValuesAdapter.h"
#include <gtest/gtest.h>
#include <unordered_set>

using namespace adapters;

TEST(AdaptersTestSuit, VectorFilterTestDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 3, 5};
    std::vector<int> ans;

    auto removed = vec | filter([](int i){return i % 2 == 1;});

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorFilterTestNoDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 3, 5};
    std::vector<int> ans;

    for (auto i :  vec | filter([](int i){return i % 2 == 1;})) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorTransformTestDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 4, 9, 16, 25, 36};
    std::vector<int> ans;

    for (auto i : vec | transform([](int i){return i * i;})) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorTransformTestNoDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 4, 9, 16, 25, 36};
    std::vector<int> ans;

    auto removed = vec | transform([](int i){return i * i;});

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorTakeTestDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3};
    std::vector<int> ans;

    auto removed = vec | take(3);

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorTakeTestNoDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3};
    std::vector<int> ans;

    for (auto i : vec | take(3)) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorDropTestDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {4, 5, 6};
    std::vector<int> ans;

    auto removed = vec | drop(3);

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorDropTestNoDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {4, 5, 6};
    std::vector<int> ans;

    for (auto i : vec | drop(3)) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorReverseTestDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {6, 5, 4, 3, 2, 1};
    std::vector<int> ans;

    auto removed = vec | reverse();

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorReverseTestNoDefault) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {6, 5, 4, 3, 2, 1};
    std::vector<int> ans;

    for (auto i : vec | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapKeysTestDefault) {
    std::map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {1, 3, 4, 5};
    std::vector<int> ans;

    auto removed = map | keys();

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapKeysTestNoDefault) {
    std::map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {1, 3, 4, 5};
    std::vector<int> ans;

    for (auto i : map | keys()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapValuesTestDefault) {
    std::map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {2, 4, 5, 6};
    std::vector<int> ans;

    auto removed = map | values();

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapValuesTestNoDefault) {
    std::map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {2, 4, 5, 6};
    std::vector<int> ans;

    for (auto i : map | values()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, SetKeysTestDefault) {
    std::set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    auto removed = set | keys();

    for (auto i : removed) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, SetKeysTestNoDefault) {
    std::set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    for (auto i : set | keys()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, SetValuesTestDefault) {
    std::set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    for (auto i : set | values()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, SetValuesTestNoDefault) {
    std::set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    for (auto i : set | values()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}


TEST(AdaptersTestSuit, UnorderedMapKeysTestDefault) {
    std::unordered_map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {1, 3, 4, 5};
    std::vector<int> ans;

    auto removed = map | keys();

    for (auto i : removed) {
        ans.push_back(i);
    }

    std::sort(ans.begin(), ans.end());

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedMapKeysTestNoDefault) {
    std::unordered_map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {5, 4, 3, 1};
    std::vector<int> ans;

    for (auto i : map | keys()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedMapValuesTestDefault) {
    std::unordered_map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {2, 4, 5, 6};
    std::vector<int> ans;

    auto removed = map | values();

    for (auto i : removed) {
        ans.push_back(i);
    }

    std::sort(ans.begin(), ans.end());

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedMapValuesTestNoDefault) {
    std::unordered_map<int, int> map = {{1, 2}, {3, 4}, {4, 5}, {5, 6}};
    std::vector<int> OK = {6, 5, 4, 2};
    std::vector<int> ans;

    for (auto i : map | values()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedSetKeysTestDefault) {
    std::unordered_set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    auto removed = set | keys();

    for (auto i : removed) {
        ans.push_back(i);
    }

    std::sort(ans.begin(), ans.end());

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedSetKeysTestNoDefault) {
    std::unordered_set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {6, 5, 4, 3, 2, 1};
    std::vector<int> ans;

    for (auto i : set | keys()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedSetValuesTestDefault) {
    std::unordered_set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;

    for (auto i : set | values()) {
        ans.push_back(i);
    }

    std::sort(ans.begin(), ans.end());

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, UnorderedSetValuesTestNoDefault) {
    std::unordered_set<int> set = {1, 2, 3, 4, 5, 6};
    std::vector<int> OK = {6, 5, 4, 3, 2, 1};
    std::vector<int> ans;

    for (auto i : set | values()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest1) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {4, 16, 36};
    for(int i : v | filter([](int i){return i % 2 == 0;}) | transform([](int i){return i * i;}))
        ans.push_back(i);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest2) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {1, 9, 25};
    for(int i : v | filter([](int i){return i % 2 == 1;}) | transform([](int i){return i * i;}))
        ans.push_back(i);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest3) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {25, 9, 1};
    for(int i : v | filter([](int i){return i % 2 == 1;}) | transform([](int i){return i * i;})
                    | reverse())
        ans.push_back(i);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest4) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {3, 4};

    for (int i : v | take(4) | drop(2)) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest5) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> ans;
    std::vector<int> OK = {1, 2, 3, 4, 5, 6};

    for (int i : v | reverse() | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, VectorComboTest6) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    for (auto i : v | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                 | take(3) | drop(1) | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapComboKeysTest1) {
    std::map<int, int> v = {{1, 11}, {2, 22}, {3, 33}, {4, 44}, {5, 55}, {6, 66}, {7, 77},
                            {8, 88}, {9, 99}, {12, 132}};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    for (auto i : v | keys() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                  | take(3) | drop(1) | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, MapComboValuesTest2) {
    std::map<int, int> v = {{11, 1}, {22, 2}, {33, 3}, {44, 4}, {55, 5}, {66, 6}, {77, 7},
                            {88, 8}, {99, 9}, {132, 12}};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    for (auto i : v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                  | take(3) | drop(1) | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, SetComboTest1) {
    std::set<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    for (auto i : v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                  | take(3) | drop(1) | reverse()) {
        ans.push_back(i);
    }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorViewTest) {
    std::set<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

     auto view = v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                  | take(3) | drop(1) | reverse();

     for (auto it : view) {
         ans.push_back(it);
     }

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorViewTest2) {
    std::set<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    auto view = v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                | take(3) | drop(1) | reverse();

    auto view_begin = view.begin();
    auto view_end = view.end();
    --view_end;

    ASSERT_EQ(*view_begin, 18);
    ASSERT_EQ(*view_end, 12);
}

TEST(AdaptersTestSuit, IteratorReverseViewTest3) {
    std::set<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    auto view = v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                | take(3) | drop(1);

    auto it = --view.end();
    for (; it != view.begin(); --it) {
        ans.push_back(*it);
    }
    ans.push_back(*it);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorReverseViewTest4) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12};

    auto view = v | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;})
                | take(3) | drop(1);

    auto it = --view.end();
    for (; it != view.begin(); --it) {
        ans.push_back(*it);
    }
    ans.push_back(*it);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorReverseViewTest5) {
    std::map<int, int> v = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    std::vector<int> ans;
    std::vector<int> OK = {12, 6};

    auto view = v | keys() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;});

    auto it = --view.end();
    for (; it != view.begin(); --it) {
        ans.push_back(*it);
    }
    ans.push_back(*it);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorReverseViewTest6) {
    std::map<int, int> v = {{2, 3}, {3, 6}, {4, 4}, {5, 8}, {6, 9}, {7, 7}};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12, 6};

    auto view = v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;});

    auto it = --view.end();
    for (; it != view.begin(); --it) {
        ans.push_back(*it);
    }
    ans.push_back(*it);

    ASSERT_EQ(ans, OK);
}

TEST(AdaptersTestSuit, IteratorEqualTest) {
    std::map<int, int> v = {{2, 3}, {3, 6}, {4, 4}, {5, 8}, {6, 9}, {7, 7}};
    std::vector<int> ans;
    std::vector<int> OK = {18, 12, 6};

    auto view = v | values() | transform([](int i){return i * 2;}) | filter([](int i){return i % 3 == 0;});

    auto it = view.begin();
    auto it2 = it;

    while (it != view.end()) {
        ASSERT_EQ(*it, *it2);
        ++it;
        ++it2;
    }

}


