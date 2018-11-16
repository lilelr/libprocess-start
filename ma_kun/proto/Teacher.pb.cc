// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Teacher.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Teacher.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Chinese_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Chinese_reflection_ = NULL;
const ::google::protobuf::Descriptor* Teacher_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Teacher_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Teacher_2eproto() {
  protobuf_AddDesc_Teacher_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Teacher.proto");
  GOOGLE_CHECK(file != NULL);
  Chinese_descriptor_ = file->message_type(0);
  static const int Chinese_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, age_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, career_),
  };
  Chinese_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Chinese_descriptor_,
      Chinese::default_instance_,
      Chinese_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Chinese, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Chinese));
  Teacher_descriptor_ = file->message_type(1);
  static const int Teacher_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, value_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, hostname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, lele_label_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, chinese_),
  };
  Teacher_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Teacher_descriptor_,
      Teacher::default_instance_,
      Teacher_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Teacher, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Teacher));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Teacher_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Chinese_descriptor_, &Chinese::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Teacher_descriptor_, &Teacher::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Teacher_2eproto() {
  delete Chinese::default_instance_;
  delete Chinese_reflection_;
  delete Teacher::default_instance_;
  delete Teacher_reflection_;
}

void protobuf_AddDesc_Teacher_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rTeacher.proto\"@\n\007Chinese\022\013\n\003age\030\001 \002(\005\022"
    "\n\n\002id\030\002 \002(\005\022\014\n\004name\030\003 \002(\t\022\016\n\006career\030\004 \001("
    "\t\"f\n\007Teacher\022\013\n\003key\030\001 \002(\t\022\r\n\005value\030\002 \002(\014"
    "\022\020\n\010hostname\030\004 \001(\t\022\022\n\nlele_label\030\005 \001(\t\022\031"
    "\n\007chinese\030\006 \002(\0132\010.Chinese", 185);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Teacher.proto", &protobuf_RegisterTypes);
  Chinese::default_instance_ = new Chinese();
  Teacher::default_instance_ = new Teacher();
  Chinese::default_instance_->InitAsDefaultInstance();
  Teacher::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Teacher_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Teacher_2eproto {
  StaticDescriptorInitializer_Teacher_2eproto() {
    protobuf_AddDesc_Teacher_2eproto();
  }
} static_descriptor_initializer_Teacher_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Chinese::kAgeFieldNumber;
const int Chinese::kIdFieldNumber;
const int Chinese::kNameFieldNumber;
const int Chinese::kCareerFieldNumber;
#endif  // !_MSC_VER

Chinese::Chinese()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Chinese)
}

void Chinese::InitAsDefaultInstance() {
}

Chinese::Chinese(const Chinese& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Chinese)
}

void Chinese::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  age_ = 0;
  id_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  career_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Chinese::~Chinese() {
  // @@protoc_insertion_point(destructor:Chinese)
  SharedDtor();
}

void Chinese::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (career_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete career_;
  }
  if (this != default_instance_) {
  }
}

void Chinese::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Chinese::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Chinese_descriptor_;
}

const Chinese& Chinese::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Teacher_2eproto();
  return *default_instance_;
}

Chinese* Chinese::default_instance_ = NULL;

Chinese* Chinese::New() const {
  return new Chinese;
}

void Chinese::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Chinese*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 15) {
    ZR_(age_, id_);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
    if (has_career()) {
      if (career_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        career_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Chinese::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Chinese)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 age = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &age_)));
          set_has_age();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_id;
        break;
      }

      // required int32 id = 2;
      case 2: {
        if (tag == 16) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_name;
        break;
      }

      // required string name = 3;
      case 3: {
        if (tag == 26) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_career;
        break;
      }

      // optional string career = 4;
      case 4: {
        if (tag == 34) {
         parse_career:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_career()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->career().data(), this->career().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "career");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Chinese)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Chinese)
  return false;
#undef DO_
}

void Chinese::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Chinese)
  // required int32 age = 1;
  if (has_age()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->age(), output);
  }

  // required int32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->id(), output);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->name(), output);
  }

  // optional string career = 4;
  if (has_career()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->career().data(), this->career().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "career");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->career(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Chinese)
}

::google::protobuf::uint8* Chinese::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Chinese)
  // required int32 age = 1;
  if (has_age()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->age(), target);
  }

  // required int32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->id(), target);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->name(), target);
  }

  // optional string career = 4;
  if (has_career()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->career().data(), this->career().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "career");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->career(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Chinese)
  return target;
}

