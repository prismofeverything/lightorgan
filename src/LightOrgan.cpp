#include "LightOrgan.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/audio/PcmBuffer.h"
#include <map>

using namespace ci;
using namespace std;

#define HEXAGON 0.866

LightOrgan::LightOrgan()
{

}

void LightOrgan::toneOn( unsigned char tone, unsigned char velocity ) 
{

}

void LightOrgan::control( unsigned char code, unsigned char velocity ) 
{

}

void LightOrgan::generateAudio( uint64_t offset, uint32_t count, ci::audio::Buffer32f *buffer )
{
    for ( uint32_t index = 0; index < count; index++ ) {
        buffer->mData[index*2] = 0;
        buffer->mData[index*2+1] = 0;
    }
}
