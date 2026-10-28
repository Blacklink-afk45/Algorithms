#include <iostream>
#include <stdexcept>

#include "queue.h"

#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Check failed: " #condition " at line " << __LINE__ << '\n'; \
            return 1; \
        } \
    } while (false)

int main() {
    Queue* queue = queue_create();
    CHECK(queue != nullptr);

    // Keep the original FIFO checks and output while adding explicit checks
    // for the empty state and the queue's transition back to empty.
    queue_insert(queue, 1);
    queue_insert(queue, 2);
    queue_insert(queue, 3);

    if (queue_get(queue) != 1) {
        std::cout << "Invalid first element of the queue\n";
        return 1;
    }
    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 2) {
        std::cout << "Invalid second element of the queue\n";
        return 1;
    }
    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_remove(queue);

    if (queue_get(queue) != 3) {
        std::cout << "Invalid third element of the queue\n";
        return 1;
    }
    std::cout << "Get: " << queue_get(queue) << "\n";
    queue_insert(queue, 4);
    while (!queue_empty(queue)) {
        std::cout << "Get: " << queue_get(queue) << "\n";
        queue_remove(queue);
    }
    CHECK(queue_empty(queue));

    // Reading an empty queue must report the documented error.
    bool threw_on_empty_get = false;
    try {
        (void)queue_get(queue);
    } catch (const std::out_of_range&) {
        threw_on_empty_get = true;
    }
    CHECK(threw_on_empty_get);

    // Removing from empty is harmless, and enqueue/dequeue works after empty.
    queue_remove(queue);
    CHECK(queue_empty(queue));
    queue_insert(queue, 50);
    CHECK(queue_get(queue) == 50);
    queue_remove(queue);
    CHECK(queue_empty(queue));

    // Preserve the original queue performance checks.
    queue_insert(queue, 0);
    for (int i = 1; i <= 1000000; ++i) {
        queue_insert(queue, i);
    }
    for (int i = 1; i <= 1000000; ++i) {
        queue_remove(queue);
    }
    for (int i = 1; i <= 1000000; ++i) {
        queue_insert(queue, i);
        queue_remove(queue);
    }

    queue_delete(queue);

    queue = queue_create();
    queue_insert(queue, 0);
    for (int i = 1; i <= 100000; ++i) {
        const int count = 1 + i % 20;
        for (int j = 0; j < count; ++j) {
            queue_insert(queue, i);
        }
        for (int j = 0; j < count; ++j) {
            queue_remove(queue);
        }
    }
    queue_delete(queue);
}
