#include "LightOrgan.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/audio/PcmBuffer.h"
#include "math.h"
#include <map>

using namespace ci;
using namespace std;

#define HEXAGON 0.866

LightOrgan::LightOrgan()
    : cap(0.8f),
      basis(30.0f)
{
    vector<float> tones;
    for ( int r = 0; r < 19; r++ ) {
        tones.push_back( pow( 2.0f, r / 19.0f ) );
    }
    scale = Scale( tones );
}

void LightOrgan::toneOn( unsigned char key, unsigned char velocity ) 
{
    std::map<unsigned char, LightTone>::iterator tone = tones.find( key );
    if ( tone == tones.end() ) {
        if ( velocity > 0 ) {
            LightTone light = LightTone( scale.tone( key ) * basis, velocity / 128.0f );
            tones.insert( std::pair<unsigned char, LightTone>( key, light ) );
        }
    } else {
        if ( velocity == 0 ) {
            tone->second.off();
        } else {
            if ( tone->second.over ) tone->second.over = false;
            tone->second.point( velocity / 128.0f, 0.0001f );
        }
    }
}

void LightOrgan::control( unsigned char code, unsigned char velocity ) 
{

}

void LightOrgan::generateAudio( uint64_t offset, uint32_t count, ci::audio::Buffer32f *buffer )
{
    float cycle;
    for ( uint32_t index = 0; index < count; index++ ) {
        buffer->mData[index*2] = 0;
        buffer->mData[index*2+1] = 0;
        for ( map<unsigned char, LightTone>::iterator tone = tones.begin(); tone != tones.end(); tone++ ) {
            if ( tone->second.complete ) {
                tones.erase( tone );
            } else {
                cycle = tone->second.cycle();
                buffer->mData[index*2] += cycle;
                buffer->mData[index*2+1] += cycle;
            }
        }
        buffer->mData[index*2] *= cap;
        buffer->mData[index*2+1] *= cap;
    }
}
