# cppclient-rest
Http client for c++. Depends on libcurl.

cppclient-rest follow KISS: Keep It Simple Stupid! No overhead or useless configuration
unless you need it.

## Features

- Basic Get/Post/Patch/Delete/Put requests
- Basic HTTP Auth handling
- Json send/receive
- Parsing json in Response.
- File upload with put requests.

And more to be added !

## Installing

No package yet, clone the source and build
```
$ git clone git@github.com:reyreaud-l/cppclient-rest.git
$ cd cppclient-rest
$ mkdir build && cd build
$ cmake ..
$ make && make install
```

## Usage

Doing a get request is dead simple:
```c++
#include <cppclient/cppclient.hh>
#include <iostream>


int main(void)
{
  cppclient::Connection connec;
  cppclient::Response response = connec.get("http://whatthecommit.com/index.txt");
  std::cout << response.get_body();
  return 0;
}
```

## Test

We use ctest shipped with cmake to run our tests. Simply run 
```
$ make test
```

in the your build directory
