#pragma once

#include <string>
#include <curl/curl.h>

#include "json.hpp"

namespace cppclient
{
using json = nlohmann::json;
/** @class Response
 *  @brief Represent a response from a request.
 */
class Response
{
  public:
    Response(std::string, std::string, CURLcode, long);

    /** @brief Return the body of the response
     */
    std::string inline get_body()
    {
      return this->body;
    }

    /** @brief Return the body of the response as a json object
     */
    json inline get_body_json()
    {
      return json::parse(body);
    }

    /** @brief Return the header of the response
     */
    std::string inline get_header()
    {
      return this->header;
    }

    /** @brief Return the curlcode form libcurl
     *  @todo    Check CURLcode in the Connection and either raise an exception or create
     *           an according response with an explicit error message.
     */
    CURLcode inline get_curlcode()
    {
      return this->curlcode;
    }

    /** @brief Return the HTTP returncode received
     */
    long inline get_returncode()
    {
      return this->returncode;
    }

  protected:
    std::string body;
    std::string header;
    CURLcode curlcode;
    long returncode;

};
}

