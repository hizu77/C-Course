#pragma once
#include <iterator>
#include <iostream>
#include <type_traits>
#include <cstdint>
#include <limits>

namespace bst {

    struct InOrderTag {};
    struct PreOrderTag {};
    struct PostOrderTag {};

    template<typename T>
    struct Node {
        Node(T value, Node *par) : data(value), left(nullptr), right(nullptr), parent(par) {}

        Node(Node* l, Node* r, Node* p) : left(l), right(r), parent(p) {}

        T data{};

        Node* left;
        Node* right;
        Node* parent;
    };

    template<typename Container, bool isConst>
    class Iterator {
    public:
        using value_type = typename Container::node_type;
        using key_type = typename Container::key_type;
        using reference = value_type&;
        using size_type = typename Container::size_type;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = typename Container::difference_type;

        using conditional_ptr = std::conditional_t<isConst, const pointer, pointer>;

        using travel_tag = typename Container::tag;

        Iterator(pointer ptr, bool isBegin, size_t size, pointer end) : size_(size), end_(end) {
            pos_ = (isBegin ? 0 : size);

            if (std::is_same_v<travel_tag, PreOrderTag>) {
                ptr_ = ptr;
            } else {
                ptr_ = ptr;
                while (ptr_ && ptr_->left) {
                    ptr_ = ptr_->left;
                }
            }
        }

        Iterator(pointer ptr, size_type size, pointer end) : ptr_(ptr), size_(size), end_(end), pos_(0) {}

        Iterator(const Iterator& other)
        : ptr_(other.ptr_), size_(other.size_), end_(other.end_), pos_(other.pos_) {}

        Iterator& operator=(const Iterator& other) {
            Iterator temp(other);
            Swap(temp);

            return *this;
        }

        ~Iterator() = default;

        key_type operator*() {
            return ptr_->data;
        }

        conditional_ptr operator->() {
            return ptr_;
        }

        Iterator& operator++() {
            ++pos_;

            if (pos_ >= size_ || ptr_ == end_->parent || ptr_ == end_->right) {
                ptr_ = end_;
                return *this;
            }

            if (std::is_same_v<travel_tag, InOrderTag>) {
                InorderIncr();
            }
            if (std::is_same_v<travel_tag, PostOrderTag>) {
                PostorderIncr();
            }
            if (std::is_same_v<travel_tag, PreOrderTag>) {
                PreorderIncr();
            }

            return *this;
        }

        Iterator operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            --pos_;

            if (std::is_same_v<travel_tag, InOrderTag>) {
                InorderDecr();
            }
            if (std::is_same_v<travel_tag, PostOrderTag>) {
                PostorderDecr();
            }
            if (std::is_same_v<travel_tag, PreOrderTag>) {
                PreorderDecr();
            }

            return *this;
        }

        Iterator operator--(int) {
            auto temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator &other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }


    private:
        void PreorderIncr() {
            if (ptr_->left) {
                ptr_ = ptr_->left;

            } else if (ptr_->right) {
                ptr_ = ptr_->right;

            } else {
                while (ptr_->parent && ptr_ == ptr_->parent->right) {
                    ptr_ = ptr_->parent;
                }

                if (ptr_->parent) {
                    ptr_ = ptr_->parent->right;

                }

            }
        }

        void InorderIncr() {
            if (ptr_->right) {
                ptr_ = ptr_->right;
                while (ptr_->left) {
                    ptr_ = ptr_->left;
                }

            } else {
                auto temp = ptr_;

                while (temp->parent && temp == temp->parent->right) {
                    temp = temp->parent;
                }
                ptr_ = temp->parent;

            }
        }

        void PostorderIncr() {
            if (!ptr_->parent) {
                ptr_ = end_;
                return;
            }

            if (!ptr_->parent->right || ptr_->parent->right == ptr_) {
                ptr_ = ptr_->parent;
                return;
            }

            ptr_ = ptr_->parent->right;

            while((ptr_->left || ptr_->right) && ptr_) {
                if (ptr_->left) {
                    ptr_ = ptr_->left;
                } else {
                    ptr_ = ptr_->right;
                }
            }

        }

