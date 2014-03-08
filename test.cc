// Inspired by:
// http://stackoverflow.com/questions/2687143/json-spirit-good-examples-of-unpacking-a-json-string
// http://markharrison.net/stackoverflow/t2-json.cpp

#include <iostream>
#include <string>

#include "json_spirit.h"
#include "json_spirit_stream_reader.h"

template<typename T_OSTREAM> void stringify(const json_spirit::Value &v, T_OSTREAM& os);

template<typename T_OSTREAM> void stringify_array(const json_spirit::Value &v, T_OSTREAM& os) {
  os << '[';
  const json_spirit::Array& a = v.get_array();
  for (size_t i = 0; i < a.size(); ++i) {
    if (i) {
      os << ',';
    }
    stringify(a[i], os);
  }
  os << ']';
}

template<typename T_OSTREAM> void stringify_object(const json_spirit::Value &v, T_OSTREAM& os) {
  os << '{';
  const json_spirit::Object& o = v.get_obj();
  for (size_t i = 0; i < o.size(); ++i) {
    if (i) {
      os << ',';
    }
    const json_spirit::Pair& p = o[i];
    os << '"' << p.name_ << '"' << ':';
    stringify(p.value_, os);
  }
  os << '}';
}

template<typename T_OSTREAM> void stringify_null(const json_spirit::Value &v, T_OSTREAM& os) {
  os << "null";
}

template<typename T_OSTREAM> void stringify_string(const std::string& s, T_OSTREAM& os) {
  os << '"' << s << '"';
}

template<typename T, typename T_OSTREAM> void stringify_primitive(const json_spirit::Value &v, T_OSTREAM& os) {
  os << v.get_value<T>();
}

template<typename T_OSTREAM> void stringify_unknown(T_OSTREAM& os) {
  os << '?';
}

template<typename T_OSTREAM> void stringify(const json_spirit::Value &v, T_OSTREAM& os) {
  switch(v.type()) {
    case json_spirit::obj_type:   stringify_object<T_OSTREAM>(v, os); break;
    case json_spirit::array_type: stringify_array<T_OSTREAM>(v, os); break;
    case json_spirit::str_type:   stringify_string<T_OSTREAM>(v.get_value<std::string>(), os); break;
    case json_spirit::bool_type:  stringify_primitive<bool, T_OSTREAM>(v, os); break;
    case json_spirit::int_type:   stringify_primitive<int, T_OSTREAM>(v, os); break;
    case json_spirit::real_type:  stringify_primitive<double, T_OSTREAM>(v, os); break;
    case json_spirit::null_type:  stringify_null(v, os); break;
    default:                      stringify_unknown(os); break;
  }
}

int main() {
  json_spirit::Stream_reader<std::istream, json_spirit::Value> reader(std::cin);
  json_spirit::Value value;
  while (reader.read_next(value)) {
    std::ostringstream os;
    stringify(value, os);
    std::cout << os.str() << std::endl;
  }
}
