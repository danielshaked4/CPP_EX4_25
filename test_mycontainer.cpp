// Email: sone0149@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <string>
#include <vector>
#include <algorithm>

using namespace ariel;

TEST_CASE("Basic container operations") {
    SUBCASE("Default constructor creates empty container") {
        MyContainer<int> container;
        CHECK(container.size() == 0);
    }

    SUBCASE("Adding single element") {
        MyContainer<int> container;
        container.add(5);
        CHECK(container.size() == 1);
    }

    SUBCASE("Adding multiple elements") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        CHECK(container.size() == 3);
    }


    SUBCASE("Removing existing element") {
        MyContainer<int> container;
        container.add(5);
        container.add(10);
        container.remove(5);
        CHECK(container.size() == 1);
    }

    SUBCASE("Removing non-existent element throws exception") {
        MyContainer<int> container;
        container.add(5);
        CHECK_THROWS_AS(container.remove(10), std::runtime_error);
    }

    SUBCASE("Removing all instances of duplicate elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(10);
        container.add(5);
        container.add(5);
        CHECK(container.size() == 4);
        container.remove(5);
        CHECK(container.size() == 1);
    }
}

TEST_CASE("Container with different types") {
    SUBCASE("Container with doubles") {
        MyContainer<double> container;
        container.add(3.14);
        container.add(2.71);
        container.add(1.41);
        CHECK(container.size() == 3);
    }

    SUBCASE("Container with strings") {
        MyContainer<std::string> container;
        container.add("hello");
        container.add("world");
        container.add("test");
        CHECK(container.size() == 3);
        container.remove("world");
        CHECK(container.size() == 2);
    }

    SUBCASE("Container with chars") {
        MyContainer<char> container;
        container.add('a');
        container.add('b');
        container.add('c');
        CHECK(container.size() == 3);
    }
}

TEST_CASE("Ascending order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct ascending order") {
        std::vector<int> expected = {1, 2, 6, 7, 15};
        std::vector<int> actual;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Iterator post-increment") {
        auto it = container.begin_ascending_order();
        int first = *it++;
        int second = *it;
        CHECK(first == 1);
        CHECK(second == 2);
    }

    SUBCASE("Empty container ascending iterator") {
        MyContainer<int> empty;
        auto begin = empty.begin_ascending_order();
        auto end = empty.end_ascending_order();
        CHECK(begin == end);
    }
}

TEST_CASE("Descending order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct descending order") {
        std::vector<int> expected = {15, 7, 6, 2, 1};
        std::vector<int> actual;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Single element descending") {
        MyContainer<int> single;
        single.add(42);
        auto it = single.begin_descending_order();
        CHECK(*it == 42);
    }
}

TEST_CASE("Side cross order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct side cross order") {
        std::vector<int> expected = {1, 15, 2, 7, 6};
        std::vector<int> actual;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Even number of elements side cross") {
        MyContainer<int> even;
        even.add(4);
        even.add(1);
        even.add(3);
        even.add(2);
        std::vector<int> actual;
        for (auto it = even.begin_side_cross_order(); it != even.end_side_cross_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual.size() == 4);
        CHECK(actual[0] == 1);
        CHECK(actual[1] == 4);
    }
}

TEST_CASE("Reverse order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct reverse order") {
        std::vector<int> expected = {2, 1, 6, 15, 7};
        std::vector<int> actual;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Reverse of reverse is original") {
        std::vector<int> original;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            original.push_back(*it);
        }
        std::vector<int> reverse_reverse;
        MyContainer<int> temp;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            temp.add(*it);
        }
        for (auto it = temp.begin_reverse_order(); it != temp.end_reverse_order(); ++it) {
            reverse_reverse.push_back(*it);
        }
        CHECK(original == reverse_reverse);
    }
}

TEST_CASE("Normal order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct normal order") {
        std::vector<int> expected = {7, 15, 6, 1, 2};
        std::vector<int> actual;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Order preserved after operations") {
        MyContainer<int> cont;
        cont.add(1);
        cont.add(2);
        cont.add(3);
        std::vector<int> before;
        for (auto it = cont.begin_order(); it != cont.end_order(); ++it) {
            before.push_back(*it);
        }
        // Do some operation that shouldn't change order
        cont.size();
        std::vector<int> after;
        for (auto it = cont.begin_order(); it != cont.end_order(); ++it) {
            after.push_back(*it);
        }
        CHECK(before == after);
    }
}

