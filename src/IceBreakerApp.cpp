#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Words.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Words;

class IceBreakerApp : public AppNative {
public:
	void prepareSettings(Settings *pSettings);
	void setup();
	void mouseMove( MouseEvent event );
	void update();
	void draw();

private:
	WordCloud *mWords;
};

void IceBreakerApp::prepareSettings(Settings *pSettings)
{
	pSettings->setWindowSize(640,480);
	pSettings->setTitle("Face Words");
}

void IceBreakerApp::setup()
{
	gl::TextureFontRef cFontRef = gl::TextureFont::create(Font("Times New Roman", 36));
	mWords = new WordCloud(cFontRef);
}

void IceBreakerApp::mouseMove( MouseEvent event )
{
	Vec2f cTarget = Vec2f(event.getX(), event.getY());
	mWords->SetTarget(cTarget);
}

void IceBreakerApp::update()
{
	mWords->Step();
}

void IceBreakerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	mWords->Display();
}

CINDER_APP_NATIVE( IceBreakerApp, RendererGl )
