#include <node.h>
#include <uv.h>

namespace demo {

using namespace v8;

static std::string fooLib;

void TestLoadLibrary(const FunctionCallbackInfo<Value>& args) {
  uv_lib_t lib;
  const int result = uv_dlopen(fooLib.c_str(), &lib);

  Isolate* isolate = args.GetIsolate();
  if (result == 0)
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Success", NewStringType::kNormal).ToLocalChecked());
  else {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, uv_dlerror(&lib), NewStringType::kNormal).ToLocalChecked());
  }
}

extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(Local<Object> exports, Local<Value> module, Local<Context> context) {
  Isolate* isolate = Isolate::GetCurrent();
  auto v8Path = module->ToObject(context).ToLocalChecked()
    ->Get(context, String::NewFromUtf8(isolate, "path", NewStringType::kNormal).ToLocalChecked())
    .ToLocalChecked();
#ifdef __linux__
  fooLib = std::string(*String::Utf8Value(isolate, v8Path)) + "/foo.so";
#elif _WIN32
  fooLib = std::string(*String::Utf8Value(isolate, v8Path)) + "/libfoo.dll";
#else
  error: "Unsupported OS"
#endif
  NODE_SET_METHOD(exports, "testLoadLibrary", TestLoadLibrary);
}

}  // namespace demo