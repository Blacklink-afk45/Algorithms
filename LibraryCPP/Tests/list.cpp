#include <iostream>

#include "list.h"

#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Check failed: " #condition " at line " << __LINE__ << '\n'; \
            return 1; \
        } \
    } while (false)

int main() {
    List* list = list_create();

    // Keep the original checks from this test and make them fail reliably in
    // both debug and release builds.
    if (!list) {
        std::cout << "List creation error\n";
        return 1;
    }

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    if (list_item_data(list_first(list)) != 3) {
        std::cout << "list_insert error\n";
        return 1;
    }
    if (list_item_data(list_last(list)) != 1) {
        std::cout << "list_insert error\n";
        return 1;
    }

    list_insert_after(list, list_first(list), 4);
    if (list_item_data(list_item_next(list_first(list))) != 4) {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list_erase_first(list);
    if (list_item_data(list_first(list)) != 4) {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List: ";
    for (ListItem* item = list_first(list); item; item = list_item_next(item)) {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";
    list_delete(list);

    // Check empty boundaries, forward links, and insertion after a middle item.
    list = list_create();
    CHECK(list_first(list) == nullptr);
    CHECK(list_last(list) == nullptr);

    ListItem* three = list_insert(list, 3);
    ListItem* two = list_insert(list, 2);
    ListItem* one = list_insert(list, 1);
    CHECK(list_item_data(list_first(list)) == 1);
    CHECK(list_item_data(list_last(list)) == 3);
    CHECK(list_item_next(one) == two);
    CHECK(list_item_next(two) == three);
    CHECK(list_item_next(three) == nullptr);

    ListItem* four = list_insert_after(list, two, 4);
    CHECK(list_item_next(two) == four);
    CHECK(list_item_next(four) == three);
    CHECK(list_last(list) == three);

    // Erasing the first, middle, and last elements updates both boundaries.
    CHECK(list_erase_first(list) == two);
    CHECK(list_item_data(list_first(list)) == 2);
    CHECK(list_erase_next(list, two) == three);
    CHECK(list_erase_next(list, two) == nullptr);
    CHECK(list_first(list) == two);
    CHECK(list_last(list) == two);
    CHECK(list_erase_first(list) == nullptr);
    CHECK(list_first(list) == nullptr);
    CHECK(list_last(list) == nullptr);

    // An empty list remains safe and reusable after erasing.
    CHECK(list_erase_first(list) == nullptr);
    ListItem* only = list_insert(list, 42);
    CHECK(list_first(list) == only);
    CHECK(list_last(list) == only);
    CHECK(list_erase_first(list) == nullptr);
    CHECK(list_first(list) == nullptr);

    list_delete(list);
}
