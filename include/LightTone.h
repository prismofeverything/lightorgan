#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <vector>

class LightTone {
 public:
    LightTone( float freq, float amp );
    void bound();
    float cycle();
    void point( float towards, float urgency );
    void off();

    float frequency;
    float amplitude;
    float level;
    float inertia;
    float target;
    float gradient;
    float history;
    bool over;
    bool complete;
};
