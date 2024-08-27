#pragma once
#include "any.h"
#include <vector>

class TTaskScheduler {
public:

    using task_id = size_t;

    TTaskScheduler() : id_(0), updated_(false) {}

    template<typename Func>
    auto add(const Func& func) {
        auto cur_task = std::make_shared<ZeroArgsTask<Func>>(func, id_);
        Adder(cur_task);

        return id_++;
    }

    template<typename Func, typename Arg1>
    auto add(const Func& func, Arg1 arg1) {
        auto cur_task = std::make_shared<OneArgsTask<Func, Arg1>>(func, arg1, id_);
        Adder(cur_task);

        return id_++;
    }

    template<typename Func, typename Arg1, typename Arg2>
    auto add(const Func& func, Arg1 arg1, Arg2 arg2) {
        auto cur_task = std::make_shared<TwoArgsTask<Func, Arg1, Arg2>>(func, arg1, arg2, id_);
        Adder(cur_task);

        return id_++;
    }

    template<typename T>
    auto getFutureResult(size_t need_id){
        task_graph_[need_id].push_back(id_);
        updated_ = false;

        return GetFutureResult<T>(tasks_[need_id]);
    }

    template<typename T>
    auto getResult(task_id need_id) {
        if (!tasks_[need_id]->isExecuted()) {
            executeAll();
        }

        return tasks_[need_id]->GetResult().Cast<T>();
    }

    void executeAll() {
        if (!updated_) {
            TopologicalSort();
        }

        for (int i = order_.size() - 1; i >= 0; --i) {
            if (!tasks_[order_[i]]->isExecuted()) {
                tasks_[order_[i]]->execute();
            }
        }
    }

private:
    struct TaskBase {
        virtual ~TaskBase() = default;
        virtual void execute() = 0;

        virtual bool isExecuted() = 0;
        virtual any GetResult() = 0;
    };

    void Adder(const std::shared_ptr<TaskBase>& cur_task) {
        tasks_.push_back(cur_task);
        task_graph_.emplace_back();
        order_.push_back(id_);
    }

    template<typename T>
    class GetFutureResult {
    public:
        GetFutureResult(const std::shared_ptr<TaskBase>& ptr) : ptr_(ptr.get()) {}

        operator T() {
            return ptr_->GetResult().Cast<T>();
        }

    private:
        TaskBase* ptr_;
    };

    template<typename Func>
    class ZeroArgsTask : public TaskBase {
    public:

        ZeroArgsTask(const Func& func, size_t id)
                : function_(func), task_id(id), is_executed_(false) {}

        any GetResult() override {
            return result_;
        }

        bool isExecuted() override {
            return is_executed_;
        }

        void execute() override {
            result_ = function_();
            is_executed_ = true;
        }

    private:
        Func function_;

        bool is_executed_;
        any result_;
        task_id task_id;
    };

    template<typename Func, typename Arg>
    class OneArgsTask : public TaskBase {
    public:

        OneArgsTask(const Func& func, const Arg& arg, size_t id)
                : function_(func), arg_(arg), task_id(id), is_executed_(false) {}

        any GetResult() override {
            return result_;
        }

        bool isExecuted() override {
            return is_executed_;
        }

        void execute() override {
            result_ = function_(arg_);
            is_executed_ = true;
        }

    private:
        Func function_;
        Arg arg_;

        bool is_executed_;
        any result_;
        task_id task_id;
    };

    template<typename Func, typename Arg1, typename Arg2>
    class TwoArgsTask : public TaskBase {
    public:

        TwoArgsTask(const Func& func, const Arg1& arg1, const Arg2& arg2, size_t id)
            : function_(func), arg_1_(arg1), arg_2_(arg2), task_id(id), is_executed_(false) {}

        any GetResult() override {
            return result_;
        }

        bool isExecuted() override {
            return is_executed_;
        }

        void execute() override {
            result_ = function_(arg_1_, arg_2_);
            is_executed_ = true;
        }

    private:
        Func function_;
        Arg1 arg_1_;
        Arg2 arg_2_;

        bool is_executed_;
        any result_;
        task_id task_id;
    };

    void DFS(size_t cur, std::vector<bool>& visited) {
        visited[cur] = true;

        for (auto to : task_graph_[cur]) {
            if (!visited[to]) {
                DFS(to, visited);
            }
        }

        order_.push_back(cur);
    }

    void TopologicalSort() {
        order_.clear();
        std::vector<bool> visited(id_);

        for (size_t i = 0; i < id_; ++i) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }

        updated_ = true;
    }

    std::vector<std::shared_ptr<TaskBase>> tasks_;
    std::vector<std::vector<size_t>> task_graph_;
    std::vector<size_t> order_;

    bool updated_;
    task_id id_;
};