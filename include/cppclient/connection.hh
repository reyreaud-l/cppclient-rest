#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <sys/stat.h>
#include <set>

#include "cppclient/cppclient.hh"
#include "json.hpp"

namespace cppclient
{
using json = nlohmann::json;
/** @class Connection
 *  @brief Represent a connection using a single curl handler. Should not be shared between threads.
 *  @details The class uses a single curl handler and keep state of the last request made
 *          using the handler. Due to libcurl handler not being thread safe, an instance
 *          of this class should not be shared between threads.
 *
 *  @todo Add overloading on basic method get/post/...
 *       Check that connection free the resouces used by libcurl
 *
 *
 */
class Connection
{
  public:

  /** @brief Build a Connection object. Under the hood create the libcurl
   *        handler the class will be using.
   */
  Connection();

  /** @brief Destroy the Connection object. Frees the ressource used by libcurl
   */
  ~Connection();

  /** @brief Perform an http get on the given url
   *  @param url
   *  @return Response object resulting of the http get
   */
  Response get(std::string);

  /** @brief Perform an http post on the given url
   *  @param url
   *  @param data
   *  @return Response object resulting of the http post
   */
  Response post(std::string, std::string);

  /** @brief Perform an http post on the given url with a json payload
   *  @param url
   *  @param json data
   *  @return Response object resulting of the http post
   */
  Response post(std::string, json);

  /** @brief Perform an http delete on the given url
   *  @param url
   *  @param data
   *  @return Response object resulting of the http delete
   */
  Response del(std::string, std::string);

  /** @brief Perform an http patch on the given url
   *  @param url
   *  @param data
   *  @return Response object resulting of the http patch
   */
  Response patch(std::string, std::string);

  /** @brief Perform an http put on the given url to upload a file.
   *  @param url
   *  @param file to upload.
   *  @return Response object resulting of the http put
   */
  Response put(std::string, FILE*);

  /** @brief Set the password in the handler for http basic auth.
   *  @param password
   */
  void auth_password(std::string);

  /** @brief Set the username in the handler for http basic auth.
   *  @param username
   */
  void auth_username(std::string);

  /** @brief Set username and password in the handler for http basic auth.
   *  @param password
   *  @param username
   */
  void auth(std::string, std::string);

  /** @brief Add a custom header in the handler.
   *  @param header
   */
  void add_header(const std::string);

  /** @brief Add predetermined json header to send json data through the handler.
   */
  void add_json_headers();

  /** @brief Set a timeout for the requests in the libcurl handler.
   *  @param timeout in seconds
   */
  void set_timeout(unsigned int);

  /** @brief Set a maximum number of redirection to follow when doing a request.
   */
  void set_redirects(unsigned int);

  /** @brief Fully reset the underlying handler and state retained by the object.
   */
  void reset();

  private:
  /** @brief The underlying libcurl handler.
   */
  CURL* handler;

  /** @brief Body of the last request made through the handler.
   */
  std::string body;

  /** @brief Header of the last request made through the handler.
   */
  std::string header;

  /** @brief Return code of the last request made through the handler.
   */
  long http_code;

  /** @brief Set of all the headers used by the connection.
   *  @details We use a set of string to remember which headers are used by the handler.
   *           We can manipulate our headers remove/add some and regenerate the libcurl
   *           list to update the used headers.
   */
  std::set<std::string> headers;

  /** @brief Perform the request registered in the handler and return a Reponse object
   *         corresponding of the result of the request.
   */
  Response curl_perform();

  /** @brief Regenerate the handlers header based on our set of headers.
   */
  void generate_headers();

  /** @brief Setup default's callback in the handler to get the results in std::string.
   */
  void set_default_callback();

  /** @brief Setup the url in the handler
   */
  void set_url(std::string);

  /** @brief Reset to default the data saved from the last request.
   */
  void purge_content();
};
}
