#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Rand.h"
#include "cinder/audio/PcmBuffer.h"
#include "LightTone.h"
#include "Scale.h"
#include <map>

class LightOrgan {
 public:
    LightOrgan();
    void toneOn( unsigned char tone, unsigned char velocity );
    void control( unsigned char code, unsigned char velocity );
    void generateAudio( uint64_t offset, uint32_t count, ci::audio::Buffer32f *buffer );

    Scale scale;
    std::map<unsigned char, LightTone> tones;
    float cap;
    float basis;
};
