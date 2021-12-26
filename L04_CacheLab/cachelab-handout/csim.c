#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** 
 * Zhang Chao (Frodocz)
 */

// Structure for a cache line
typedef struct cache_t {
    int valid;          /* simulate valid bit in a cache line */
    int tag;            /* simulate tag bits in a cache line */
    int timestamp;      /* timestamp used for LRU */
} cache_t;

#define MAX_STR_LEN 100

cache_t **cache = NULL; // cache --> S sets --> S * (E lines)
int hits = 0, misses = 0, evictions = 0;

/**
 * Model the cache structure
 * cache[0]     --> [line 0][line 1]...[line j]...[line E - 1]
 * cache[1]     --> [line 0][line 1]...[line j]...[line E - 1]
 * ...
 * cache[i]     --> [line 0][line 1]...[line j]...[line E - 1]
 * ...
 * cache[S - 1] --> [line 0][line 1]...[line j]...[line E - 1]
 */

void initCache(int S, int E) {
    cache = (cache_t **)malloc(S * sizeof(cache_t *)); // S sets of cache
    for (int i = 0; i < S; ++i) {
        cache[i] = (cache_t *)malloc(E * sizeof(cache_t)); // E lines per set
        for (int j = 0; j < E; ++j) {
            cache[i][j].valid = 0;
            cache[i][j].tag = -1;
            cache[i][j].timestamp = -1;
        }
    }
}

void freeCache(int S) {
    for (int i = 0; i < S; ++i) {
        free(cache[i]);
        cache[i] = NULL;
    }
    free(cache);
    cache = NULL;
}

/**
 * Model of a cache line
 * | valid | tag | cache block |
 * 
 * Model of an address
 * | tag (t-bit) | set index (s-bit) | block offset | 
 */
void updateCache(uint64_t address, int b, int s, int E) {
    int index = (address >> b) & ((-1U) >> (64 - s)); // Get the set index to search
    int tag = address >> (b + s);
    int maxTimestamp = (1 << 31); // Init a max timestamp
    int maxTimestampIdx = -1; // Record the index of this block
    for (int i = 0; i < E; ++i) {
        if (cache[index][i].tag == tag) {
            cache[index][i].timestamp = 0;
            ++hits; // hit
            return;
        }
    }

    // Check if still have available cache space
    for (int i = 0; i < E; ++i) {
        if (cache[index][i].valid == 0){
            cache[index][i].timestamp = 0;
            cache[index][i].valid = 1;
            cache[index][i].tag = tag;
            ++misses; // miss, copy to available block
            return;
        }
    }

    // No available cache space, overwrite by LRU
    ++evictions; ++misses;
    for (int i = 0; i < E; ++i) { // search for the LRU
        if (cache[index][i].timestamp > maxTimestamp) {
            maxTimestamp = cache[index][i].timestamp;
            maxTimestampIdx = i;
        }
    }
    cache[index][maxTimestampIdx].tag = tag;
    cache[index][maxTimestampIdx].timestamp = 0;
    return;
}

void updateTimestamp(int s, int E) {
    int S = 1 << s;
    for (int i = 0; i < S; ++i)
        for(int j = 0; j < E; ++j)
            if(cache[i][j].valid == 1)
                ++cache[i][j].timestamp;
}

/* Parse the cmd line arguments and convert char to int */
int char2int(char c) {
    return c - '0';
}

int main(int argc, char const *argv[]) {
    // 1. Parse the arguments
    int s, E, b, size;
    char op;
    uint64_t address;
    const char *path;
    char str[MAX_STR_LEN] = { 0 };
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            char tag = argv[i][1];
            switch (tag) {
                case 's':
                    s = char2int(argv[++i][0]);
                    break;
                case 'E':
                    E = char2int(argv[++i][0]);
                    break;
                case 'b':
                    b = char2int(argv[++i][0]);
                    break;
                case 't':
                    path = argv[++i];
                    break;
                default:
                    break;
            }
        }
    }

    // printf("s = %d, E = %d, b = %d, path = %s\n", s, E, b, path);
    // 2. Initialize Cache
    initCache(1 << s, E);
    
    // 3. Process the file to simulate the cache
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("Failed to open the file %s\n", path);
        exit(-1);
    }

    while(fgets(str, MAX_STR_LEN, fp)) {
        sscanf(str, " %c %lx,%d", &op, &address, &size);
        switch (op) {
            case 'I':
                continue;
            case 'L':
            case 'S':
                updateCache(address, b, s, E);
                break;
            case 'M':
                updateCache(address, b, s, E);
                updateCache(address, b, s, E);
                break;
        }
        updateTimestamp(s, E);
    }

    // 4. Cleanup
    fclose(fp);
    freeCache(1 << s);
    printSummary(hits, misses, evictions);
    return 0;
}
