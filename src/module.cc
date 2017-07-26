#include <nnu.h>

#include "mmap.h"

void freeCb(char *data, void *hint) {
    MMap *ptr = (MMap *)hint;
    delete ptr;
}

NAN_METHOD(sync) {
    nnu::getPrivate<MMap*>(info.This(), "MMapPtr")->sync();
}

NAN_METHOD(map) {
    Nan::Utf8String path(info[0]);
    const size_t length  = info[1]->NumberValue();

    MMap *ptr = new MMap(*path, length);

    if (**ptr) {
        v8::Local<v8::Object> buffer = Nan::NewBuffer(**ptr, length, freeCb, ptr).ToLocalChecked();

        nnu::setPrivate(buffer, "MMapPtr", ptr);
        Nan::SetMethod(buffer, "sync", sync);

        info.GetReturnValue().Set(buffer);
    } else {
        Nan::ThrowError("Create mmap failed.");
    }
}

NAN_MODULE_INIT(initAll) {
    NAN_EXPORT(target, map);
}

NODE_MODULE(mmap, initAll);