#include "Words.h"
#include "cinder/Rand.h"

string S_WORDS[] = {"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dogs"};
int S_COUNT = 9;
namespace Words
{
	Wordicle::Wordicle(const gl::TextureFontRef &pFont):mFont(pFont)
	{
		int cid = randInt(S_COUNT);		
		mPosition = Vec2f::zero();
		mVelocity = Vec2f::zero();
		mWord = S_WORDS[cid];
		mSpeed = mWord.length()+randFloat(5,10);
		mColor = ColorA(randFloat(0.1f, 0.5f), randFloat(0.1f, 0.5f), randFloat(0.1f, 0.5f), randFloat(0.1f,0.5f));
		mStringSize = mFont->measureString(mWord);
	}

	Wordicle::Wordicle(string pWord, Vec2f pPosition, Vec2f pOffset, const gl::TextureFontRef &pFont):mFont(pFont)
	{
		mPosition = pPosition;
		mVelocity = Vec2f::zero();
		mWord = pWord;
		mSpeed = mWord.length()*randFloat(1.5,4);
		mColor = ColorA(randFloat(0.25f, 0.8f), randFloat(0.25f, 0.8f), randFloat(0.25f, 0.8f), randFloat(0.75f,1.f));
		mStringSize = mFont->measureString(mWord);
		mOffset = pOffset;
	}

	Wordicle::~Wordicle()
	{
	}

	void Wordicle::Step(Vec2f &pFaceCenter, Vec2f &pFaceSize)
	{
		//pTarget is actual location(mouse or face rect center)
		float cx = mOffset.x*pFaceSize.x;
		if(mOffset.x<0)
			cx -= mStringSize.x;
		float cy = (mOffset.y*(mStringSize.y*3))+pFaceSize.y;
		mVelocity=(pFaceCenter+Vec2f(cx,cy))-mPosition;
		mVelocity.limit(mSpeed*0.325f);
		mPosition+=mVelocity;
	}

	void Wordicle::Display()
	{
		gl::color(mColor);
		mFont->drawString(mWord, mPosition);
	}

	WordCloud::WordCloud(gl::TextureFontRef pFont)
	{
		mFont = pFont;

		for(int i=0;i<S_COUNT;++i)
		{

			float cx = i<=S_COUNT*0.5f? -1:1;
			float cy = i<=S_COUNT*0.5f? lmap<float>(i,0,S_COUNT*0.5f,0,-1):lmap<float>(i,S_COUNT*0.5f,S_COUNT,-1,0);
			Vec2f cOffset(cx,cy);
			mWords.push_back(Wordicle(S_WORDS[i], Vec2f::zero(), cOffset, mFont));
		}
		mFaceCenter = Vec2f::zero();
		mFaceSize = Vec2f::zero();
	}

	WordCloud::WordCloud(vector<Wordicle> pWords)
	{
	}

	WordCloud::WordCloud(vector<string> pWords)
	{
	}

	WordCloud::WordCloud(string pWords[], int pCount)
	{
	}

	WordCloud::~WordCloud()
	{
	}

	void WordCloud::AddWord()
	{
	}

	void WordCloud::Step()
	{
		for(auto wit=mWords.begin();wit!=mWords.end();++wit)
			wit->Step(mFaceCenter, mFaceSize);
	}

	void WordCloud::Display()
	{
		gl::enableAdditiveBlending();
		for(auto wit=mWords.begin();wit!=mWords.end();++wit)
			wit->Display();
		gl::disableAlphaBlending();

		/*
		gl::color(Color(0,1,0));
		gl::drawStrokedRect(Rectf(mFaceCenter-mFaceSize, mFaceCenter+mFaceSize));*/
	}

	void WordCloud::SetFaceCenter(Vec2f &pFaceCenter)
	{
		mFaceCenter.set(pFaceCenter);
	}

	void WordCloud::SetFaceSize(Vec2f &pFaceSize)
	{
		mFaceSize.set(pFaceSize);
	}
}
