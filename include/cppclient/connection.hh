#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>

#include "cppclient/response.hh"
#include "cppclient/helper.hh"


namespace cppclient
{
class Connection
{
  public:
  Connection();
  ~Connection();
  Response get(std::string);
  Response post(std::string, std::string);
  Response del(std::string, std::string);
  Response patch(std::string, std::string);

  private:
  CURL* handler;
  std::string body;
  std::string header;
  long http_code;

  void set_default_callback();
  void set_url(std::string);

};
}
