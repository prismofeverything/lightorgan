#pragma once
#include <vector>

class Scale {
 public:
    Scale( float ratios[] );
    unsigned int cardinality();

    std::vector<float> tones;
}
