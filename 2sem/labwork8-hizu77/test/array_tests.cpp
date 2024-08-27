#include "lib/BinarySearchTree.h"
#include <gtest/gtest.h>
#include <vector>

using namespace bst;

TEST(BSTreeTestSuit, CreateInorderTest) {
    InOrderBST<int> tree;
    ASSERT_TRUE(tree.empty());

    InOrderBST<int> tree1({1, 2, 3});
    ASSERT_TRUE(!tree1.empty());

    InOrderBST<std::string> tree2;
    ASSERT_TRUE(tree.empty());

    InOrderBST<std::string> tree3({"aba", "bcs", "ttt"});
    ASSERT_TRUE(!tree3.empty());

    InOrderBST<int> tree4(tree1);
    ASSERT_TRUE(!tree4.empty());

    InOrderBST<int> tree5 = tree1;
    ASSERT_TRUE(!tree5.empty());

}

TEST(BSTreeTestSuit, CreateSizeTest) {
    InOrderBST<int> tree;
    ASSERT_TRUE(tree.size() == 0);

    InOrderBST<int> tree1({1, 2, 3});
    ASSERT_TRUE(tree1.size() == 3);

    InOrderBST<std::string> tree2;
    ASSERT_TRUE(tree.size() == 0);

    InOrderBST<std::string> tree3({"aba", "bcs", "ttt"});
    ASSERT_TRUE(tree3.size() == 3);

    InOrderBST<int> tree4(tree1);
    ASSERT_TRUE(tree4.size() == 3);

    InOrderBST<int> tree5 = tree1;
    ASSERT_TRUE(tree4.size() == 3);

}

TEST(BSTreeTestSuit, EqualTest) {
    InOrderBST<int> tree;

    InOrderBST<int> tree1({1, 2, 3});
    ASSERT_TRUE(tree != tree1);

    InOrderBST<std::string> tree2;

    InOrderBST<std::string> tree3({"aba", "bcs", "ttt"});
    ASSERT_TRUE(tree2 != tree3);

    InOrderBST<int> tree4(tree1);
    ASSERT_TRUE(tree4 == tree1);

    InOrderBST<int> tree5 = tree1;
    ASSERT_TRUE(tree5 == tree1);

}

TEST(BSTreeTestSuit, InsertTest) {
    InOrderBST<int> tree;
    tree.insert(5);
    tree.insert(4);

    ASSERT_TRUE(tree.size() == 2);

    InOrderBST<std::string> tree2;
    tree2.insert("aaa");
    tree2.insert("bbb");

    ASSERT_TRUE(tree2.size() == 2);

    InOrderBST<int> tree3;
    tree3.insert(1, 5);

    ASSERT_TRUE(tree3.size() == 4);

    InOrderBST<std::string> tree4({"aba", "bcs"});
    tree4.insert("aaa");
    tree4.insert("bbb");

    ASSERT_TRUE(tree4.size() == 4);

}

TEST(BSTreeTestSuit, InorderIteratorTest) {
    InOrderBST<int> tree;
    tree.insert(5);
    tree.insert(4);

    auto it = tree.begin();
    ASSERT_TRUE(*it == 4);

    auto it1 = tree.end();
    --it1;
    ASSERT_TRUE(*it1 == 5);

    tree.insert(6, 8);

    std::vector<int> res({4, 5, 6, 7});
    std::vector<int> cur;

    for (auto it4 = tree.begin(); it4 != tree.end(); ++it4) {
        cur.push_back(*it4);
    }

    ASSERT_TRUE(res == cur);

    std::vector<int> cur2;
    for (auto it4 : tree) {
        cur2.push_back(it4);
    }

    ASSERT_TRUE(cur2 == cur);

    auto it5 = tree.end();

    ASSERT_TRUE(*--it5 == 7);

}

TEST(BSTreeTestSuit, FindIteratorTest) {
    InOrderBST<int> tree({ 8, 3, 10, 1, 6, 14, 4, 7, 13});

    auto it = tree.find(6);

    std::vector<int> OK({6, 7, 8, 10, 13, 14});
    std::vector<int> OK2({6, 4, 3, 1});

    std::vector<int> cur;
    std::vector<int> cur2;

    while (it != tree.end()) {
        cur.push_back(*it);
        ++it;
    }

    auto it2 = tree.find(6);

    while (it2 != tree.begin()) {
        cur2.push_back(*it2);
        --it2;
    }
    cur2.push_back(*it2);


    ASSERT_TRUE(OK == cur);
    ASSERT_TRUE(OK2 == cur2);

}

