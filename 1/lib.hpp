#include <vector>
#include <string>
#include <format>
#include <algorithm>

char *encode(int *array, size_t size_array, const char *name_array);

char *encode(int *array, size_t size_array, const char *name_array, size_t size_name);

std::string encode(std::vector<int> array, std::string name_array);

std::vector<int> decode(std::string urlencoded, std::string &name_array);

int *decode(const char *urlencoded, size_t &size_array, char *&name_array_c);

int *decode(const char *urlencoded, size_t size, size_t &size_array, char *&name_array_c);
