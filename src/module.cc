#include <nnu.h>

#include "mmap.h"

void freeCb(char *data, void *hint) {
    MMap *ptr = (MMap *)hint;
    delete ptr;
}

NAN_METHOD(sync) {
    v8::Local<v8::Value> val = Nan::GetPrivate(info.This(), nnu::newString("MMapPtr")).ToLocalChecked();
    MMap *ptr = (MMap *)v8::External::Cast(*val)->Value();
    ptr->sync();
}

NAN_METHOD(map) {
    Nan::Utf8String path(info[0]);
    const size_t length  = info[1]->NumberValue();

    MMap *ptr = new MMap(*path, length);

    if (**ptr) {
        v8::Local<v8::Object> buffer = Nan::NewBuffer(**ptr, length, freeCb, ptr).ToLocalChecked();

        Nan::SetPrivate(buffer, nnu::newString("MMapPtr"), Nan::New<v8::External>(ptr));
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