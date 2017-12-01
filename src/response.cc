#include "cppclient/response.hh"

namespace cppclient
{

Response::Response(std::string body, std::string head, CURLcode curlcode, long returncode)
{
  this->body = body;
  this->header = head;
  this->curlcode = curlcode;
  this->returncode = returncode;
}
}
