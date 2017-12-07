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

  cppclient::Connection connec;
  std::string base;
};

TEST_F(ConnectionTest, Get)
{
  auto resp = connec.get(base + "/get");
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, Post)
{
  auto resp = connec.post(base + "/post", std::string("{\"key\" : \"value\"}"));
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, Delete)
{
  auto resp = connec.del(base + "/delete", std::string("{\"key\" : \"value\"}"));
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, Patch)
{
  auto resp = connec.patch(base + "/patch", std::string("{\"key\" : \"value\"}"));
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, PutString)
{
  auto resp = connec.put(base + "/put", std::string("abcd"));
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}

TEST_F(ConnectionTest, PutFile)
{
  FILE* file = fopen("../../test/testfile.txt", "r");
  EXPECT_TRUE(file != NULL);
  auto resp = connec.put(base + "/put", file);
  EXPECT_EQ(resp.get_curlcode(), 0);
  EXPECT_EQ(resp.get_returncode(), 200);
}
