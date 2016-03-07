#ifndef __V8DISPATCH_H__
#define __V8DISPATCH_H__

#include <node.h>
#include <nan.h>
#include "node_win32ole.h"
#include "ole32core.h"

namespace node_win32ole {

class V8Dispatch : public node::ObjectWrap {
public:
  static Nan::Persistent<FunctionTemplate> clazz;
  static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);
  static NAN_METHOD(OLEValue);
  static NAN_METHOD(OLEPrimitiveValue);
  static NAN_METHOD(OLEStringValue);
  static NAN_METHOD(OLELocaleStringValue);
  static Handle<Object> CreateNew(IDispatch* disp); // *** private
  static NAN_METHOD(New);
  static NAN_PROPERTY_GETTER(OLEGetAttr);
  static NAN_PROPERTY_SETTER(OLESetAttr);
  static NAN_INDEX_GETTER(OLEGetIdxAttr);
  static NAN_INDEX_SETTER(OLESetIdxAttr);
  static NAN_METHOD(Finalize);
public:
  V8Dispatch() : finalized(false) {}
  ~V8Dispatch() { if(!finalized) Finalize(); }
  ole32core::OCDispatch ocd;

  Local<Value> OLECall(DISPID propID, Nan::NAN_METHOD_ARGS_TYPE info);
  Local<Value> OLECall(DISPID propID, int argc = 0, Local<Value> argv[] = NULL);
  Local<Value> OLEGet(DISPID propID, int argc = 0, Local<Value> argv[] = NULL);
  bool OLESet(DISPID propID, int argc = 0, Local<Value> argv[] = NULL);

protected:
  static Local<Value> resolveValueChain(Local<Object> thisObject, const char* prop);
  void Finalize();
  bool finalized;
};

} // namespace node_win32ole

#endif // __V8VARIANT_H__
