#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

#define CRYPT 1
#define DECRYPT -1

std::vector< char > createKM ( const std::string key);
std::string playfair(std::string text , const std::string key, int crypt);
