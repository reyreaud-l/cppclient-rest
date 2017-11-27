#pragma once

#include <string>
#include <curl/curl.h>

namespace cppclient
{
class Response
{
  public:
    Response(std::string, std::string, CURLcode, long);

    std::string inline get_body()
    {
      return this->body;
    }

    std::string inline get_header()
    {
      return this->header;
    }

    CURLcode inline get_curlcode()
    {
      return this->curlcode;
    }

    long inline get_returncode()
    {
      return this->returncode;
    }

  private:
    std::string body;
    std::string header;
    CURLcode curlcode;
    long returncode;

};
}

