#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "definitions.h"
#include "nodes.h"
#include "hash.h"
#include "splitter.h"

void handle_file(char *path, hash *table);
void handle_dir(char *path, hash *table);
bool is_file(char *path);
bool is_dir(char *path);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Error: Wrong number of arguments\n");
        return 1;
    }

    hash *table = create_hash();
    if (is_file(argv[2])) {
        handle_file(argv[2], table);
    } else if (is_dir(argv[2])) {
        handle_dir(argv[2], table);
    } else {
        fprintf(stderr, "Error: Could not open specified file. Perhaps it doesn't exist?\n");
        destroy_hash(table);
        return 1;
    }

    return 0;
}

void handle_dir(char *path, hash *table) {
    DIR *directory = opendir(path);
    if (directory) {
        for (struct dirent *entry = readdir(directory); entry; entry = readdir(directory)) {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                char new_path[strlen(path) + strlen(entry->d_name) + 2];
                sprintf(new_path, "%s/%s", path, entry->d_name);
                if (entry->d_type & DT_REG) {
                    handle_file(new_path, table);
                } else if (entry->d_type & DT_DIR) {
                    handle_dir(new_path, table);
                } else {
                    fprintf(stderr, "Warning: Directory hierarchy contains an entry which is neither a regular file nor directory, skipping it\n");
                }
            }
        }
    } else {
        fprintf(stderr, "Error: Directory %s could not be opened\n", path);
    }
}

void handle_file(char *path, hash *table) {
    FILE *file = fopen(path, "r");
    if (file) {
        splitter *split = create_splitter(file);
        for (char *token = split_next(split); token; token = split_next(split)) {
            index_node *head = get(table, token);
            if (head) {
                index_node *target = find_index_node(head, path);
                if (target) {
                    target->count++;
                } else {
                    target = create_index_node(path);
                    target->count++;
                }
            } else {
                index_node *node = create_index_node(path);
                node->count++;
                put(table, token, node);
            }
        }
    } else {
        fprintf(stderr, "Error: File %s could not be opened\n", path);
    }
}

bool is_file(char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}