TEST(BSTreeTestSuit, ReverseIteratorTest) {
    InOrderBST<int> tree({8, 3, 4, 1, 7, 11});

    std::vector<int> OK({11, 8, 7, 4, 3, 1});
    std::vector<int> cur;

    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
        cur.push_back(it->data);
    }
    ASSERT_TRUE(OK == cur);
}

TEST(BSTreeTestSuit, InorderDecrementTest) {
    InOrderBST<int> tree;

    tree.insert(8);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    tree.insert(7);
    tree.insert(11);

    std::vector<int> OK({11, 8, 7, 4, 3, 1});
    std::vector<int> cur;

    auto it = tree.end();
    --it;

    while (it != tree.begin()) {
        cur.push_back(*it);
        --it;
    }

    cur.push_back(*it);
    ASSERT_TRUE(OK == cur);
}

TEST(BSTreeTestSuit, InsertEqualTest) {
    InOrderBST<int> tree({5, 6, 1, 2, 3, 10});

    std::vector<int> result;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        result.push_back(*it);
    }

    std::vector<int> OK{1, 2, 3, 5, 6, 10};
    ASSERT_TRUE(result == OK);

    InOrderBST<char> tree1;
    tree1.insert('c');
    tree1.insert('d');
    tree1.insert('a');
    tree1.insert('b');

    std::vector<char> result1;
    std::vector<char> OK1{'a', 'b', 'c', 'd'};

    for (auto i : tree1) {
        result1.push_back(i);
    }

    ASSERT_TRUE(result1 == OK1);

    InOrderBST<int> tree2;
    std::vector<int> result2;
    tree1.insert(0, 9);

    auto it2 = tree2.begin();
    for (size_t i = 0; i < tree2.size(); ++i) {
        ASSERT_TRUE(i == *it2);
        ++it2;
    }
}

TEST(BSTreeTestSuit, FindTest) {
    InOrderBST<int> tree;
    tree.insert(5, 10);

    auto it = tree.find(6);
    ASSERT_TRUE(it != tree.end());

    auto it1 = tree.find(10);
    ASSERT_TRUE(it1 == tree.end());

    auto it2 = tree.find(11);
    ASSERT_TRUE(it2 == tree.end());

    tree.insert(11);

    auto it3 = tree.find(11);
    ASSERT_TRUE(it3 != tree.end());

}

TEST(BSTreeTestSuit, LowerBoundTest) {
    InOrderBST<int> tree({4, 1, 13, 7, 2, 11});

    auto it = tree.lower_bound(6);
    ASSERT_TRUE(*it == 7);

    auto it1 = tree.lower_bound(11);
    ASSERT_TRUE(*it1 == 11);

    auto it2 = tree.lower_bound(14);
    ASSERT_TRUE(it2 == tree.end());

}

TEST(BSTreeTestSuit, UpperBoundTest) {
    InOrderBST<int> tree({4, 1, 13, 7, 2, 11});

    auto it = tree.upper_bound(6);
    ASSERT_TRUE(*it == 7);

    auto it1 = tree.upper_bound(11);
    ASSERT_TRUE(*it1 == 13);

    auto it2 = tree.upper_bound(14);
    ASSERT_TRUE(it2 == tree.end());

}


TEST(BSTreeTestSuit, CountTest) {
    InOrderBST<int> tree({4, 1, 13, 7, 2, 11});

    ASSERT_TRUE(1 == tree.count(1));

    ASSERT_TRUE(0 == tree.count(14));
}

TEST(BSTreeTestSuit, ContainsTest) {
    InOrderBST<int> tree({4, 13, 7, 2, 11});

    ASSERT_TRUE(tree.contains(2));

    tree.insert(1);
    ASSERT_TRUE(tree.contains(1));

    ASSERT_TRUE(!tree.contains(14));
}

