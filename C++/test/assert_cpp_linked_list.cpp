#include <cassert>
#include <cstdlib>
#include <iostream>

#include <LinkedList.hpp>

int main() {
    using algo::playground::LinkedList;
    auto ll = LinkedList(10);
    auto &leaf = ll;
    for (int i = 9; i > 0; i--) {
        leaf = ll.add_node(i);
    }
    std::cout << "ll: " << ll.to_string() << std::endl;
    std::cout.flush();
    assert(ll.get_data() == 10);
    for (int i = 9; i > 0; i--) {
        const auto& node = ll.get_next();
        std::cout << "i=" << i << ", val=" << node.get_data() << std::endl;
        std::cout.flush();
        assert(node.get_data() == i);
    }
    return EXIT_SUCCESS;
}
