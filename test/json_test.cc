#include <string>
#include "gtest/gtest.h"
#include "cppclient/cppclient.hh"
#include <iostream>

using json = nlohmann::json;

class ConnectionTest : public ::testing::Test
{
  protected:
  ConnectionTest()
  {
    cppclient::init();
    connec.add_json_headers();
    base = "http://httpbin.org";
    data = {
      {"key", "value"}
    };
  }

  cppclient::Connection connec;
  std::string base;
  json data;
};

TEST_F(ConnectionTest, JsonPost)
{
  auto resp = connec.post(base + "/post", data);
  EXPECT_EQ(resp["data"], data.dump());
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, JsonPut)
{
  auto resp = connec.put(base + "/put", data);
  EXPECT_EQ(resp["data"], data.dump());
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}
