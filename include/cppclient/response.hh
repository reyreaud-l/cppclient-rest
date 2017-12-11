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
      parse_jbody();
      return jbody;
    }

    /** @brief Return the header of the response
     */
    std::string inline get_header()
    {
      return this->header;
    }

    /** @brief Return the curlcode form libcurl
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

    /** @brief Return a string representing an error. Will return the http code as a
     *         string if it is an http error, otherwise curl error as a string
     *
     *         If no error the string will be empty string
     */
    std::string inline get_error()
    {
      return this->errormsg;
    }

    /** @brief Return true if there was an error during transmission
     */
    bool inline is_error()
    {
      return this->error;
    }

    /* @brief Access a field of the response parsed as json
     */
    json operator[](std::string);

  protected:
    std::string body;
    std::string header;
    std::string errormsg;

    CURLcode curlcode;
    long returncode;

    bool has_parsed_json;
    bool error;

    json jbody;

    void parse_jbody();

};
}

