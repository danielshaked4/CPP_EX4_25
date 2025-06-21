// Email: sone0149@gmail.com


#include <iostream>
#include <string>
#include "MyContainer.hpp"

using namespace ariel;
using namespace std;

int main() {
    // Original demo
    cout << "=== Basic Integer Container ===" << endl;
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    cout << "Size of container: " << container.size() << endl;
    cout << "Container contents: " << container << endl << endl;

    cout << "Ascending order:   ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "Descending order:  ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "Side cross order:  ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "Reverse order:     ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "Normal order:      ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "Middle out order:  ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    // Additional demos
    cout << "\n=== String Container ===" << endl;
    MyContainer<string> words;
    words.add("dog");
    words.add("cat");
    words.add("bird");
    words.add("fish");
    
    cout << "Words: " << words << endl;
    cout << "Alphabetical: ";
    for (auto it = words.begin_ascending_order(); it != words.end_ascending_order(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;

    cout << "\n=== Remove Demo ===" << endl;
    MyContainer<int> numbers;
    numbers.add(10);
    numbers.add(20);
    numbers.add(10);
    numbers.add(30);
    
    cout << "Before remove: " << numbers << " (size: " << numbers.size() << ")" << endl;
    numbers.remove(10);
    cout << "After remove 10: " << numbers << " (size: " << numbers.size() << ")" << endl;

    // Try removing non-existent element
    try {
        numbers.remove(99);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\n=== Empty Container ===" << endl;
    MyContainer<int> empty;
    cout << "Empty container size: " << empty.size() << endl;
    cout << "Empty container: " << empty << endl;

    return 0;
}