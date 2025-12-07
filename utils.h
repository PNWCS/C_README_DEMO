#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define TABLE_SIZE 10007

void init_table();
bool insert_ip(const char* ip);
void free_table();

#endif
