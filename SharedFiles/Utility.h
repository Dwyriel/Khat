#ifndef KHAT_UTILITY_H
#define KHAT_UTILITY_H

#include <cstdint>
#include <string>

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> convertToUnsignedInteger(const std::string &string, uint64_t maxValueAllowed) {
    char *lastReadChar;
    uint64_t conversion = strtoull(string.c_str(), &lastReadChar, 10);
    if (*lastReadChar != '\0')
        return 0;
    if (conversion > maxValueAllowed)
        return 0;
    return (T) conversion;
}

#endif //KHAT_UTILITY_H
