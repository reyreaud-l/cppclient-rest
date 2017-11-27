#include "cppclient/connection.hh"

namespace cppclient
{
Connection::Connection()
{
  handler = curl_easy_init();
  if (!handler)
  {
    std::cerr << "Failed to curl easy init\n";
  }
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

  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

Response Connection::post(std::string url, std::string postfields)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, postfields.c_str());

  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

Response Connection::put(std::string url, std::string file)
{
  purge_content();
  struct stat file_info;

  // TODO: Add error checking
  stat(file.c_str(), &file_info);
  FILE* file_ptr = std::fopen(file.c_str(), "r");

  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(handler, CURLOPT_UPLOAD, 1L); 
  // Set file to upload and indicate it's size
  curl_easy_setopt(handler, CURLOPT_READDATA, file_ptr);
  curl_easy_setopt(handler, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);

  std::fclose(file_ptr);
  return Response(body, header, success, http_code);
}

Response Connection::del(std::string url, std::string postfields)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, postfields.c_str());

  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

Response Connection::patch(std::string url, std::string postfields)
{
  purge_content();
  set_url(url);
  set_default_callback();
  curl_easy_setopt(handler, CURLOPT_CUSTOMREQUEST, "PATCH");
  curl_easy_setopt(handler, CURLOPT_POSTFIELDS, postfields.c_str());

  CURLcode success = curl_easy_perform(handler);
  curl_easy_getinfo(handler, CURLINFO_RESPONSE_CODE, &http_code);
  return Response(body, header, success, http_code);
}

void Connection::purge_content()
{
  http_code = 0;
  body = "";
  header = "";
}

void Connection::set_url(std::string url)
{
  curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
}

void Connection::set_default_callback()
{
  curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, curl_string_callback);
  curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, curl_string_callback);
  curl_easy_setopt(handler, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(handler, CURLOPT_HEADERDATA, &header);
}

}
