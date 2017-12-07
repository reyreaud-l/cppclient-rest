#include "cppclient/helper.hh"

#include <iostream>

size_t curl_string_callback(void *contents, size_t size, size_t nmemb, void *s)
{
  auto str = static_cast<std::string*>(s);
  str->reserve(size * nmemb);
  str->append(static_cast<char*>(contents), size * nmemb);
  return size * nmemb;
}

size_t curl_string_read_callback(void *buffer, size_t size, size_t nmemb, std::string *s)
{
  return s->copy(static_cast<char*>(buffer), size * nmemb);
}

size_t file_size(FILE* file)
{
  fseek(file, 0, SEEK_END);
  return ftell(file);
}

std::string escape_json(const std::string& src)
{
  size_t len = src.length();
  std::string dst;
  dst = "\"";

  for (size_t i = 0; i < len; ++i) {
    std::string tmp;
    switch(src[i]) {
      case '\"':
        tmp = "\\\"";
        break;
      case '\\':
        tmp = "\\\\";
        break;
      case '\r':
        tmp = "\\r";
        break;
      case '\t':
        tmp = "\\t";
        break;
      case '\n':
        tmp = "\\n";
        break;
      default:
        tmp = src[i];
        break;
    };
    dst += tmp;
  }
  dst += '\"';
  return dst;
}
