#ifndef REFERENCE_COUNTING_H
#define REFERENCE_COUNTING_H

#include <unordered_map>

extern std::unordered_map<void *, int> references;

#endif //REFERENCE_COUNTING_H