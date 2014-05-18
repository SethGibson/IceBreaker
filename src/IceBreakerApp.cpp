#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Words.h"
#include "util_pipeline.h"

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
	void quit();

private:
	WordCloud *mWords;
	UtilPipeline mPXC;
	gl::Texture mRgb;
	Vec2f mMouse;
	Vec2f mHitBox;
};

void IceBreakerApp::prepareSettings(Settings *pSettings)
{
	pSettings->setWindowSize(640,480);
	pSettings->setTitle("Face Words");
}

void IceBreakerApp::setup()
{
	mHitBox = Vec2f(50,50);
	gl::TextureFontRef cFontRef = gl::TextureFont::create(Font("Times New Roman", 36));
	mWords = new WordCloud(cFontRef);
	mPXC.EnableImage(PXCImage::COLOR_FORMAT_RGB24);
	mPXC.EnableFaceLocation();
	mPXC.Init();
}

void IceBreakerApp::mouseMove( MouseEvent event )
{
	mMouse.set(event.getPos());
	mWords->SetTarget(mMouse);
}

void IceBreakerApp::update()
{
	if(mPXC.AcquireFrame(true))
	{
		PXCImage *cImg = mPXC.QueryImage(PXCImage::IMAGE_TYPE_COLOR);
		PXCImage::ImageData cData;
		if(cImg->AcquireAccess(PXCImage::ACCESS_READ, &cData)>=PXC_STATUS_NO_ERROR)
		{
			mRgb = gl::Texture(cData.planes[0], GL_BGR,640,480);
			cImg->ReleaseAccess(&cData);
		}
		mPXC.ReleaseFrame();
	}
	mWords->Step();
}

void IceBreakerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::color(Color::white());
	gl::draw(mRgb, Vec2f::zero());
	mWords->Display();

	gl::color(Color(0,1,0));
	gl::drawStrokedRect(Rectf(mMouse-mHitBox,mMouse+mHitBox));
}

void IceBreakerApp::quit()
{
	delete mWords;
	mPXC.Close();
}

CINDER_APP_NATIVE( IceBreakerApp, RendererGl )
