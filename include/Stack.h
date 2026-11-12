#pragma once

#include <cstddef>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class ArrayStack {
public:
    explicit ArrayStack(std::size_t capacity = 100)
        : items_(capacity), top_(-1) {}

    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Array stack overflow");
        }
        items_[static_cast<std::size_t>(++top_)] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Array stack underflow");
        }
        return items_[static_cast<std::size_t>(top_--)];
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Array stack is empty");
        }
        return items_[static_cast<std::size_t>(top_)];
    }

    bool isEmpty() const { return top_ < 0; }
    bool isFull() const { return top_ + 1 == static_cast<int>(items_.size()); }
    std::size_t size() const { return static_cast<std::size_t>(top_ + 1); }
    std::size_t capacity() const { return items_.size(); }

    std::vector<T> contents() const {
        return std::vector<T>(items_.begin(), items_.begin() + top_ + 1);
    }

private:
    std::vector<T> items_;
    int top_;
};

template <typename T>
class LinkedStack {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        explicit Node(const T& item, std::unique_ptr<Node> link)
            : value(item), next(std::move(link)) {}
    };

public:
    LinkedStack() = default;
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    void push(const T& value) {
        top_ = std::make_unique<Node>(value, std::move(top_));
        ++size_;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Linked stack underflow");
        }
        T value = top_->value;
        top_ = std::move(top_->next);
        --size_;
        return value;
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Linked stack is empty");
        }
        return top_->value;
    }

    bool isEmpty() const { return top_ == nullptr; }
    bool isFull() const { return false; }
    std::size_t size() const { return size_; }

    std::vector<T> contents() const {
        std::vector<T> result;
        for (const Node* node = top_.get(); node != nullptr; node = node->next.get()) {
            result.push_back(node->value);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    std::unique_ptr<Node> top_;
    std::size_t size_ = 0;
};
