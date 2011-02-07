#include "LightTone.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace std;

#define TAU 6.2831853071795862f
#define FREQUENCY_TRANSLATION 0.0001424542
#define AMPLITUDE_EPSILON 0.001f

LightTone::LightTone( float freq, float amp ) 
  : frequency( freq * FREQUENCY_TRANSLATION ), 
    amplitude( 0.0f ), 
    target( amp ),
    gradient( 0.0001f ),
    level( 0.0f ), 
    history( 0.0f ),
    inertia( 1.0f ),
    over( false ),
    complete( false )
{
    bound();
}

void LightTone::bound()
{
    if ( frequency <= 0.0f ) frequency = 0.0f;
    if ( frequency >= 1.0f ) frequency = 1.0f;
    if ( amplitude <= 0.0f ) amplitude = 0.0f;
    if ( amplitude >= 1.0f ) amplitude = 1.0f;
}

float LightTone::cycle() 
{
    inertia -= level * frequency;
    level += inertia * frequency;

    if ( ( history <= 0.0f && level > 0.0f ) || ( history >= 0.0f && level < 0.0f ) ) {
        amplitude += (target - amplitude) * gradient;

        if ( over ) {
            if ( abs( amplitude - target ) < AMPLITUDE_EPSILON ) {
                amplitude = 0.0f;
                complete = true;            
            }
        }
    }

    return level * amplitude;
}

void LightTone::point( float towards, float urgency )
{
    target = towards;
    gradient = urgency;
}

void LightTone::off()
{
    over = true;
    point( 0.0f, 0.0001f );
}
