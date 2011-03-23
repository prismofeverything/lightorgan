#include "math.h"
#include "Scale.h"

using namespace std;

Scale::Scale()
{
    tones = vector<float>();
    tones.push_back( 1.0f );
}

Scale::Scale( vector<float>& ratios )
{
    tones = ratios;
}

unsigned int Scale::cardinality()
{
    return tones.size();
}

float Scale::tone( int key )
{
    int octave = key / tones.size();
    int tone = key % tones.size();
    return pow( 2, octave ) * tones[tone];
}
