cppclient-rest
==============

Http client for c++. Depends on libcurl.

cppclient-rest follow KISS: Keep It Simple Stupid! No overhead or useless configuration
unless you need it.

Features
-------

- Basic Get/Post/Patch/Delete/Put requests
- Basic HTTP Auth handling
- Json send/receive
- Parsing json in Response.
- File upload with put requests.

And more to be added !

Installing
----------

No package yet, clone the source and build
```
$ git clone git@github.com:reyreaud-l/cppclient-rest.git
$ cd cppclient-rest
$ mkdir build && cd build
$ cmake .. # For custom install dir: cmake -DCMAKE_INSTALL_PREFIX=/my/path ..
$ make && make install
```

To uninstall
```
$ make uninstall
```

Usage
-----

Doing a get request is dead simple:
```c++
#include <cppclient/cppclient.hh>
#include <iostream>


int main(void)
{
  cppclient::Connection conn;
  cppclient::Response response = conn.get("http://whatthecommit.com/index.txt");
  std::cout << response.get_body();
  return 0;
}
```

Here are some basics:
```c++
/* Connection Object */
conn.get("url");
conn.post("url", "payload"); // The payload can be json if add_json_headers is called
conn.delete("url", "payload");
conn.patch("url", "payload");
conn.put("url", myfile); // myfile is a FILE*

conn.auth_password("password"); // Set username for basic HTTP Auth
conn.auth_username("username"); // Set password for basic HTTP Auth
conn.auth("username", "password"); // Or set both at the same time

conn.add_header("myheader"); // Add an arbitraty header to be sent allong side the requests
conn.set_timeout(5); // Set a timeout for the requests
conn.set_redirects(5); // Set max number of redirects to follow
conn.reset(); // Get a connection clean it's state and underlying handler

/* Response object */
response.get_body(); // Return body of the request
response.get_header(); // Return header of the request

response.get_json_body(); // Return the body as a json object
response["data"]; // Return the json under the key "data" in the body of the response

response.is_error(); // Return true if there was an error
response.get_error(); // Return a string representing the error
response.get_returncode(); // Return the HTTP code of the request
response.get_curlcode(); // Return error code from curl, should be 0 unless connection problem
```

If you want more insight, build the doxygen doc with
```
make doc
```

Test
----

We use ctest shipped with cmake to run our tests. Simply run 
```
$ make test
```

in the your build directory
