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
	mPXC.EnableImage(PXCImage::COLOR_FORMAT_RGB24);
	mPXC.EnableFaceLocation();
	mPXC.Init();
}

void IceBreakerApp::mouseMove( MouseEvent event )
{
}

void IceBreakerApp::update()
{
	Vec2f cFacePos, cFaceSize;
	if(mPXC.AcquireFrame(true))
	{
		PXCFaceAnalysis *cFace = mPXC.QueryFace();
		PXCFaceAnalysis::Detection *cFaceDetection = cFace->DynamicCast<PXCFaceAnalysis::Detection>();
		for(int fi=0;;++fi)
		{
			pxcUID cFId;
			pxcU64 cTs;
			if(cFace->QueryFace(fi,&cFId,&cTs)<PXC_STATUS_NO_ERROR)
				break;

			PXCFaceAnalysis::Detection::Data cData;
			cFaceDetection->QueryData(cFId, &cData);
			PXCRectU32 cFaceRect = cData.rectangle;
			float cSizeX = cFaceRect.w*0.5f;
			float cSizeY = cFaceRect.h*0.5f;
			cFacePos.x = cFaceRect.x+cSizeX;
			cFacePos.y = cFaceRect.y+cSizeY;
			cFaceSize.set(cSizeX,cSizeX);

		}
		PXCImage *cImg = mPXC.QueryImage(PXCImage::IMAGE_TYPE_COLOR);
		PXCImage::ImageData cData;
		if(cImg->AcquireAccess(PXCImage::ACCESS_READ, &cData)>=PXC_STATUS_NO_ERROR)
		{
			mRgb = gl::Texture(cData.planes[0], GL_BGR,640,480);
			cImg->ReleaseAccess(&cData);
		}

		mPXC.ReleaseFrame();
	}
	mWords->SetFaceCenter(cFacePos);
	mWords->SetFaceSize(cFaceSize);
	mWords->Step();
}

void IceBreakerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::color(Color::white());
	gl::draw(mRgb, Vec2f::zero());
	mWords->Display();
}

void IceBreakerApp::quit()
{
	delete mWords;
	mPXC.Close();
}

CINDER_APP_NATIVE( IceBreakerApp, RendererGl )
