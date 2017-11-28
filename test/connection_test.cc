#define CATCH_CONFIG_MAIN
#include <cstdio>
#include <string>
#include "catch.hpp"
#include "cppclient/cppclient.hh"

TEST_CASE("Check basic connection function", "[connection]")
{
  cppclient::init();
  cppclient::Connection myconnec;
  myconnec.enable_json();
  std::string base("http://httpbin.org");

  SECTION("GET")
  {
    auto resp = myconnec.get(base + "/get");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("POST")
  {
    auto resp = myconnec.post(base + "/post", std::string("{\"key\" : \"value\"}"));
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("DELETE")
  {
    auto resp = myconnec.del(base + "/delete", std::string("{\"key\": \"value\""));
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("PATCH")
  {
    auto resp = myconnec.patch(base + "/patch", std::string("{\\\"key\\\": value"));
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("PUT")
  {
    FILE* file = fopen("../../test/testfile.txt", "r");
    auto resp = myconnec.put(base + "/put", file);
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
    fclose(file);
  }
  cppclient::cleanup();
}

TEST_CASE("Check auth", "[connection]")
{
  cppclient::init();
  cppclient::Connection myconnec;
  myconnec.enable_json();
  std::string base("http://httpbin.org");

  SECTION("Valid creds")
  {
    myconnec.auth("user", "passwd");
    auto resp = myconnec.get(base + "/basic-auth/user/passwd");
    REQUIRE(resp.get_body() == "{\n  \"authenticated\": true, \n  \"user\": \"user\"\n}\n");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("Invalid Creds")
  {
    myconnec.auth("user", "h4ck3r");
    auto resp = myconnec.get(base + "/basic-auth/user/passwd");
    REQUIRE(resp.get_body() == "");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 401);
  }

  cppclient::cleanup();
}
