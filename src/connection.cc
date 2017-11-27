#include "cppclient/connection.hh"

namespace cppclient
{
Connection::Connection()
{
  this->handler = curl_easy_init();
  if (!this->handler)
  {
    std::cerr << "Failed to curl easy init\n";
  }
}

Connection::~Connection()
{
  curl_easy_cleanup(this->handler);
}


Response Connection::get(std::string url)
{
  std::string body;
  std::string header;
  long http_code;
  curl_easy_setopt(this->handler, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->handler, CURLOPT_WRITEFUNCTION, curl_string_callback);
  curl_easy_setopt(this->handler, CURLOPT_HEADERFUNCTION, curl_string_callback);
  curl_easy_setopt(this->handler, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(this->handler, CURLOPT_HEADERDATA, &header);
  CURLcode success = curl_easy_perform(this->handler);
  curl_easy_getinfo(this->handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

Response Connection::post(std::string url, std::string postfields)
{
  std::string body;
  std::string header;
  long http_code;
  curl_easy_setopt(this->handler, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->handler, CURLOPT_WRITEFUNCTION, curl_string_callback);
  curl_easy_setopt(this->handler, CURLOPT_HEADERFUNCTION, curl_string_callback);
  curl_easy_setopt(this->handler, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(this->handler, CURLOPT_HEADERDATA, &header);

  curl_easy_setopt(this->handler, CURLOPT_POSTFIELDS, postfields.c_str());
  CURLcode success = curl_easy_perform(this->handler);
  curl_easy_getinfo(this->handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

}
