/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_types_h.h>



namespace apache {
namespace thrift {
namespace tag {
struct majorVer;
struct package;
struct annotation_with_quote;
struct class_;
} // namespace tag
namespace detail {
#ifndef APACHE_THRIFT_ACCESSOR_majorVer
#define APACHE_THRIFT_ACCESSOR_majorVer
APACHE_THRIFT_DEFINE_ACCESSOR(majorVer);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_package
#define APACHE_THRIFT_ACCESSOR_package
APACHE_THRIFT_DEFINE_ACCESSOR(package);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_annotation_with_quote
#define APACHE_THRIFT_ACCESSOR_annotation_with_quote
APACHE_THRIFT_DEFINE_ACCESSOR(annotation_with_quote);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_class_
#define APACHE_THRIFT_ACCESSOR_class_
APACHE_THRIFT_DEFINE_ACCESSOR(class_);
#endif
} // namespace detail
} // namespace thrift
} // namespace apache

// BEGIN declare_enums
namespace cpp2 {

enum class MyEnum {
  MyValue1 = 0,
  MyValue2 = 1,
  REALM = 2
};




} // cpp2
namespace std {


template<> struct hash<typename ::cpp2::MyEnum> : public apache::thrift::detail::enum_hash<typename ::cpp2::MyEnum> {};
template<> struct equal_to<typename ::cpp2::MyEnum> : public apache::thrift::detail::enum_equal_to<typename ::cpp2::MyEnum> {};


} // std

namespace apache { namespace thrift {


template <> struct TEnumDataStorage<::cpp2::MyEnum>;

template <> struct TEnumTraits<::cpp2::MyEnum> {
  using type = ::cpp2::MyEnum;

  static constexpr std::size_t const size = 3;
  static folly::Range<type const*> const values;
  static folly::Range<folly::StringPiece const*> const names;

  static char const* findName(type value);
  static bool findValue(char const* name, type* out);

  static constexpr type min() { return type::MyValue1; }
  static constexpr type max() { return type::REALM; }
};


}} // apache::thrift

namespace cpp2 {

using _MyEnum_EnumMapFactory = apache::thrift::detail::TEnumMapFactory<MyEnum>;
extern const _MyEnum_EnumMapFactory::ValuesToNamesMapType _MyEnum_VALUES_TO_NAMES;
extern const _MyEnum_EnumMapFactory::NamesToValuesMapType _MyEnum_NAMES_TO_VALUES;

} // cpp2

// END declare_enums
// BEGIN struct_indirection

// END struct_indirection
// BEGIN forward_declare
namespace cpp2 {
class MyStruct;
} // cpp2
// END forward_declare
// BEGIN typedefs

// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
namespace cpp2 {
class MyStruct final : private apache::thrift::detail::st::ComparisonOperators<MyStruct> {
 public:

  MyStruct() :
      majorVer(0) {}
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  MyStruct(apache::thrift::FragileConstructor, int64_t majorVer__arg, ::std::string package__arg, ::std::string annotation_with_quote__arg, ::std::string class___arg);

  MyStruct(MyStruct&&) = default;

  MyStruct(const MyStruct&) = default;

  MyStruct& operator=(MyStruct&&) = default;

  MyStruct& operator=(const MyStruct&) = default;
  void __clear();
 public:
  int64_t majorVer;
 public:
  ::std::string package;
 public:
  ::std::string annotation_with_quote;
 public:
  ::std::string class_;

 public:
  struct __isset {
    bool majorVer;
    bool package;
    bool annotation_with_quote;
    bool class_;
  } __isset = {};
  bool operator==(const MyStruct& rhs) const;
  bool operator<(const MyStruct& rhs) const;

  template <typename..., typename T = int64_t>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> majorVer_ref() const& {
    return {this->majorVer, __isset.majorVer};
  }

  template <typename..., typename T = int64_t>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> majorVer_ref() const&& {
    return {std::move(this->majorVer), __isset.majorVer};
  }

  template <typename..., typename T = int64_t>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> majorVer_ref() & {
    return {this->majorVer, __isset.majorVer};
  }

  template <typename..., typename T = int64_t>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> majorVer_ref() && {
    return {std::move(this->majorVer), __isset.majorVer};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> package_ref() const& {
    return {this->package, __isset.package};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> package_ref() const&& {
    return {std::move(this->package), __isset.package};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> package_ref() & {
    return {this->package, __isset.package};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> package_ref() && {
    return {std::move(this->package), __isset.package};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> annotation_with_quote_ref() const& {
    return {this->annotation_with_quote, __isset.annotation_with_quote};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> annotation_with_quote_ref() const&& {
    return {std::move(this->annotation_with_quote), __isset.annotation_with_quote};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> annotation_with_quote_ref() & {
    return {this->annotation_with_quote, __isset.annotation_with_quote};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> annotation_with_quote_ref() && {
    return {std::move(this->annotation_with_quote), __isset.annotation_with_quote};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> class__ref() const& {
    return {this->class_, __isset.class_};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> class__ref() const&& {
    return {std::move(this->class_), __isset.class_};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> class__ref() & {
    return {this->class_, __isset.class_};
  }

  template <typename..., typename T = ::std::string>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> class__ref() && {
    return {std::move(this->class_), __isset.class_};
  }

  int64_t get_majorVer() const {
    return majorVer;
  }

  int64_t& set_majorVer(int64_t majorVer_) {
    majorVer = majorVer_;
    __isset.majorVer = true;
    return majorVer;
  }

  const ::std::string& get_package() const& {
    return package;
  }

  ::std::string get_package() && {
    return std::move(package);
  }

  template <typename T_MyStruct_package_struct_setter = ::std::string>
  ::std::string& set_package(T_MyStruct_package_struct_setter&& package_) {
    package = std::forward<T_MyStruct_package_struct_setter>(package_);
    __isset.package = true;
    return package;
  }

  const ::std::string& get_annotation_with_quote() const& {
    return annotation_with_quote;
  }

  ::std::string get_annotation_with_quote() && {
    return std::move(annotation_with_quote);
  }

  template <typename T_MyStruct_annotation_with_quote_struct_setter = ::std::string>
  ::std::string& set_annotation_with_quote(T_MyStruct_annotation_with_quote_struct_setter&& annotation_with_quote_) {
    annotation_with_quote = std::forward<T_MyStruct_annotation_with_quote_struct_setter>(annotation_with_quote_);
    __isset.annotation_with_quote = true;
    return annotation_with_quote;
  }

  const ::std::string& get_class_() const& {
    return class_;
  }

  ::std::string get_class_() && {
    return std::move(class_);
  }

  template <typename T_MyStruct_class__struct_setter = ::std::string>
  ::std::string& set_class_(T_MyStruct_class__struct_setter&& class__) {
    class_ = std::forward<T_MyStruct_class__struct_setter>(class__);
    __isset.class_ = true;
    return class_;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  template <class Protocol_>
  void readNoXfer(Protocol_* iprot);

  friend class ::apache::thrift::Cpp2Ops< MyStruct >;
};

void swap(MyStruct& a, MyStruct& b);

template <class Protocol_>
uint32_t MyStruct::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // cpp2
