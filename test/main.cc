#include <string>
#include <iostream>
#include "cppclient/connection.hh"


int main(void)
{
  cppclient::Connection myconnec;
  auto resp = myconnec.get(std::string("https://loic-reyreaud.com"));
  std::cout << resp.get_body() << std::endl;
  std::cout << resp.get_header() << std::endl;
  std::cout << "CURL CODE: " << resp.get_curlcode() << std::endl;
  std::cout << "RESP CODE: " << resp.get_returncode() << std::endl;

  resp = myconnec.post(std::string("https://loic-reyreaud.com"), std::string(""));
  std::cout << resp.get_body() << std::endl;
  std::cout << resp.get_header() << std::endl;
  std::cout << "CURL CODE: " << resp.get_curlcode() << std::endl;
  std::cout << "RESP CODE: " << resp.get_returncode() << std::endl;

  resp = myconnec.del(std::string("https://loic-reyreaud.com"), std::string(""));
  std::cout << resp.get_body() << std::endl;
  std::cout << resp.get_header() << std::endl;
  std::cout << "CURL CODE: " << resp.get_curlcode() << std::endl;
  std::cout << "RESP CODE: " << resp.get_returncode() << std::endl;

  resp = myconnec.patch(std::string("https://loic-reyreaud.com"), std::string(""));
  std::cout << resp.get_body() << std::endl;
  std::cout << resp.get_header() << std::endl;
  std::cout << "CURL CODE: " << resp.get_curlcode() << std::endl;
  std::cout << "RESP CODE: " << resp.get_returncode() << std::endl;

  resp = myconnec.put(std::string("https://loic-reyreaud.com"), std::string("./testfile.txt"));
  std::cout << resp.get_body() << std::endl;
  std::cout << resp.get_header() << std::endl;
  std::cout << "CURL CODE: " << resp.get_curlcode() << std::endl;
  std::cout << "RESP CODE: " << resp.get_returncode() << std::endl;
  return 0;
}
