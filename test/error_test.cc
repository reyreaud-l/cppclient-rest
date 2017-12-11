#include <cstdio>
#include <string>
#include <curl/curl.h> // Required for curl error code

#include "gtest/gtest.h"
#include "cppclient/cppclient.hh"


class ConnectionTest : public ::testing::Test
{
  protected:
  ConnectionTest()
  {
    cppclient::init();
    connec.add_json_headers();
    invalid_url = "invalid_url";
    base = "http://httpbin.org";
  }

  cppclient::Connection connec;
  std::string base;
  std::string invalid_url;
};

TEST_F(ConnectionTest, CURLError)
{
  auto resp = connec.get(invalid_url);
  EXPECT_TRUE(resp.is_error());
  EXPECT_EQ(resp.get_curlcode(), CURLE_COULDNT_RESOLVE_HOST);
  EXPECT_NE(resp.get_error(), "");
}

TEST_F(ConnectionTest, HTTPError)
{
  auto resp = connec.get(base + "/status/500");
  EXPECT_TRUE(resp.is_error());
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 500);
  EXPECT_EQ(resp.get_error(), "500");
}
