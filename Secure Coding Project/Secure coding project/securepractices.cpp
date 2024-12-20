#include <iostream>

void safeDelete() {
    int* ptr = new int(42); // Dynamically allocate memory
    std::cout << "Value before deletion: " << *ptr << std::endl;

    delete ptr;     // Deallocate memory
    ptr = nullptr;  // Set pointer to nullptr to avoid dangling

    if (ptr == nullptr) {
        std::cout << "Pointer safely set to nullptr after deletion.\n";
    }
}

void avoidDoubleDeletion() {
    int* ptr = new int(100); // Dynamically allocate memory
    delete ptr;              // First deletion

    if (ptr != nullptr) { // Check before deleting again
        delete ptr;
        ptr = nullptr;
    } else {
        std::cout << "Pointer is already deleted or null. Avoiding double deletion.\n";
    }
}

void boundsAndNullChecks() {
    int* arr = new int[3]{10, 20, 30}; // Dynamically allocate an array

    // Null pointer check
    int* nullPtr = nullptr;
    if (nullPtr) {
        std::cout << "Null pointer check: " << *nullPtr << std::endl;
    } else {
        std::cout << "Null pointer is not valid for dereferencing.\n";
    }

    // Bounds check for the array
    for (int i = 0; i < 3; ++i) {
        std::cout << "Array[" << i << "] = " << arr[i] << std::endl;
    }

    delete[] arr; // Deallocate the array
    arr = nullptr;
    std::cout << "Array memory safely deallocated.\n";
}

int main() {
    std::cout << "=== Safe Delete ===\n";
    safeDelete();

    std::cout << "\n=== Avoid Double Deletion ===\n";
    avoidDoubleDeletion();

    std::cout << "\n=== Bounds and Null Checks ===\n";
    boundsAndNullChecks();

    return 0;
}