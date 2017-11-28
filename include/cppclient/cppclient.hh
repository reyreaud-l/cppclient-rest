#pragma once

#include <curl/curl.h>
#include <stdexcept>

#include "cppclient/response.hh"
#include "cppclient/connection.hh"
#include "cppclient/helper.hh"

namespace cppclient
{
static void init()
{
  auto code = curl_global_init(CURL_GLOBAL_ALL);
  if (code != CURLE_OK)
    throw std::runtime_error("Could not initialize curl");
}

static void cleanup()
{
  curl_global_cleanup();
}
}