        void InorderDecr() {
            if (ptr_->left) {
                ptr_ = ptr_->left;
                while (ptr_->right) {
                    ptr_ = ptr_->right;
                }
            } else {
                auto temp = ptr_;
                ptr_ = ptr_->parent;
                while (ptr_ && temp == ptr_->left) {
                    temp = ptr_;
                    ptr_ = ptr_->parent;
                }
            }
        }

        void PreorderDecr() {
            if (!ptr_->parent) {
                ptr_ = ptr_->left;
                while (ptr_->right) {
                    ptr_ = ptr_->right;
                }
                return;
            }
            if (!ptr_->parent->left || ptr_->parent->left == ptr_) {
                ptr_ = ptr_->parent;
                return;
            }
            ptr_ = ptr_->parent->left;

            while (ptr_->right) {
                ptr_ = ptr_->right;
            }

        }

        void PostorderDecr() {
            if (ptr_ == end_) {
                ptr_ = end_->right;
                return;
            }

            if (ptr_->right) {
                ptr_ = ptr_->right;
                return;
            }

            while (ptr_->parent->left == ptr_ || !ptr_->parent->left) {
                ptr_ = ptr_->parent;
            }

            ptr_ = ptr_->parent->left;
        }

        void Swap(Iterator &other) noexcept {
            std::swap(ptr_, other.ptr_);
            std::swap(size_, other.size_);
            std::swap(pos_, other.pos_);
        }


        conditional_ptr ptr_;
        conditional_ptr end_;