TEST_CASE("Middle out order iterator") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    SUBCASE("Correct middle out order - odd size") {
        std::vector<int> expected = {6, 15, 1, 7, 2};
        std::vector<int> actual;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Middle out order - even size") {
        MyContainer<int> even;
        even.add(1);
        even.add(2);
        even.add(3);
        even.add(4);
        std::vector<int> actual;
        for (auto it = even.begin_middle_out_order(); it != even.end_middle_out_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual.size() == 4);
        // Middle element should be at index 1 or 2
        CHECK((actual[0] == 3 || actual[0] == 2));
    }

    SUBCASE("Single element middle out") {
        MyContainer<int> single;
        single.add(42);
        auto it = single.begin_middle_out_order();
        CHECK(*it == 42);
    }
}

TEST_CASE("Iterator edge cases") {
    SUBCASE("Empty container iterators") {
        MyContainer<int> empty;
        CHECK(empty.begin_ascending_order() == empty.end_ascending_order());
        CHECK(empty.begin_descending_order() == empty.end_descending_order());
        CHECK(empty.begin_side_cross_order() == empty.end_side_cross_order());
        CHECK(empty.begin_reverse_order() == empty.end_reverse_order());
        CHECK(empty.begin_order() == empty.end_order());
        CHECK(empty.begin_middle_out_order() == empty.end_middle_out_order());
    }

    SUBCASE("Iterator inequality") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        auto it1 = container.begin_order();
        auto it2 = container.begin_order();
        CHECK(it1 == it2);
        ++it1;
        CHECK(it1 != it2);
    }

    SUBCASE("Dereferencing iterator") {
        MyContainer<int> container;
        container.add(42);
        auto it = container.begin_order();
        CHECK(*it == 42);
        *it = 43;  // Should be able to modify through iterator
        CHECK(*it == 43);
    }

    SUBCASE("Arrow operator") {
        struct TestStruct {
            int value;
            TestStruct(int v) : value(v) {}
            bool operator<(const TestStruct& other) const { return value < other.value; }
            bool operator==(const TestStruct& other) const { return value == other.value; }
        };
        
        MyContainer<TestStruct> container;
        container.add(TestStruct(42));
        auto it = container.begin_order();
        CHECK(it->value == 42);
    }
}

TEST_CASE("Complex scenarios") {
    SUBCASE("Multiple adds and removes") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        container.add(2);
        container.add(4);
        CHECK(container.size() == 5);
        container.remove(2);
        CHECK(container.size() == 3);
        
        std::vector<int> remaining;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            remaining.push_back(*it);
        }
        // Should not contain 2
        CHECK(std::find(remaining.begin(), remaining.end(), 2) == remaining.end());
    }

    SUBCASE("Large container performance") {
        MyContainer<int> large;
        const int SIZE = 1000;
        for (int i = 0; i < SIZE; ++i) {
            large.add(i);
        }
        CHECK(large.size() == SIZE);
        
        // Check ascending order is correct
        int expected = 0;
        for (auto it = large.begin_ascending_order(); it != large.end_ascending_order(); ++it) {
            CHECK(*it == expected++);
        }
    }

    SUBCASE("Container with negative numbers") {
        MyContainer<int> container;
        container.add(-5);
        container.add(3);
        container.add(-2);
        container.add(0);
        container.add(-10);
        
        std::vector<int> ascending;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            ascending.push_back(*it);
        }
        CHECK(ascending == std::vector<int>{-10, -5, -2, 0, 3});
    }

    SUBCASE("String container alphabetical order") {
        MyContainer<std::string> strings;
        strings.add("zebra");
        strings.add("apple");
        strings.add("banana");
        strings.add("cherry");
        
        std::vector<std::string> alphabetical;
        for (auto it = strings.begin_ascending_order(); it != strings.end_ascending_order(); ++it) {
            alphabetical.push_back(*it);
        }
        CHECK(alphabetical[0] == "apple");
        CHECK(alphabetical[3] == "zebra");
    }
}