TEST(BSTreeTestSuit, ExtractTest) {
    InOrderBST<int> tree({4, 13, 7, 2, 11});

    ASSERT_TRUE(tree.contains(7));

    tree.extract(7);
    ASSERT_TRUE(!tree.contains(7));

    std::vector<int> OK({2, 4, 11, 13});
    std::vector<int> result;

    for (auto it : tree) {
        result.push_back(it);
    }

    ASSERT_TRUE(result == OK);
}

TEST(BSTreeTestSuit, MergeTest) {
    InOrderBST<int> tree({4, 13, 7, 2, 11});

    InOrderBST<int> tree1;
    tree1.insert(5);
    tree1.insert(12);

    tree.merge(tree1);

    std::vector<int> OK({2, 4, 5, 7, 11, 12, 13});
    std::vector<int> result;

    for (auto it : tree) {
        result.push_back(it);
    }

    ASSERT_TRUE(OK == result);
}

TEST(BSTreeTestSuit, PreorderIteratorTest) {
    PreOrderBST<int> tree({8, 3, 10, 1, 6, 14, 4, 7, 13});

    std::vector<int> OK({8, 3, 1, 6, 4, 7, 10, 14, 13});

    size_t cur_idx = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        ASSERT_TRUE(*it == OK[cur_idx++]);
    }
}

TEST(BSTreeTestSuit, PostorderIteratorTest) {
    PostOrderBST<int> tree1({8, 3, 10, 1, 6, 14, 4, 7, 13});

    std::vector<int> OK({1, 4, 7, 6, 3, 13, 14, 10, 8});

    size_t cur_idx = 0;
    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
        ASSERT_TRUE(*it == OK[cur_idx++]);
    }
}

TEST(BSTreeTestSuit, PreorderInsertTest) {
    PreOrderBST<int> tree;
    tree.insert(5);
    tree.insert(4);

    ASSERT_TRUE(tree.size() == 2);

    PreOrderBST<std::string> tree2;
    tree2.insert("aaa");
    tree2.insert("bbb");

    ASSERT_TRUE(tree2.size() == 2);

    PreOrderBST<int> tree3;
    tree3.insert(1, 5);

    ASSERT_TRUE(tree3.size() == 4);

    PreOrderBST<std::string> tree4({"aba", "bcs"});
    tree4.insert("aaa");
    tree4.insert("bbb");

    ASSERT_TRUE(tree4.size() == 4);

}

TEST(BSTreeTestSuit, PreorderDecrementTest) {
    PreOrderBST<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    std::vector<int> OK({13, 14, 10, 7, 4, 6, 1, 3, 8});

    size_t cur_idx = 0;
    auto it = (--tree.end());
    for (; it != tree.begin(); --it) {
        ASSERT_TRUE(*it == OK[cur_idx++]);
    }

    ASSERT_TRUE(*it == OK[cur_idx]);
}

TEST(BSTreeTestSuit, PreorderReverseIteratorTest) {
    PreOrderBST<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    std::vector<int> OK({13, 14, 10, 7, 4, 6, 1, 3, 8});

    size_t cur_idx = 0;
    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
        ASSERT_TRUE(it->data == OK[cur_idx++]);
    }

}

TEST(BSTreeTestSuit, KthLargestTest) {
    PreOrderBST<int> tree({{8, 3, 10, 1, 6, 14, 4, 7, 13}});

    ASSERT_TRUE(tree.kth_largest(2) == 3);

    InOrderBST<std::string> tree1;
    tree1.insert("abs");
    tree1.insert("abc");
    tree1.insert("abd");
    tree1.insert("aba");

    ASSERT_TRUE(tree1.kth_largest(2) == "abc");

}

TEST(BSTreeTestSuit, EraseTest) {
    PreOrderBST<int> tree({1, 2, 3});

    ASSERT_TRUE(tree.erase(1) == 1);
    ASSERT_TRUE(tree.erase(1) == 0);

}

TEST(BSTreeTestSuit, SwapTest) {
    PreOrderBST<int> tree({1, 2});
    PreOrderBST<int> tree1({4, 5});

    swap(tree, tree1);

    ASSERT_TRUE(*tree.begin() == 4);
    ASSERT_TRUE(*(--tree.end()) == 5);

    ASSERT_TRUE(*tree1.begin() == 1);
    ASSERT_TRUE(*(--tree1.end()) == 2);

}
