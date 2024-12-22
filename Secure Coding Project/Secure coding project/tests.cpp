#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

    void safeDelete(Node*& node) {
        if (node) {
            delete node;
            node = nullptr;
        }
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    bool deleteNode(int value) {
        if (!head) return false;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            safeDelete(temp);
            return true;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            safeDelete(temp);
            return true;
        }
        return false;
    }

    int getNodeData(int index) const {
        Node* temp = head;
        int count = 0;

        while (temp) {
            if (count == index) {
                return temp->data;
            }
            count++;
            temp = temp->next;
        }

        throw std::out_of_range("Index out of bounds");
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            safeDelete(temp);
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

struct TestCase {
    std::string operation;
    std::string description;
    bool result;
};

int main() {
    LinkedList list;
    std::vector<TestCase> testResults;

    try {
        // Test 1: Insert nodes
        list.insert(10);
        list.insert(20);
        list.insert(30);
        testResults.push_back({"Insert", "Insert nodes into the linked list", true});

        // Test 2: Delete first node
        testResults.push_back({"Delete First Node", "Delete head safely", list.deleteNode(10)});

        // Test 3: Delete middle node
        testResults.push_back({"Delete Middle Node", "Delete a middle node safely", list.deleteNode(20)});

        // Test 4: Delete last node
        testResults.push_back({"Delete Last Node", "Delete the last node safely", list.deleteNode(30)});

        // Test 5: Delete non-existent node
        testResults.push_back({"Delete Non-existent Node", "Attempt to delete a node not in the list", !list.deleteNode(40)});

        // Test 6: Clear empty list
        list.clear();
        testResults.push_back({"Clear Empty List", "Clear an already empty list", list.isEmpty()});

        // Test 7: Access valid index
        list.insert(50);
        list.insert(60);
        testResults.push_back({"Access Valid Index", "Access valid index 1", list.getNodeData(1) == 60});

        // Test 8: Access invalid index
        try {
            list.getNodeData(5);
            testResults.push_back({"Access Invalid Index", "Attempt to access out-of-bounds index", false});
        } catch (...) {
            testResults.push_back({"Access Invalid Index", "Attempt to access out-of-bounds index", true});
        }

        // Test 9: Clear list with nodes
        list.clear();
        testResults.push_back({"Clear List", "Clear list with multiple nodes", list.isEmpty()});

        // Test 10: Insert after clear
        list.insert(70);
        testResults.push_back({"Insert After Clear", "Insert nodes after clearing the list", list.getNodeData(0) == 70});

        // Test 11: Delete only node
        testResults.push_back({"Delete Only Node", "Delete the only node in the list", list.deleteNode(70)});

        // Test 12: Reinsert nodes after clear
        list.insert(80);
        list.insert(90);
        testResults.push_back({"Reinsert Nodes", "Reinsert nodes after clearing the list", list.getNodeData(1) == 90});

        // Test 13: Check if empty after deletion
        list.clear();
        testResults.push_back({"Check Empty", "Verify list is empty after clearing", list.isEmpty()});

        // Test 14: Insert and delete multiple times
        list.insert(100);
        list.deleteNode(100);
        testResults.push_back({"Multiple Insert/Delete", "Insert and delete the same node", list.isEmpty()});

        // Test 15: Access head node
        list.insert(110);
        testResults.push_back({"Access Head Node", "Access the first node", list.getNodeData(0) == 110});

        // Test 16: Insert at tail
        list.insert(120);
        testResults.push_back({"Insert at Tail", "Insert a node at the end", list.getNodeData(1) == 120});

        // Test 17: Delete tail node
        testResults.push_back({"Delete Tail Node", "Delete the last node in the list", list.deleteNode(120)});

        // Test 18: Safe clear of large list
        list.insert(130);
        list.insert(140);
        list.insert(150);
        list.clear();
        testResults.push_back({"Safe Clear", "Safely clear a large list", list.isEmpty()});

        // Test 19: Attempt delete on empty list
        testResults.push_back({"Delete on Empty List", "Attempt to delete from an empty list", !list.deleteNode(160)});

        // Test 20: Single node insertion
        list.insert(170);
        testResults.push_back({"Single Node Insertion", "Insert and access a single node", list.getNodeData(0) == 170});

    } catch (...) {
        std::cerr << "An unexpected error occurred during testing.\n";
    }

    // Print results
    std::cout << std::left << std::setw(5) << "Test"
              << std::setw(30) << "Operation"
              << std::setw(50) << "Description"
              << "Result\n";
    std::cout << std::string(90, '-') << "\n";

    int testIndex = 1;
    for (const auto& test : testResults) {
        std::cout << std::setw(5) << testIndex++
                  << std::setw(30) << test.operation
                  << std::setw(50) << test.description
                  << (test.result ? "Success" : "Failure") << "\n";
    }

    return 0;
}
