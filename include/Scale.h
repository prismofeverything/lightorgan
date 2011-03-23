#pragma once
#include <vector>

class Scale {
 public:
    Scale();
    Scale( std::vector<float>& ratios );
    unsigned int cardinality();
    float tone( int key );

    std::vector<float> tones;
};
