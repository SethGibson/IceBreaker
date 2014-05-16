#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Wordicle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class IceBreakerApp : public AppNative {
public:
	void setup();
	void mouseMove( MouseEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	vector<Wordicle> mWords;
};

void IceBreakerApp::setup()
{
}

void IceBreakerApp::mouseDown( MouseEvent event )
{
}

void IceBreakerApp::update()
{
}

void IceBreakerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( IceBreakerApp, RendererGl )
