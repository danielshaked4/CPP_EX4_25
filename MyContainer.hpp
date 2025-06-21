// Email: sone0149@gmail.com


#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace ariel {

/**
 * @brief A generic container class that supports multiple iteration orders
 * 
 * This container stores elements and provides various ways to iterate through them:
 * - Default/Normal order: Elements in insertion order
 * - Ascending order: Elements sorted in ascending order
 * - Descending order: Elements sorted in descending order
 * - Side cross order: Alternating between smallest and largest remaining elements
 * - Reverse order: Elements in reverse insertion order
 * - Middle out order: Starting from middle, alternating outward
 * 
 * @tparam T The type of elements stored in the container (default: int)
 */
template <typename T = int>
class MyContainer {
private:
    std::vector<T> elements;  ///< Internal storage for container elements

public:
    // Forward declarations of iterator classes
    class AscendingIterator;
    class DescendingIterator;
    class SideCrossIterator;
    class ReverseIterator;
    class OrderIterator;
    class MiddleOutIterator;

    /**
     * @brief Default constructor - creates an empty container
     */
    MyContainer() = default;

    /**
     * @brief Add an element to the container
     * @param element The element to add
     */
    void add(const T& element) {
        elements.push_back(element);
    }


    /**
     * @brief Remove all instances of an element from the container
     * @param element The element to remove
     * @throws std::runtime_error if the element is not found
     */
    void remove(const T& element) {
        size_t initial_size = elements.size();
        elements.erase(
            std::remove(elements.begin(), elements.end(), element),
            elements.end()
        );
        
        if (elements.size() == initial_size) {
            throw std::runtime_error("Element not found in container");
        }
    }

    /**
     * @brief Get the number of elements in the container
     * @return The size of the container
     */
    size_t size() const {
        return elements.size();
    }

    /**
     * @brief Output stream operator for printing the container
     * @param os The output stream
     * @param container The container to print
     * @return The output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const MyContainer& container) {
        os << "[";
        for (size_t i = 0; i < container.elements.size(); ++i) {
            os << container.elements[i];
            if (i < container.elements.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    /**
     * @brief Get iterator to beginning (default: insertion order)
     * @return Iterator pointing to the first element
     */
    OrderIterator begin() { 
        return OrderIterator(*this); }
    
    /**
     * @brief Get iterator to end (default: insertion order)
     * @return Iterator pointing past the last element
     */
    OrderIterator end() {
        return OrderIterator(*this, true); }

    // Specialized iterator methods
    
    /**
     * @brief Get iterator for ascending order traversal
     * @return Iterator to beginning of ascending sequence
     */
    AscendingIterator begin_ascending_order() { 
        return AscendingIterator(*this); }
    
    /**
     * @brief Get end iterator for ascending order traversal
     * @return Iterator to end of ascending sequence
     */
    AscendingIterator end_ascending_order() { 
        return AscendingIterator(*this, true); }

    /**
     * @brief Get iterator for descending order traversal
     * @return Iterator to beginning of descending sequence
     */
    DescendingIterator begin_descending_order() { 
        return DescendingIterator(*this); }
    
    /**
     * @brief Get end iterator for descending order traversal
     * @return Iterator to end of descending sequence
     */
    DescendingIterator end_descending_order() { 
        return DescendingIterator(*this, true); }

    /**
     * @brief Get iterator for side cross order traversal
     * @return Iterator to beginning of side cross sequence
     */
    SideCrossIterator begin_side_cross_order() { 
        return SideCrossIterator(*this); }
    
    /**
     * @brief Get end iterator for side cross order traversal
     * @return Iterator to end of side cross sequence
     */
    SideCrossIterator end_side_cross_order() { 
        return SideCrossIterator(*this, true); }

    /**
     * @brief Get iterator for reverse order traversal
     * @return Iterator to beginning of reverse sequence
     */
    ReverseIterator begin_reverse_order() { 
        return ReverseIterator(*this); }
    
    /**
     * @brief Get end iterator for reverse order traversal
     * @return Iterator to end of reverse sequence
     */
    ReverseIterator end_reverse_order() { 
        return ReverseIterator(*this, true); }

    /**
     * @brief Get iterator for normal order traversal (same as begin())
     * @return Iterator to beginning of normal sequence
     */
    OrderIterator begin_order() { 
        return OrderIterator(*this); }
    
    /**
     * @brief Get end iterator for normal order traversal (same as end())
     * @return Iterator to end of normal sequence
     */
    OrderIterator end_order() { 
        return OrderIterator(*this, true); }

    /**
     * @brief Get iterator for middle-out order traversal
     * @return Iterator to beginning of middle-out sequence
     */
    MiddleOutIterator begin_middle_out_order() { 
        return MiddleOutIterator(*this); }
    
    /**
     * @brief Get end iterator for middle-out order traversal
     * @return Iterator to end of middle-out sequence
     */
    MiddleOutIterator end_middle_out_order() { 
        return MiddleOutIterator(*this, true); }

    /**
     * @brief Base iterator class for all iteration strategies
     * 
     * Provides common functionality for all iterator types.
     * Stores a copy of elements in the desired order.
     */
    class BaseIterator {
    protected:
        std::vector<T> sorted_elements;  ///< Elements arranged in iteration order
        size_t index;                    ///< Current position in iteration

