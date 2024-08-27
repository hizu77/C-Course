#include "lib/TaskScheduler.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(AnyTestSuit, DefaultTestInt) {
    any any = 5;
    ASSERT_EQ(5, any.Cast<int>());
}

TEST(AnyTestSuit, DefaultFailureTest) {
    any any = 5;
    ASSERT_ANY_THROW(any.Cast<float>());
}

TEST(AnyTestSuit, DefaultTestVector) {
    any any = std::vector<int>{1, 2};
    ASSERT_EQ((std::vector<int>{1, 2}),  any.Cast<std::vector<int>>());
}

TEST(AnyTestSuit, SequentialTestTrue) {
    any any = 5;
    ASSERT_EQ(5, any.Cast<int>());

    any = std::vector<int> {1, 2, 3};

    ASSERT_EQ((std::vector<int>{1, 2, 3}), any.Cast<std::vector<int>>());
}

TEST(AnyTestSuit, SequentialTestFalse) {
    any any = 5;
    ASSERT_TRUE(4 != any.Cast<int>());

    any = std::vector<int> {1, 2, 3};

    ASSERT_TRUE((std::vector<int>{1, 2}) != any.Cast<std::vector<int>>());
}

TEST(AnyTestSuit, CopyTest1) {
    any any_ = 5;
    any any2 = any_;

    ASSERT_EQ(any2.Cast<int>(), 5);
}

TEST(AnyTestSuit, CopyTest2) {
    any any_(5);
    any any2(any_);

    ASSERT_EQ(any2.Cast<int>(), 5);
}

TEST(AnyTestSuit, CopyTest3) {
    any any_;
    any_ = 5;

    any any2;
    any2 = any_;

    ASSERT_EQ(any2.Cast<int>(), 5);
}

TEST(AnyTestSuit, MultiTest) {
    any any_ = 4;
    ASSERT_EQ(any_.Cast<int>(), 4);

    char a = '5';
    any_ = a;
    ASSERT_EQ('5', any_.Cast<char>());

    any any2 = any_;
    std::vector<std::string> as = {"12", "23"};
    any2 = as;
    ASSERT_EQ(any2.Cast<std::vector<std::string>>(), as);

    any2 = true;
    ASSERT_EQ(any2.Cast<bool>(), true);

}

TEST(SchedulerTestSuit, TwoArgsAddTest1) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](int a, int b) {return a * b - a + b;},2, 3);
    ASSERT_EQ(scheduler.getResult<int>(id0), 7);
}

TEST(SchedulerTestSuit, TwoArgsAddTest2) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](size_t a, const std::string& b) {return a * b.size() - a + b.size();},2, "321");
    ASSERT_EQ(scheduler.getResult<size_t>(id0), 7);
}

TEST(SchedulerTestSuit, OneArgAddTest1) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](int a) {return a * 2;},2);
    ASSERT_EQ(scheduler.getResult<int>(id0), 4);
}

TEST(SchedulerTestSuit, OneArgAddTest2) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](float a) {return std::sqrt(a);}, 4);
    ASSERT_EQ(scheduler.getResult<float>(id0), 2);
}

TEST(SchedulerTestSuit, ZeroArgAddTest1) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([]() {return 54;});
    ASSERT_EQ(scheduler.getResult<int>(id0), 54);
}

TEST(SchedulerTestSuit, getFutureResult) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](int a, int b) {return a * b - a + b;},2, 3);
    auto id1 = scheduler.add([](int a){return a * 2;}, scheduler.getResult<int>(id0));

    ASSERT_EQ(scheduler.getResult<int>(id1), 14);
}

TEST(SchedulerTestSuit, MultygetFutureResult) {
    TTaskScheduler scheduler;

    auto id0 = scheduler.add([](int a, int b) {return a * b - a + b;},2, 3);
    auto id1 = scheduler.add([](int a){return a * 2;}, scheduler.getResult<int>(id0));
    auto id2 = scheduler.add([](int a){return a * 3;}, scheduler.getResult<int>(id1));

    ASSERT_EQ(scheduler.getResult<int>(id2), 42);
}