int Chinese::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 age = 1;
    if (has_age()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->age());
    }

    // required int32 id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

    // required string name = 3;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // optional string career = 4;
    if (has_career()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->career());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Chinese::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Chinese* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Chinese*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Chinese::MergeFrom(const Chinese& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_age()) {
      set_age(from.age());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_career()) {
      set_career(from.career());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Chinese::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Chinese::CopyFrom(const Chinese& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Chinese::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void Chinese::Swap(Chinese* other) {
  if (other != this) {
    std::swap(age_, other->age_);
    std::swap(id_, other->id_);
    std::swap(name_, other->name_);
    std::swap(career_, other->career_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Chinese::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Chinese_descriptor_;
  metadata.reflection = Chinese_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Teacher::kKeyFieldNumber;
const int Teacher::kValueFieldNumber;
const int Teacher::kHostnameFieldNumber;
const int Teacher::kLeleLabelFieldNumber;
const int Teacher::kChineseFieldNumber;
#endif  // !_MSC_VER

Teacher::Teacher()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Teacher)
}

void Teacher::InitAsDefaultInstance() {
  chinese_ = const_cast< ::Chinese*>(&::Chinese::default_instance());
}

Teacher::Teacher(const Teacher& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Teacher)
}

void Teacher::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  value_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  hostname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  lele_label_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  chinese_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Teacher::~Teacher() {
  // @@protoc_insertion_point(destructor:Teacher)
  SharedDtor();
}

void Teacher::SharedDtor() {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete key_;
  }
  if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete value_;
  }
  if (hostname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete hostname_;
  }
  if (lele_label_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete lele_label_;
  }
  if (this != default_instance_) {
    delete chinese_;
  }
}

void Teacher::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Teacher::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Teacher_descriptor_;
}

const Teacher& Teacher::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Teacher_2eproto();
  return *default_instance_;
}

Teacher* Teacher::default_instance_ = NULL;

Teacher* Teacher::New() const {
  return new Teacher;
}

void Teacher::Clear() {
  if (_has_bits_[0 / 32] & 31) {
    if (has_key()) {
      if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        key_->clear();
      }
    }
    if (has_value()) {
      if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        value_->clear();
      }
    }
    if (has_hostname()) {
      if (hostname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        hostname_->clear();
      }
    }
    if (has_lele_label()) {
      if (lele_label_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        lele_label_->clear();
      }
    }
    if (has_chinese()) {
      if (chinese_ != NULL) chinese_->::Chinese::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Teacher::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Teacher)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string key = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_key()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->key().data(), this->key().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "key");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_value;
        break;
      }

      // required bytes value = 2;
      case 2: {
        if (tag == 18) {
         parse_value:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_value()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_hostname;
        break;
      }

      // optional string hostname = 4;
      case 4: {
        if (tag == 34) {
         parse_hostname:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_hostname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->hostname().data(), this->hostname().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "hostname");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_lele_label;
        break;
      }

      // optional string lele_label = 5;
      case 5: {
        if (tag == 42) {
         parse_lele_label:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_lele_label()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->lele_label().data(), this->lele_label().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "lele_label");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(50)) goto parse_chinese;
        break;
      }

      // required .Chinese chinese = 6;
      case 6: {
        if (tag == 50) {
         parse_chinese:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_chinese()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Teacher)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Teacher)
  return false;
#undef DO_
}

void Teacher::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Teacher)
  // required string key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->key().data(), this->key().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "key");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->key(), output);
  }

  // required bytes value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->value(), output);
  }

  // optional string hostname = 4;
  if (has_hostname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->hostname().data(), this->hostname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "hostname");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->hostname(), output);
  }

  // optional string lele_label = 5;
  if (has_lele_label()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->lele_label().data(), this->lele_label().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "lele_label");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->lele_label(), output);
  }

  // required .Chinese chinese = 6;
  if (has_chinese()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->chinese(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Teacher)
}

::google::protobuf::uint8* Teacher::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Teacher)
  // required string key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->key().data(), this->key().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "key");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->key(), target);
  }

  // required bytes value = 2;
  if (has_value()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->value(), target);
  }

  // optional string hostname = 4;
  if (has_hostname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->hostname().data(), this->hostname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "hostname");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->hostname(), target);
  }

  // optional string lele_label = 5;
  if (has_lele_label()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->lele_label().data(), this->lele_label().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "lele_label");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->lele_label(), target);
  }

  // required .Chinese chinese = 6;
  if (has_chinese()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->chinese(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Teacher)
  return target;
}

int Teacher::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->key());
    }

    // required bytes value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->value());
    }

    // optional string hostname = 4;
    if (has_hostname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->hostname());
    }

    // optional string lele_label = 5;
    if (has_lele_label()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->lele_label());
    }

    // required .Chinese chinese = 6;
    if (has_chinese()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->chinese());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Teacher::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Teacher* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Teacher*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Teacher::MergeFrom(const Teacher& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
    if (from.has_hostname()) {
      set_hostname(from.hostname());
    }
    if (from.has_lele_label()) {
      set_lele_label(from.lele_label());
    }
    if (from.has_chinese()) {
      mutable_chinese()->::Chinese::MergeFrom(from.chinese());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Teacher::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Teacher::CopyFrom(const Teacher& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Teacher::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000013) != 0x00000013) return false;

  if (has_chinese()) {
    if (!this->chinese().IsInitialized()) return false;
  }
  return true;
}

void Teacher::Swap(Teacher* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(value_, other->value_);
    std::swap(hostname_, other->hostname_);
    std::swap(lele_label_, other->lele_label_);
    std::swap(chinese_, other->chinese_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Teacher::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Teacher_descriptor_;
  metadata.reflection = Teacher_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
