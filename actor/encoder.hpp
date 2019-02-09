// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

#ifndef MY__ENCODER_HPP__
#define MY__ENCODER_HPP__

#include <stdint.h>
#include <time.h>

#include <limits>
#include <map>
#include <sstream>

#include <process/http.hpp>

#include <stout/foreach.hpp>
#include <stout/gzip.hpp>
#include <stout/hashmap.hpp>
#include <stout/numify.hpp>
#include <stout/os.hpp>

#include "actor.hpp"
#include "mymessage.hpp"


namespace actor {

const uint32_t GZIP_MINIMUM_BODY_LENGTH = 1024;

// Forward declarations.
class Encoder;


class Encoder
{
public:
  enum Kind
  {
    DATA,
    FILE
  };

  Encoder() = default;

  virtual ~Encoder() {}

  virtual Kind kind() const = 0;

  virtual void backup(size_t length) = 0;

  virtual size_t remaining() const = 0;
};


class DataEncoder : public Encoder
{
public:
  DataEncoder(const std::string& _data)
    : data(_data), index(0) {}

  virtual ~DataEncoder() {}

  virtual Kind kind() const
  {
    return Encoder::DATA;
  }

  virtual const char* next(size_t* length)
  {
    size_t temp = index;
    index = data.size();
    *length = data.size() - temp;
    return data.data() + temp;
  }

  virtual void backup(size_t length)
  {
    if (index >= length) {
      index -= length;
    }
  }

  virtual size_t remaining() const
  {
    return data.size() - index;
  }

private:
  const std::string data;
  size_t index;
};


class MessageEncoder : public DataEncoder
{
public:
  MessageEncoder(MyMessage* _message)
    : DataEncoder(encode(_message)), message(_message) {}

  virtual ~MessageEncoder()
  {
    if (message != nullptr) {
      delete message;
    }
  }

  static std::string encode(MyMessage* message)
  {
    std::ostringstream out;

    if (message != nullptr) {
      out << "POST ";
      // Nothing keeps the 'id' component of a PID from being an empty
      // string which would create a malformed path that has two
      // '//' unless we check for it explicitly.
      // TODO(benh): Make the 'id' part of a PID optional so when it's
      // missing it's clear that we're simply addressing an ip:port.
      if (message->to.id != "") {
        out << "/" << message->to.id;
      }

      out << "/" << message->name << " HTTP/1.1\r\n"
          << "User-Agent: libprocess/" << message->from << "\r\n"
          << "Libprocess-From: " << message->from << "\r\n"
          << "Connection: Keep-Alive\r\n"
          << "Host: \r\n";

      if (message->body.size() > 0) {
        out << "Transfer-Encoding: chunked\r\n\r\n"
            << std::hex << message->body.size() << "\r\n";
        out.write(message->body.data(), message->body.size());
        out << "\r\n"
            << "0\r\n"
            << "\r\n";
      } else {
        out << "\r\n";
      }
    }

    return out.str();
  }

private:
    MyMessage* message;
};



class FileEncoder : public Encoder
{
public:
  FileEncoder(int_fd _fd, size_t _size)
    : fd(_fd), size(static_cast<off_t>(_size)), index(0)
  {
    // NOTE: For files, we expect the size to be derived from `stat`-ing
    // the file.  The `struct stat` returns the size in `off_t` form,
    // meaning that it is a programmer error to construct the `FileEncoder`
    // with a size greater the max value of `off_t`.
    CHECK_LE(_size, static_cast<size_t>(std::numeric_limits<off_t>::max()));
  }

  virtual ~FileEncoder()
  {
    CHECK_SOME(os::close(fd)) << "Failed to close file descriptor";
  }

  virtual Kind kind() const
  {
    return Encoder::FILE;
  }

  virtual int_fd next(off_t* offset, size_t* length)
  {
    off_t temp = index;
    index = size;
    *offset = temp;
    *length = size - temp;
    return fd;
  }

  virtual void backup(size_t length)
  {
    if (index >= static_cast<off_t>(length)) {
      index -= static_cast<off_t>(length);
    }
  }

  virtual size_t remaining() const
  {
    return static_cast<size_t>(size - index);
  }

private:
  int_fd fd;
  off_t size;
  off_t index;
};

}  // namespace process {

#endif // __ENCODER_HPP__
