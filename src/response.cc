#include "cppclient/response.hh"

namespace cppclient
{
Response::Response(std::string body, std::string head, CURLcode curlcode, long returncode)
{
  this->body = body;
  this->header = head;
  this->curlcode = curlcode;
  this->returncode = returncode;
  this->has_parsed_json = false;

  if (returncode != 200)
  {
    this->error = true;
    this->errormsg = std::to_string(returncode);
  }

  if (curlcode != CURLE_OK)
  {
    this->error = true;
    this->errormsg = std::string(curl_easy_strerror(this->curlcode));
  }
}

void Response::parse_jbody()
{
  if (!has_parsed_json)
    jbody = json::parse(body);
}

json Response::operator[](std::string key)
{
  parse_jbody();
  return jbody[key];
}

}
