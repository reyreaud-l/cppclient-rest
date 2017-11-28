#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <sys/stat.h>
#include <set>

#include "cppclient/cppclient.hh"

namespace cppclient
{
/** class Connection
 *  brief Represent a connection using a single curl handler. Should not be shared between threads.
 *  details The class uses a single curl handler and keep state of the last request made
 *          using the handler. Due to libcurl handler not being thread safe, an instance
 *          of this class should not be shared between threads.
 *
 *  \todo Add overloading on basic method get/post/...
 *       Check that connection free the resouces used by libcurl
 *
 *
 */
class Connection
{
  public:
  Connection();
  ~Connection();
  void reset();
  Response get(std::string);
  Response post(std::string, std::string);
  Response del(std::string, std::string);
  Response patch(std::string, std::string);
  Response put(std::string, FILE*);

  void auth_password(std::string);
  void auth_username(std::string);
  void auth(std::string, std::string);

  void add_header(const std::string head);
  void add_json_headers();

  void set_timeout(unsigned int);
  void set_redirects(unsigned int);

  private:
  CURL* handler;
  std::string body;
  std::string header;
  long http_code;
  std::set<std::string> headers;

  Response curl_perform();

  void generate_headers();
  void set_default_callback();
  void set_url(std::string);
  void purge_content();

};
}
