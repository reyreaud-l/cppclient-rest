#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "cppclient/connection.hh"

TEST_CASE("Check basic connection function", "[connection]")
{
  cppclient::Connection myconnec;
  SECTION("GET")
  {
    auto resp = myconnec.get(std::string("localhost:8000"));
    REQUIRE(resp.get_body() == "get_success");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("POST")
  {
    auto resp = myconnec.post(std::string("localhost:8000"), std::string(""));
    REQUIRE(resp.get_body() == "post_success");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("DELETE")
  {
    auto resp = myconnec.del(std::string("localhost:8000"), std::string(""));
    REQUIRE(resp.get_body() == "delete_success");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("PATCH")
  {
    auto resp = myconnec.patch(std::string("localhost:8000"), std::string(""));
    REQUIRE(resp.get_body() == "patch_success");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }

  SECTION("PUT")
  {
    auto resp = myconnec.put(std::string("localhost:8000"), std::string("../../test/testfile.txt"));
    REQUIRE(resp.get_body() == "put_success");
    REQUIRE(resp.get_curlcode() == 0);
    REQUIRE(resp.get_returncode() == 200);
  }
}
