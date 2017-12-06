#define CATCH_CONFIG_MAIN
#include <cstdio>
#include <string>
#include <iostream>
#include "catch.hpp"
#include "cppclient/cppclient.hh"

using json = nlohmann::json;

TEST_CASE("Check basic connection function with json objects", "[connection]")
{
  cppclient::init();
  cppclient::Connection connec;
  connec.add_json_headers();
  std::string base("http://httpbin.org");

  json data = {
    {"key", "value"}
  };

  SECTION("POST")
  {
    auto resp = connec.post(base + "/post", data);
    REQUIRE(resp["data"] == data.dump());
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("PUT")
  {
    auto resp = connec.put(base + "/put", std::string("a"));
    REQUIRE(resp["data"] == data.dump());
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }
}
