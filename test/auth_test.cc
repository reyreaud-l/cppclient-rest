#include <string>
#include "catch.hpp"
#include "cppclient/cppclient.hh"

TEST_CASE("Check auth", "[connection]")
{
  cppclient::init();
  cppclient::Connection connec;
  connec.add_json_headers();
  std::string base("http://httpbin.org");

  SECTION("Valid creds")
  {
    connec.auth("user", "passwd");
    auto resp = connec.get(base + "/basic-auth/user/passwd");
    REQUIRE(resp.get_body() == "{\n  \"authenticated\": true, \n  \"user\": \"user\"\n}\n");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("Invalid Creds")
  {
    connec.auth("user", "h4ck3r");
    auto resp = connec.get(base + "/basic-auth/user/passwd");
    REQUIRE(resp.get_body() == "");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 401);
  }

  cppclient::cleanup();
}
