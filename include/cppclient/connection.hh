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

  private:
  CURL* handler;

};
}
