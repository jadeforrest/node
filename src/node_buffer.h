#ifndef NODE_BUFFER_H_
#define NODE_BUFFER_H_

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <assert.h>

namespace node {

/* A buffer is a chunk of memory stored outside the V8 heap, mirrored by an
 * object in javascript. The object is not totally opaque, one can access
 * individual bytes with [] and slice it into substrings or sub-buffers
 * without copying memory.
 *
 * // return an ascii encoded string - no memory iscopied
 * buffer.asciiSlide(0, 3)
 *
 * // returns another buffer - no memory is copied
 * buffer.slice(0, 3)
 *
 * Interally, each javascript buffer object is backed by a "struct buffer"
 * object.  These "struct buffer" objects are either a root buffer (in the
 * case that buffer->root == NULL) or slice objects (in which case
 * buffer->root != NULL).  A root buffer is only GCed once all its slices
 * are GCed.
 */


struct Blob_;

class Buffer : public ObjectWrap {
 public:
  ~Buffer();

  static void Initialize(v8::Handle<v8::Object> target);
  static Buffer* New(size_t length); // public constructor
  static Buffer* New(char *data, size_t len); // public constructor
  static bool HasInstance(v8::Handle<v8::Value> val);

  static char* Data(v8::Handle<v8::Object>);
  static size_t Length(v8::Handle<v8::Object>);

  char* data() {
    assert(0 && "v0.3 API change: Use node::Buffer::Data().");
    return NULL;
  }


  size_t length() const {
    assert(0 && "v0.3 API change: Use node::Buffer::Length().");
    return 0;
  }

  int AsciiWrite(char *string, int offset, int length);
  int Utf8Write(char *string, int offset, int length);

 private:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  static v8::Handle<v8::Value> New(const v8::Arguments &args);
  static v8::Handle<v8::Value> Slice(const v8::Arguments &args);
  static v8::Handle<v8::Value> BinarySlice(const v8::Arguments &args);
  static v8::Handle<v8::Value> AsciiSlice(const v8::Arguments &args);
  static v8::Handle<v8::Value> Base64Slice(const v8::Arguments &args);
  static v8::Handle<v8::Value> Utf8Slice(const v8::Arguments &args);
  static v8::Handle<v8::Value> BinaryWrite(const v8::Arguments &args);
  static v8::Handle<v8::Value> Base64Write(const v8::Arguments &args);
  static v8::Handle<v8::Value> AsciiWrite(const v8::Arguments &args);
  static v8::Handle<v8::Value> Utf8Write(const v8::Arguments &args);
  static v8::Handle<v8::Value> ByteLength(const v8::Arguments &args);
  static v8::Handle<v8::Value> MakeFastBuffer(const v8::Arguments &args);
  static v8::Handle<v8::Value> Unpack(const v8::Arguments &args);
  static v8::Handle<v8::Value> Copy(const v8::Arguments &args);

  Buffer(size_t length);
  Buffer(Buffer *parent, size_t start, size_t end);

  size_t off_;
  size_t length_;
  char* data_;
};


}  // namespace node buffer

#endif  // NODE_BUFFER_H_
