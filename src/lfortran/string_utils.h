#ifndef LFORTRAN_STRING_UTILS_H
#define LFORTRAN_STRING_UTILS_H

#include <string>
#include <vector>

namespace LFortran
{


bool startswith(const std::string &s, const std::string &e);
bool endswith(const std::string &s, const std::string &e);
std::vector<std::string> split(const std::string &s);
std::string join(const std::string j, const std::vector<std::string> &v);
std::vector<std::string> slice(const std::vector<std::string> &v,
        int start=0, int end=-1);

// Replaces all occurrences of `regex` (a regular expression, must escape
// special characters) with `replace`
std::string replace(const std::string &s,
    const std::string &regex, const std::string &replace);


} // namespace LFortran




#endif // LFORTRAN_STRING_UTILS_H
