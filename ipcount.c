#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_LINE 256

static void print_usage(const char* progname) {
    fprintf(stderr, "Usage: %s [-v] <input_file>\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -v    Verbose mode: print each new unique IP as it is counted.\n");
    fprintf(stderr, "  -h    Show this help message and exit.\n");
}

int main(int argc, char* argv[]) {
    int verbose = 0;
    const char* filename = NULL;

    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    int argi = 1;

    // Handle optional flags (-h, -v)
    while (argi < argc && argv[argi][0] == '-') {
        if (strcmp(argv[argi], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[argi], "-v") == 0) {
            verbose = 1;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[argi]);
            print_usage(argv[0]);
            return 1;
        }
        argi++;
    }

    if (argi >= argc) {
        fprintf(stderr, "Missing input file.\n");
        print_usage(argv[0]);
        return 1;
    }

    filename = argv[argi];

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    init_table();

    char line[MAX_LINE];
    int unique_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue;
        }

        if (insert_ip(line)) {
            unique_count++;
            if (verbose) {
                printf("[new] %s\n", line);
            }
        }
    }

    fclose(fp);

    printf("Unique IP addresses: %d\n", unique_count);

    free_table();
    return 0;
}
