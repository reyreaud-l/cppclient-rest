#pragma once

#include <string>
#include <cstdio>

size_t curl_string_callback(void*, size_t, size_t, void*);
size_t file_size(FILE* file);
std::string escape_json(const std::string&);
