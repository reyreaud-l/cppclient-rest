#include "cppclient/helper.hh"

size_t curl_string_callback(void *contents, size_t size, size_t nmemb, void *s)
{
  ((std::string*)s)->append((char*)contents, size * nmemb);
  return size * nmemb;
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