        size_t size_;
        size_t pos_;

    };


    template<typename Key, typename IteratorTag, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
    class BSTree {
    public:

        using Alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node<Key>>;
        using allocator_traits = std::allocator_traits<Allocator>;

        using node_type = Node<Key>;
        using key_type = Key;
        using difference_type = ptrdiff_t;
        using size_type = typename allocator_traits::size_type;

        using pointer = typename Allocator::pointer;
        using reference = node_type&;
        using tag = IteratorTag;

        using iterator = Iterator<BSTree<Key, IteratorTag>, false>;
        using const_iterator = Iterator<BSTree<Key, IteratorTag>, true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using key_compare = Compare;


        BSTree() : size_(0), root_(nullptr) {
            node_type* allocated = Allocate(key_type{}, nullptr);
            end_ = allocated;

        }

        BSTree(const BSTree& other) : comp_(other.comp_), alloc_(other.alloc_), size_(other.size_) {
            root_ = Copy(other.root_);

            node_type* temp = alloc_.allocate(1);
            alloc_.construct(temp, *other.end_);

            end_ = temp;

            EditFakeNode();
            EditParents(root_);

        }

        BSTree& operator=(const BSTree& other) {
            BSTree temp(other);
            swap(temp);

            return *this;
        }

        ~BSTree() {
            Clear(root_);
            root_ = nullptr;

            Deallocate(end_);
            end_ = nullptr;
        }

        BSTree(const std::initializer_list<key_type>& list) : size_(0) {
            root_ = nullptr;

            node_type* allocated = Allocate(key_type{}, nullptr);
            end_ = allocated;

            for (key_type it : list) {
                insert(it);
            }

        }

        std::pair<iterator, bool> insert(key_type value) {
            node_type* temp = nullptr;
            bool inserted = false;

            root_ = AddNode(root_, nullptr, value, temp);

            if (temp) {
                ++size_;
                inserted = true;
                EditFakeNode();
            }

            return {iterator(temp, size_, end_), inserted};

        }

        void insert(int64_t i, int64_t j) {
            for (size_t st = i; st < j; ++st) {
                insert(st);
            }
        }

        iterator find(key_type key) {
            auto result = Find(root_, key);

            if (!result) {
                return end();
            }

            return iterator(result, size_, end_);
        }

        const_iterator find(key_type key) const {
            auto result = find(root_, key);

            if (!result) {
                return end();
            }

            return const_iterator(result, size_, end_);
        }

        iterator lower_bound(key_type key) {
            auto result = LowerBound(root_, key);

            if (!result) {
                return end();
            }

            return iterator(result, size_, end_);
        }

        const_iterator lower_bound(key_type key) const {
            auto result = LowerBound(root_, key);

            if (!result) {
                return end();
            }

            return const_iterator(result, size_, end_);
        }

        size_t erase(key_type key) {
            size_t counter = 0;

            root_ = ExtractNode(root_, key, counter);
            if (counter > 0) {
                --size_;
                EditFakeNode();
            }

            return counter;
        }

        iterator upper_bound(key_type key) {
            auto result = UpperBound(root_, key);

            if (!result) {
                return end();
            }

            return iterator(result, size_, end_);
        }

        const_iterator upper_bound(key_type key) const {
            auto result = UpperBound(root_, key);

            if (!result) {
                return end();
            }

            return const_iterator(result, size_, end_);
        }

        size_t count(key_type key) const {
            return Count(root_, key, 0);
        }

        key_type kth_largest(size_t k) {
            size_t counter = 0;

            key_type result{};
            KthLargestUtil(root_, k, counter, result);

            return result;
        }

        void extract(key_type key) {
            size_t counter = 0;

            root_ = ExtractNode(root_, key, counter);
            if (counter > 0) {
                --size_;
                EditFakeNode();
            }

        }

        void merge(BSTree& other) {
            for (auto it = other.begin(); it != other.end(); ++it) {
                insert(*it);
            }

        }

        bool contains(key_type k) {
            return find(k) != end();
        }

        friend void swap(BSTree& lhs, BSTree& rhs) {
            lhs.swap(rhs);
        }

        void swap(BSTree& temp) {
            std::swap(root_, temp.root_);
            std::swap(size_, temp.size_);
            std::swap(alloc_, temp.alloc_);
            std::swap(comp_, temp.comp_);
            std::swap(end_, temp.end_);
        }

        void clear() {
            Clear(root_);
            root_ = nullptr;

            Deallocate(end_);
            end_ = nullptr;
        }

        iterator begin() {
            return iterator(root_, true, size_, end_);

        }

        const_iterator cbegin() const {
            return const_iterator(root_, true, size_, end_);

        }

        iterator end() {
            return iterator(end_, false, size_, end_);

        }

        const_iterator end() const {
            return const_iterator(end_, false, size_, end_);

        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        bool operator==(BSTree& other) {
            if (size_ != other.size_) return false;

            auto it1 = begin();
            auto it2 = other.begin();

            for (size_t i = 0; i < size_; ++i) {
                if (*it1 != *it2) {
                    return false;
                }
                ++it1;
                ++it2;
            }

            return true;
        }

        bool operator!=(BSTree& other) {
            return !(*this == other);
        }

        key_compare key_comp() {
            return comp_;
        }

        bool empty() const {
            return root_ == nullptr;
        }

        size_type size() const {
            return size_;
        }

        size_t max_size() const {
            return std::numeric_limits<size_type>::max();
        }


    private:
        void KthLargestUtil(node_type* root, size_t k, size_t counter, key_type& result) {
            if (root == nullptr || counter >= k) {
                return;
            }

            KthLargestUtil(root->right, k, counter, result);
            counter++;

            if (counter == k) {
                result = root->data;
            }

            KthLargestUtil(root->left, k, counter, result);

        }

        void EditParents(node_type* node) {
            if (node == nullptr) {
                return;
            }

            if (node->left) {
                node->left->parent = node;
                EditParents(node->left);
            }

            if (node->right) {
                node->right->parent = node;
                EditParents(node->right);
            }

        }

        node_type* ExtractNode(node_type* root, key_type key, size_t& counter) {
            if (root == nullptr) {
                return root;

            } else if (comp_(key, root->data)) {
                root->left = ExtractNode(root->left, key, counter);

            } else if (comp_(root->data, key)) {
                root->right = ExtractNode(root->right, key, counter);

            } else {
                ++counter;

                if (!root->left) {
                    node_type* temp = root->right;
                    if (temp) {
                        temp->parent = root->parent;
                    }

                    Deallocate(root);

                    return temp;
                } else if (!root->right) {
                    node_type* temp = root->left;

                    if (temp) {
                        temp->parent = root->parent;
                    }

                    Deallocate(root);

                    return temp;
                }

                node_type* temp = LeftNode(root->right);
                root->data = temp->data;
                root->right = ExtractNode(root->right, temp->data, counter);
            }

            return root;
        }


        node_type* Allocate(key_type value, node_type* parent) {
            node_type* allocated = alloc_.allocate(1);
            alloc_.construct(allocated, node_type(value, parent));

            return allocated;
        }

        size_t Count(node_type* root, key_type key, size_t count = 0) const {
            if (root == nullptr) {
                return count;
            }

            if (comp_(key, root->data)) {
                return Count(root->left, key, count);

            } else if (comp_(root->data, key)) {
                return Count(root->right, key, count);

            } else {
                return Count(root->right, key, count + 1);
            }
        }

        node_type* LowerBound(node_type* root, key_type value) const {
            node_type* result = nullptr;

            while (root != nullptr) {
                if (comp_(root->data, value)) {
                    root = root->right;
                } else if (comp_(value, root->data)) {
                    result = root;
                    root = root->left;
                } else {
                    return root;
                }
            }
            return result;

        }

        node_type* UpperBound(node_type* root, key_type value) const {
            node_type* result = nullptr;

            while (root != nullptr) {
                if (comp_(value, root->data)) {
                    result = root;
                    root = root->left;

                } else {
                    root = root->right;
                }
            }

            return result;

        }

        void Deallocate(node_type* ptr) {
            alloc_.destroy(ptr);
            alloc_.deallocate(ptr, 1);
        }

        node_type* LeftNode(node_type* root) {
            while (root->left) {
                root = root->left;
            }
            return root;
        }

        node_type* RightNode(node_type* root) {
            while (root->right) {
                root = root->right;
            }

            return root;
        }

        node_type* Find(node_type* node, key_type key) const {
            if (!node || key == node->data) {
                return node;

            }
            if (comp_(key, node->data)) {
                return Find(node->left, key);

            } else {
                return Find(node->right, key);
            }
        }

        node_type* Copy(node_type* node) {
            if (node == nullptr) {
                return nullptr;
            }

            node_type* temp = alloc_.allocate(1);
            alloc_.construct(temp, *node);

            temp->left = Copy(node->left);
            temp->right = Copy(node->right);

            return temp;
        }

        void Clear(node_type* node) {
            if (!node) {
                return;
            }

            Clear(node->right);
            Clear(node->left);
            Deallocate(node);
        }

        node_type* AddNode(node_type* node, node_type* parent, key_type value, node_type*& cur) {
            if (node == nullptr) {
                cur = Allocate(value, parent);
                return cur;
            }

            if (comp_(value, node->data)) {
                node->left = AddNode(node->left, node, value, cur);
            } else if (comp_(node->data, value)){
                node->right = AddNode(node->right, node, value, cur);
            }

            return node;

        }

        void LowestRightNode(node_type* root, size_t cur_lvl, size_t& max_lvl, node_type*& result, bool& from_right) {
            if (!root) {
                return;
            }

            LowestRightNode(root->left, cur_lvl + 1, max_lvl, result, from_right);

            if (cur_lvl > max_lvl || (cur_lvl == max_lvl && !from_right)) {
                result = root;
                max_lvl = cur_lvl;
                from_right = false;
            }

            if (root->right && cur_lvl == max_lvl) {
                result = root->right;
                from_right = true;
            }

            LowestRightNode(root->right, cur_lvl + 1, max_lvl, result, from_right);
        }

        void EditFakeNode() {
            if (std::is_same_v<tag, InOrderTag>) {
                node_type* temp = RightNode(root_);
                end_->parent = temp;
            }

            if (std::is_same_v<tag, PreOrderTag>) {

                node_type* result = nullptr;
                size_t cur_lvl = 0;
                size_t max_lvl = 0;
                bool from_right = false;

                LowestRightNode(root_, cur_lvl, max_lvl, result, from_right);
                end_->parent = result;
            }

            if (std::is_same_v<tag, PostOrderTag>) {
                end_->right = root_;
            }
        }

        Alloc alloc_;
        Compare comp_;

        node_type* root_;
        node_type* end_;

        size_type size_;
    };


    template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
    class PreOrderBST : public BSTree<Key, PreOrderTag, Compare, Allocator> {
        //This entry is used to pass the present signature of the base class constructors into the derived class
        using BSTree<Key, PreOrderTag, Compare, Allocator>::BSTree;
    };

    template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
    class InOrderBST : public BSTree<Key, InOrderTag, Compare, Allocator> {
        using BSTree<Key, InOrderTag, Compare, Allocator>::BSTree;
    };

    template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
    class PostOrderBST : public BSTree<Key, PostOrderTag, Compare, Allocator> {
        using BSTree<Key, PostOrderTag, Compare, Allocator>::BSTree;
    };

} //namespace bst end