#include "mem_alloc.h"

/*----- Internal Function Declarations -----*/

char *find_best_fit(char *memory, size_t size);
void set_block_links(char *block, size_t size);
char *get_next_block(char *block, bool forward);
size_t get_block_size(char *block);
size_t get_block_data_size(char *block);
void set_block_status(char *block, bool used);
bool get_block_status(char *block);
size_t coerce_size(size_t size, bool up);
int size_of_link();
void panic_full(char *reason, const char *file, const int line);
void panic(char *reason);

/*----- Memory Allocation Functions -----*/

void *allocate(size_t size, const char *file, const int line) {
    static bool initialized = false;
    static char memory[MAX_MEMORY];

    if (size == 0 || size > MAX_MEMORY) {
        panic_full("User passed bad value", file, line);
    }

    size = coerce_size(size, true);

    if (!initialized) {
        initialized = true;
        memset(memory, 0, sizeof(char) * MAX_MEMORY);
        set_block_links(memory, MAX_MEMORY - size_of_link());
        set_block_status(memory, true);
    }

    char *best_fit = find_best_fit(memory, size);
}

void deallocate(void *ptr, const char *file, const int line) {
    // Cool stuff to come.
}

/*----- Internal Function Implementations -----*/

char *find_best_fit(char *memory, size_t size) {
    char *block = memory, *best_fit;
    while (block >= memory && block < (memory + MAX_MEMORY)) {

    }
}

void set_block_links(char *block, size_t size) {
    int length = size_of_link();
    void *header = block, *footer = block + length + size;
    if (length == 1) {
        char data = (char) size, *cast_head = header, *cast_foot = footer;
        *cast_head = data;
        *cast_foot = data;
    } else if (length == 2) {
        short data = (short) size, *cast_head = header, *cast_foot = footer;
        *cast_head = data;
        *cast_foot = data;
    } else if (length == 4) {
        int data = (int) size, *cast_head = header, *cast_foot = footer;
        *cast_head = data;
        *cast_foot = data;
    } else {
        size_t data = (size_t) size, *cast_head = header, *cast_foot = footer;
        *cast_head = data;
        *cast_foot = data;
    }
}

char *get_next_block(char *block, bool forward) {
    if (forward) {
        return block + get_block_size(block);
    } else {
        return block - get_block_size(block - size_of_link());
    }
}

size_t get_block_size(char *block) {
    int length = size_of_link();
    size_t size;
    if (length == 1) {
        size = (size_t) *block;
    } else if (length == 2) {
        size = (size_t) *((short *) block);
    } else if (length == 4) {
        size = (size_t) *((int *) block);
    } else {
        size = *((size_t *) block);
    }
    return size + (length * 2);
}

size_t get_block_data_size(char *block) {
    return get_block_size(block) - (size_of_link() * 2);
}

void set_block_status(char *block, bool used) {
    int length = size_of_link();
    if (length == 1) {
        *block |= used;
    } else if (length == 2) {
        *((short *) block) |= used;
    } else if (length == 4) {
        *((int *) block) |= used;
    } else {
        *((size_t *) block) |= used;
    }
}

bool get_block_status(char *block) {
    int length = size_of_link();
    if (length == 1) {
        return *block & 1;
    } else if (length == 2) {
        return *((short *) block) & 1;
    } else if (length == 4) {
        return *((int *) block) & 1;
    } else {
        return *((size_t *) block) & 1;
    }
}

size_t coerce_size(size_t size, bool up) {
    if (size % MIN_ALLOC) {
        int next = MIN_ALLOC;
        while (next < size) {
            next += MIN_ALLOC;
        }
        return up ? next : next - MIN_ALLOC;
    } else {
        return size;
    }
}

int size_of_link() {
    if (MAX_MEMORY <= SINGLE_BYTE_MAX) {
        return 1;
    } else if (MAX_MEMORY <= DOUBLE_BYTE_MAX) {
        return 2;
    } else if (MAX_MEMORY <= QUAD_BYTE_MAX) {
        return 4;
    } else {
        return sizeof(size_t);
    }
}

void panic_full(char *reason, const char *file, const int line) {
    fprintf(stderr, "Encountered error [%s] at line #%d in file %s.", reason, line, file);
    exit(EXIT_FAILURE);
}

void panic(char *reason) {
    fprintf(stderr, "Encountered error [%s].", reason);
    exit(EXIT_FAILURE);
}
