#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "mmap.h"

char *MMap::operator *() {
    return _data;
}

MMap::MMap(const char *path, size_t sz) : _data(NULL), _size(sz) {
    int fd = open(path, O_CREAT | O_RDWR, 0666);

    if (fd != -1) {
        struct stat st;
        fstat(fd, &st);

        if (size_t(st.st_size) < sz) {
            lseek(fd, sz - 1, SEEK_SET);
            write(fd, "", 1);
        }

        void *m = mmap(0, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_NORESERVE, fd, 0);
        if (m != MAP_FAILED) {
            _data = (char *)m;
        }        
    }
}

MMap::~MMap() {
    if (_data) {
        munmap(_data, _size);
    }
}

void MMap::sync() {
    msync(_data, _size, MS_SYNC);
}