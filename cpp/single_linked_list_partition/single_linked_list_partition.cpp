#include <iostream>
#include <vector>

struct Node {
    explicit Node(int value, Node* next)
        : next_(next)
        , value_(value)
    {
        std::cerr << "Create list Node: " << value_ << std::endl;
    }

    ~Node() {
        std::cerr << "Remove list Node: " << value_ << std::endl;
    }

    Node* next_;
    int value_;
};

struct PartitionedList {
    Node* head_ = nullptr;
    Node* afterPivot_ = nullptr;
};

PartitionedList listPartition(Node* pt, int pivot) {
    PartitionedList ret;
    Node* left = nullptr;
    Node* right = nullptr;

    while (pt != nullptr) {
        std::cerr << "Compare: " << pt->value_ << std::endl;
        if (pt->value_ < pivot) {
            if (left == nullptr) {
                ret.head_ = pt;
            } else {
                left->next_ = pt;
            }
            left = pt;
        } else {
            if (right == nullptr) {
                ret.afterPivot_ = pt;
            } else {
                right->next_ = pt;
            }
            right = pt;
        }
        pt = pt->next_;
    }

    if (left != nullptr) {
        left->next_ = ret.afterPivot_;
    } else {
        ret.head_ = ret.afterPivot_;
    }
    if (right != nullptr) {
        right->next_ = nullptr;
    }

    return ret;
}

void partitionTest(const std::vector<int>& cont, int pivot) {
    Node* head = nullptr;
    for (const auto& number : cont) {
        head = new Node{number, head};
    }
    auto part = listPartition(head, pivot);
    std::cout << "Pivot: " << pivot << "\n";
    std::cout << "Before pivot:\n";
    for (auto pt = part.head_; pt != part.afterPivot_; pt = pt->next_) {
        std::cout << "  " << pt->value_ << "\n";
    }
    std::cout << "After pivot:\n";
    for (auto pt = part.afterPivot_; pt != nullptr; pt = pt->next_) {
        std::cout << "  " << pt->value_ << "\n";
    }

    auto pt = part.head_;
    while (pt != nullptr) {
        auto next = pt->next_;
        delete pt;
        pt = next;
    }
}

int main() {
    partitionTest({0, 0}, 0);
    partitionTest({1, -10, 10, -1, 0}, 0);
    partitionTest({1, 2, -5, -6, 0}, -5);
    partitionTest({1, 2, 3, 4, 5}, 2);
}
