#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Camera.h"
#include "cinder/CinderMath.h"
#include "cinder/Cinder.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/Callback.h"
#include "cinder/audio/PcmBuffer.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "RtMidi.h"
#include "LightOrgan.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class lightorganApp : public AppBasic {
  public:
	void setup();
    void midiIn( double deltatime, std::vector<unsigned char> *message, void *userData );
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();

    LightOrgan * organ;
};

void lightorganApp::setup()
{
    organ = new LightOrgan();
    audio::Output::play( audio::createCallback( organ, &LightOrgan::generateAudio, true ) );
}

void lightorganApp::midiIn( double deltatime, std::vector<unsigned char> *message, void *userData )
{
    unsigned char type = (*message)[0];
    unsigned char key = message->size() > 1 ? (*message)[1] : 0;
    unsigned char velocity = message->size() > 2 ? (*message)[2] : 0;

    if ( type == 176 ) { // control
        organ->control( key, velocity );
    } else if ( type == 144 ) { // key
        organ->toneOn( key, velocity );
    } else if ( type == 224 ) { // pitch

    }
}

void lightorganApp::keyDown( KeyEvent event )
{
    unsigned char key = event.getChar();
    organ->toneOn( key, 80 );
}

void lightorganApp::keyUp( KeyEvent event )
{
    unsigned char key = event.getChar();
    organ->toneOn( key, 0 );
}

void lightorganApp::mouseDown( MouseEvent event )
{
}

void lightorganApp::update()
{
}

void lightorganApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

AppBasic *lightorgan;

void midiIn( double deltatime, std::vector<unsigned char> *message, void *userData )
{
    ((lightorganApp *) lightorgan)->midiIn( deltatime, message, userData );
}

int main( int argc, char * const argv[] ) 
{
    AppBasic::prepareLaunch();							
    lightorgan = new lightorganApp();
    Renderer *ren = new RendererGl();							
    std::string title("yellow");

    bool midiEnabled = true;
    RtMidiIn * midiin = 0;

    try {
        midiin = new RtMidiIn();
    } catch ( RtError &error ) {
        error.printMessage();
        midiEnabled = false;
    }

    if ( midiEnabled ) {
        try {
            midiin->openPort( 0 );
        } catch ( RtError &error ) {
            error.printMessage();
            delete midiin;
        }

        midiin->setCallback( &midiIn );
        midiin->ignoreTypes( false, false, true );
    }

    AppBasic::executeLaunch( lightorgan, ren, title.c_str(), argc, argv );
    AppBasic::cleanupLaunch();								

    if ( midiEnabled ) {
        delete midiin;
    }

    return 0;															
}



