#include <cstdio>
#include <string>
#include "gtest/gtest.h"
#include "cppclient/cppclient.hh"

class ConnectionTest : public ::testing::Test
{
  protected:
  ConnectionTest()
  {
    cppclient::init();
    connec.add_json_headers();
    base = "http://httpbin.org";
  }

  virtual ~ConnectionTest()
  {
    cppclient::cleanup();
  }

  cppclient::Connection connec;
  std::string base;
};

TEST_F(ConnectionTest, ValidCreds)
{
  connec.auth("user", "passwd");
  auto resp = connec.get(base + "/basic-auth/user/passwd");
  EXPECT_EQ(resp.get_body(), "{\n  \"authenticated\": true, \n  \"user\": \"user\"\n}\n");
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, InvalidCreds)
{
  connec.auth("user", "h4ack3r");
  auto resp = connec.get(base + "/basic-auth/user/passwd");
  EXPECT_EQ(resp.get_body(), "");
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 401);
}
