#pragma once

#include <cstddef>

class MMap {
public:
    MMap(const char *path, size_t sz);
    virtual ~MMap();

public:
    void sync();
    char *operator *();

private:
    char *_data;
    size_t _size;
};