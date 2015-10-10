// Copyright 2015 Las Venturas Playground. All rights reserved.
// Use of this source code is governed by the MIT license, a copy of which can
// be found in the LICENSE file.

#ifndef PLAYGROUND_BINDINGS_EXCEPTION_HANDLER_H_
#define PLAYGROUND_BINDINGS_EXCEPTION_HANDLER_H_

#include "bindings/runtime.h"

namespace bindings {

// A scoped exception source may be used to improve the clarity of exceptions generated by code ran
// because we invoked JavaScript for some reason. The reason will be included in the output.
class ScopedExceptionSource {
 public:
  explicit ScopedExceptionSource(const std::string& source);
  ~ScopedExceptionSource();
};

// The exception handler handles exceptions that are not handled in the JavaScript code by
// outputting them to the console in a neatly formatted fashion.
class ExceptionHandler {
 public:
  explicit ExceptionHandler(Runtime::Delegate* runtime_delegate);
  ~ExceptionHandler();

  // Called when the v8 runtime generates a message. It may also be called manually by any code
  // that maintains a v8::TryCatch before doing an operation on the engine.
  void OnMessage(v8::Local<v8::Message> message, v8::Local<v8::Value> error);

  // Called when a non-recoverable error occurs within the runtime.
  void OnFatalError(const char* location, const char* message);

 private:
  Runtime::Delegate* runtime_delegate_;
};

}  // namespace bindings

#endif  // PLAYGROUND_BINDINGS_EXCEPTION_HANDLER_H_