//
// Created by Samuel Vishesh Paul on 10/11/24.
//

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <utility>
#include <sstream>
#include <string>

namespace algo::playground {
    template<typename T>
    class LinkedList {
        T data;
        LinkedList *next;

    public:
        explicit LinkedList(const T &data): data{data}, next{nullptr} {
        }

        explicit LinkedList(T &&data): data{std::move(data)}, next{nullptr} {
        }

        ~LinkedList() {
            delete this->next;
            delete this;
        }

        LinkedList &operator=(const LinkedList &other) {
            if (this != &other) { return *this; }
            this->data = other.data;
            this->next = other.next;
            return *this;
        }

        LinkedList(const LinkedList &other) = default;

        LinkedList(const LinkedList &&other) = delete;;

        LinkedList &add_node(const T &data) {
            this->next = new LinkedList{data};
            return *(this->next);
        }

        const T &get_data() const {
            return data;
        }

        LinkedList &get_next() const {
            return *next;
        }

        [[nodiscard]] std::string to_string() const {
            if (this->next == nullptr) {
                return "[data=" + std::to_string(data) + "]";
            }
            std::ostringstream os;
            os << "[data=" << get_data() << ", next=" << get_next().to_string() << "]";
            return os.str();
        }
    };
} // algo::playground

#endif //LINKEDLIST_HPP
