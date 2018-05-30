#include <node.h>
#include <v8.h>
#include <errno.h>
#include <unistd.h>

static v8::Handle<v8::Value> Hostname(const v8::Arguments& args) {
    v8::HandleScope scope;
    char name[255];

    int code = gethostname(name, 255);
    if (code < 0) {
      return v8::ThrowException(node::ErrnoException(errno, "gethostname"));
    }

    return scope.Close(v8::String::New(name));
}

extern "C" void init(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;
    NODE_SET_METHOD(target, "hostname", Hostname);
}
