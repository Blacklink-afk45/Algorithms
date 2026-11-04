#include <stdexcept>
#include "queue.h"
#include "list.h"

struct Queue {
    List* input;
    List* output;
};

Queue* queue_create() {
    return new Queue{list_create(), list_create()};
}

void queue_delete(Queue* queue) {
    if (!queue) return;
    list_delete(queue->input);
    list_delete(queue->output);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    list_insert(queue->input, data);
}

static void prepare_output(const Queue* queue) {
    if (list_first(queue->output)) return;
    while (list_first(queue->input)) {
        list_insert(queue->output, list_item_data(list_first(queue->input)));
        list_erase_first(queue->input);
    }
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) throw std::out_of_range("Queue is empty");
    prepare_output(queue);
    return list_item_data(list_first(queue->output));
}

void queue_remove(Queue* queue) {
    prepare_output(queue);
    list_erase_first(queue->output);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->input) == nullptr && list_first(queue->output) == nullptr;
}
