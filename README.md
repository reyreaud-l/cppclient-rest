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
$ cmake ..
$ make && make install
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
conn.get("url");
// The payload can be json if add_json_headers is called
conn.post("url", "payload");
conn.delete("url", "payload");
conn.patch("url", "payload");
// myfile is a FILE*
conn.put("url", myfile);

// Set username for basic HTTP Auth
conn.auth_password("password");

// Set password for basic HTTP Auth
conn.auth_username("username");

// Or set both at the same time
conn.auth("username", "password");

// Add an arbitraty header to be sent allong side the requests
conn.add_header("myheader");

// Set a timeout for the requests
conn.set_timeout(5);

// Set max number of redirects to follow
conn.set_redirects(5);

// Get a connection clean it's state and underlying handler
conn.reset();


// Return either body, header or code of the response
response.get_body();
response.get_header();
response.get_returncode();

// Return error code from curl, should be 0 unless connection problem
response.get_curlcode();
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
