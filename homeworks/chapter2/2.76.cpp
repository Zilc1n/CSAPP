#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string.h>
void *calloc(size_t nmemb, size_t size) {
    if (!nmemb or !size)
        return NULL;
    size_t buf_size = nmemb * size;
    if (nmemb == buf_size / size) {
        void *ptr = malloc(buf_size);
        if (ptr != NULL) {
            memset(ptr, 0, buf_size);
        }
        return ptr;
    }
    return NULL;
    return NULL;
}

int main() {
    void *p;
    p = calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);
    return 0;
}