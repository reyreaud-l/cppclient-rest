#include "cppclient/connection.hh"

namespace cppclient
{
Connection::Connection()
{
  handler = curl_easy_init();
  if (!handler)
    std::cerr << "Failed to curl easy init\n";
}

Connection::~Connection()
{
  curl_easy_cleanup(handler);
}

Response Connection::get(std::string url)
{
  purge_content();
  set_url(url);
  set_default_callback();

  return curl_perform();
}

Response Connection::post(std::string url, std::string data)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data.c_str());

  return curl_perform();
}

Response Connection::post(std::string url, json data)
{
  return post(url, data.dump());
}

Response Connection::put(std::string url, std::string data)
{
  purge_content();
  set_url(url);
  set_default_callback();

  add_header("Transfer-Encoding: chunked");
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(handler, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(handler, CURLOPT_READFUNCTION, curl_string_callback);
  curl_easy_setopt(handler, CURLOPT_READDATA, data.c_str());
  curl_easy_setopt(handler, CURLOPT_INFILESIZE_LARGE, data.length());

  return curl_perform();
}

Response Connection::put(std::string url, json data)
{
  return put(url, data.dump());
}

Response Connection::put(std::string url, FILE* file)
{
  purge_content();
  set_url(url);
  set_default_callback();

  add_header("Transfer-Encoding: chunked");
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(handler, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(handler, CURLOPT_READDATA, file);
  curl_easy_setopt(handler, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_size(file));

  return curl_perform();
}

Response Connection::del(std::string url, std::string data)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data.c_str());

  return curl_perform();
}

Response Connection::patch(std::string url, std::string data)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PATCH");
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, data.c_str());
  return curl_perform();
}

/** @details Make the curl_easy_perform call and uses body, header, http_code attributes
 *           to create a Response object corresponding. http_code is obtained with
 *           curl_easy_getinfo.
 *
 */
Response Connection::curl_perform()
{
  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);
  auto tmp =  Response(body, header, success, http_code);
  return tmp;
}

void Connection::add_header(const std::string header)
{
  headers.insert(header);
  generate_headers();
}

/** @details The headers are needed to use json, otherwise libcurl will consider the data
 *           sent to be the key to "" like { data : "" }
 */
void Connection::add_json_headers()
{
  headers.insert("Accept: application/json");
  headers.insert("Content-Type: application/json");
  headers.insert("charsets: utf-8");
  generate_headers();
}

void Connection::set_timeout(unsigned int timeout)
{
  curl_easy_setopt(handler, CURLOPT_TIMEOUT, timeout);
}

void Connection::set_redirects(unsigned int redirs)
{
  curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, redirs);
}

void Connection::generate_headers()
{
  struct curl_slist *curlheaders = NULL;
  for (auto it = headers.begin(); it != headers.end(); it++)
    curlheaders = curl_slist_append(curlheaders, it->c_str());
  curl_easy_setopt(handler, CURLOPT_HTTPHEADER, curlheaders);
}

void Connection::auth_password(std::string password)
{
  curl_easy_setopt(handler, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
  curl_easy_setopt(handler, CURLOPT_PASSWORD, password.c_str());
}

void Connection::auth_username(std::string username)
{
  curl_easy_setopt(handler, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
  curl_easy_setopt(handler, CURLOPT_USERNAME, username.c_str());
}

void Connection::auth(std::string username, std::string password)
{
  auth_password(password);
  auth_username(username);
}

void Connection::purge_content()
{
  http_code = 0;
  body = "";
  header = "";
}

void Connection::reset()
{
  curl_easy_reset(handler);
  headers.clear();
}

void Connection::set_url(std::string url)
{
  curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
}

/** @details Set the callback CURLOPT_WRITEFUNCTION and CURLOPT_HEADERFUNCTION to
 *           curl_string_callback. Set body and header attributes to receive the
 *           corresponding data from libcurl.
 */
void Connection::set_default_callback()
{
  curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, curl_string_callback);
  curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, curl_string_callback);
  curl_easy_setopt(handler, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(handler, CURLOPT_HEADERDATA, &header);
}
}
