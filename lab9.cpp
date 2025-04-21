#include <iostream>
#include <limits>

template<typename T>
class GenericArray {
private:
    T* data;      // Pointer to the dynamic array
    int length;   // Number of elements in the array

public:
    // Constructor to initialize the array and length
    GenericArray() : data(nullptr), length(0) {}

    // Destructor to clean up memory
    ~GenericArray() {
        delete[] data;
    }

    // Add an element to the end of the array
    void addElement(T val) {
        // Allocate new memory for the array with one extra element
        T* newData = new T[length + 1];

        // Copy the old data to the new array
        for (int i = 0; i < length; ++i) {
            newData[i] = data[i];
        }

        // Add the new element
        newData[length] = val;

        // Free the old array and point to the new array
        delete[] data;
        data = newData;
        ++length;
    }

    // Get the element at the specified index
    T at(int index) const {
        if (index < 0 || index >= length) {
            std::cerr << "Index out of bounds.\n";
            return T();  // Return default value of T
        }
        return data[index];
    }

    // Return the size of the array
    int size() const {
        return length;
    }

    // Calculate and return the sum of the array
    T sum() const {
        T total = 0;
        for (int i = 0; i < length; ++i) {
            total += data[i];
        }
        return total;
    }

    // Find and return the maximum value in the array
    T max() const {
        if (length == 0) return T();  // Return default value if empty
        T maxVal = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] > maxVal) maxVal = data[i];
        }
        return maxVal;
    }

    // Find and return the minimum value in the array
    T min() const {
        if (length == 0) return T();  // Return default value if empty
        T minVal = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] < minVal) minVal = data[i];
        }
        return minVal;
    }

    // Get a slice of the array from index 'begin' to 'end'
    T* slice(int begin, int end) const {
        // Check that the range is valid
        if (begin < 0 || end >= length || begin > end) {
            std::cerr << "Invalid slice range.\n";
            return nullptr;
        }

        int newSize = end - begin + 1;
        T* sliced = new T[newSize];

        // Copy the elements to the new array
        for (int i = 0; i < newSize; ++i) {
            sliced[i] = data[begin + i];
        }

        return sliced;
    }
};

int main() {
    // Create an array of integers and add some elements
    GenericArray<int> intArray;
    for (int i = 0; i < 12; ++i) {
        intArray.addElement(i * 2);  // Adds: 0, 2, 4, ..., 22
    }

    // Display the size of the array
    std::cout << "Size of the array: " << intArray.size() << std::endl;

    // Calculate and display the sum of the array
    std::cout << "Sum of the array: " << intArray.sum() << std::endl;

    // Find and display the maximum and minimum values in the array
    std::cout << "Max value: " << intArray.max() << std::endl;
    std::cout << "Min value: " << intArray.min() << std::endl;

    // Get a slice of the array from index 5 to 10 and print it
    int* slicedArray = intArray.slice(5, 10);
    if (slicedArray) {
        std::cout << "Sliced array from index 5 to 10: ";
        for (int i = 0; i <= 10 - 5; ++i) {
            std::cout << slicedArray[i] << " ";
        }
        std::cout << std::endl;

        // Don't forget to free the memory for the sliced array!
        delete[] slicedArray;
    }

    return 0;
}