TEST(SchedulerTestSuit, ExecuteAllTest) {
    TTaskScheduler scheduler;
    size_t counter = 0;

    auto id0 = scheduler.add([&counter](int a, int b) {counter++; return a * b - a + b;},2, 3);
    scheduler.executeAll();

    ASSERT_EQ(counter, 1);
    ASSERT_EQ(scheduler.getResult<int>(id0), 7);
}

TEST(SchedulerTestSuit, InvariantExecuteAllTest) {
    TTaskScheduler scheduler;
    size_t counter = 0;

    auto id0 = scheduler.add([&counter](int a, int b) {counter++; return a * b - a + b;},2, 3);
    auto id1 = scheduler.add([](int a){return a * 2;}, scheduler.getResult<int>(id0));
    auto id2 = scheduler.add([](int a){return a * 3;}, scheduler.getResult<int>(id0));

    scheduler.executeAll();

    ASSERT_EQ(counter, 1);
    ASSERT_EQ(scheduler.getResult<int>(id1), 14);
    ASSERT_EQ(scheduler.getResult<int>(id2), 21);

}

TEST(SchedulerTestSuit, SchedulerAllTest) {
    float a = 1;
    float b = -2;
    float c = 0;

    TTaskScheduler scheduler;
    size_t counter = 0;

    auto id1 = scheduler.add([&counter](float a, float c){++counter; return -4 * a * c;}, a, c);

    auto id2 = scheduler.add([&counter](float b, float v){++counter; return b * b + v;}, b, scheduler.getFutureResult<float>(id1));

    auto id3 = scheduler.add([](float b, float d){return -b + std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));

    auto id4 = scheduler.add([](float b, float d){return -b - std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));

    auto id5 = scheduler.add([](float a, float v){return v/(2*a);}, a, scheduler.getFutureResult<float>(id3));

    auto id6 = scheduler.add([](float a, float v){return v/(2*a);},a, scheduler.getFutureResult<float>(id4));

    auto id7 = scheduler.add([](float a){return a + 5;},scheduler.getFutureResult<float>(id6));

    scheduler.executeAll();

    ASSERT_EQ(counter, 2);
    ASSERT_EQ(scheduler.getResult<float>(id1), 0);
    ASSERT_EQ(scheduler.getResult<float>(id2), 4);
    ASSERT_EQ(scheduler.getResult<float>(id3), 4);
    ASSERT_EQ(scheduler.getResult<float>(id4), 0);
    ASSERT_EQ(scheduler.getResult<float>(id5), 2);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
    ASSERT_EQ(scheduler.getResult<float>(id7), 5);
}

TEST(SchedulerTestSuit, SequenceSchedulerAllTest) {
    TTaskScheduler scheduler;

    size_t counter_1 = 0;
    size_t counter_2 = 0;
    size_t counter_3 = 0;
    size_t counter_4 = 0;


    auto id1 = scheduler.add([&counter_1](){++counter_1; return 4;});
    auto id2 = scheduler.add([&counter_2](int a){++counter_2; return a + 1;}, scheduler.getFutureResult<int>(id1));
    auto id3 = scheduler.add([&counter_3](int a){++counter_3; return a + 2;}, scheduler.getFutureResult<int>(id2));
    auto id4 = scheduler.add([&counter_4](int a, int b){++counter_4; return a + b;}, scheduler.getFutureResult<int>(id2), scheduler.getFutureResult<int>(id3));

    scheduler.executeAll();

    ASSERT_EQ(counter_1, 1);
    ASSERT_EQ(counter_2, 1);
    ASSERT_EQ(counter_3, 1);
    ASSERT_EQ(counter_4, 1);

    int i1 = scheduler.getResult<int>(id1);
    int i2 = scheduler.getResult<int>(id2);
    int i3 = scheduler.getResult<int>(id3);
    int i4 = scheduler.getResult<int>(id4);

    ASSERT_EQ(i1, 4);
    ASSERT_EQ(i2, 5);
    ASSERT_EQ(i3, 7);
    ASSERT_EQ(i4, 12);
}