    public:
        // Iterator traits for STL compatibility
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Construct an iterator
         * @param elems The elements to iterate over
         * @param idx Starting index (0 for begin, size for end)
         */
        BaseIterator(const std::vector<T>& elems, size_t idx = 0) 
            : sorted_elements(elems), index(idx) {}

        /**
         * @brief Dereference operator
         * @return Reference to current element
         */
        T& operator*() { return sorted_elements[index]; }
        
        /**
         * @brief Arrow operator
         * @return Pointer to current element
         */
        T* operator->() { return &sorted_elements[index]; }

        /**
         * @brief Equality comparison
         * @param other Iterator to compare with
         * @return true if iterators point to same position
         */
        bool operator==(const BaseIterator& other) const {
            return index == other.index;
        }

        /**
         * @brief Inequality comparison
         * @param other Iterator to compare with
         * @return true if iterators point to different positions
         */
        bool operator!=(const BaseIterator& other) const {
            return !(*this == other);
        }
    };

    /**
     * @brief Iterator for ascending order traversal
     * 
     * Iterates through elements in sorted ascending order
     */
    class AscendingIterator : public BaseIterator {
    public:
        /**
         * @brief Construct ascending iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        AscendingIterator(MyContainer& container, bool end = false) 
            : BaseIterator(container.elements, end ? container.elements.size() : 0) {
            std::sort(this->sorted_elements.begin(), this->sorted_elements.end());
        }

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        AscendingIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        AscendingIterator operator++(int) {
            AscendingIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /**
     * @brief Iterator for descending order traversal
     * 
     * Iterates through elements in sorted descending order
     */
    class DescendingIterator : public BaseIterator {
    public:
        /**
         * @brief Construct descending iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        DescendingIterator(MyContainer& container, bool end = false)
            : BaseIterator(container.elements, end ? container.elements.size() : 0) {
            std::sort(this->sorted_elements.begin(), this->sorted_elements.end(), std::greater<T>());
        }

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        DescendingIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        DescendingIterator operator++(int) {
            DescendingIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /**
     * @brief Iterator for side cross order traversal
     * 
     * Iterates by alternating between smallest and largest remaining elements.
     * Example: [1,2,3,4,5] -> [1,5,2,4,3]
     */
    class SideCrossIterator : public BaseIterator {
    public:
        /**
         * @brief Construct side cross iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        SideCrossIterator(MyContainer& container, bool end = false)
            : BaseIterator(std::vector<T>(), end ? container.elements.size() : 0) {
            if (!container.elements.empty()) {
                std::vector<T> temp = container.elements;
                std::sort(temp.begin(), temp.end());
                
                this->sorted_elements.clear();
                int left = 0, right = temp.size() - 1;
                
                while (left <= right) {
                    this->sorted_elements.push_back(temp[left++]);
                    if (left <= right) {
                        this->sorted_elements.push_back(temp[right--]);
                    }
                }
            }
        }

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        SideCrossIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        SideCrossIterator operator++(int) {
            SideCrossIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /**
     * @brief Iterator for reverse order traversal
     * 
     * Iterates through elements in reverse insertion order
     */
    class ReverseIterator : public BaseIterator {
    public:
        /**
         * @brief Construct reverse iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        ReverseIterator(MyContainer& container, bool end = false)
            : BaseIterator(container.elements, end ? container.elements.size() : 0) {
            std::reverse(this->sorted_elements.begin(), this->sorted_elements.end());
        }

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        ReverseIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        ReverseIterator operator++(int) {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /**
     * @brief Iterator for normal order traversal
     * 
     * Iterates through elements in insertion order
     */
    class OrderIterator : public BaseIterator {
    public:
        /**
         * @brief Construct normal order iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        OrderIterator(MyContainer& container, bool end = false)
            : BaseIterator(container.elements, end ? container.elements.size() : 0) {}

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        OrderIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        OrderIterator operator++(int) {
            OrderIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /**
     * @brief Iterator for middle-out order traversal
     * 
     * Iterates starting from the middle element, alternating outward.
     * Example: [1,2,3,4,5] -> [3,2,4,1,5]
     */
    class MiddleOutIterator : public BaseIterator {
    public:
        /**
         * @brief Construct middle-out iterator
         * @param container The container to iterate over
         * @param end If true, creates an end iterator
         */
        MiddleOutIterator(MyContainer& container, bool end = false)
            : BaseIterator(std::vector<T>(), end ? container.elements.size() : 0) {
            if (!container.elements.empty()) {
                std::vector<T> temp = container.elements;
                this->sorted_elements.clear();
                
                int n = temp.size();
                int middle = n / 2;
                this->sorted_elements.push_back(temp[middle]);
                
                int left = middle - 1;
                int right = middle + 1;
                
                while (left >= 0 || right < n) {
                    if (left >= 0) {
                        this->sorted_elements.push_back(temp[left--]);
                    }
                    if (right < n) {
                        this->sorted_elements.push_back(temp[right++]);
                    }
                }
            }
        }

        /**
         * @brief Pre-increment operator
         * @return Reference to this iterator after increment
         */
        MiddleOutIterator& operator++() {
            ++this->index;
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @return Copy of iterator before increment
         */
        MiddleOutIterator operator++(int) {
            MiddleOutIterator temp = *this;
            ++(*this);
            return temp;
        }
    };
};

} // namespace ariel

#endif // MYCONTAINER_HPP