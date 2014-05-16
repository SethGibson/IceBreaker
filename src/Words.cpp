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
		mColor = ColorA(randFloat(1), randFloat(1), randFloat(1), randFloat(0.4f,0.8f));
		mStringSize = mFont->measureString(mWord);
		mOffset = pOffset*Vec2f(mStringSize.x, mStringSize.x);
	}

	Wordicle::~Wordicle()
	{
	}

	void Wordicle::Step(Vec2f &pTarget)
	{
		mVelocity=(pTarget+mOffset)-mPosition;
		mVelocity.limit(mSpeed*0.25f);
		mPosition+=mVelocity;
	}

	void Wordicle::Display()
	{
		//gl::color(mColor);
		//gl::drawSolidCircle(mPosition, mSpeed*5);
		//gl::color(Color::white());
		//gl::drawStrokedCircle(mPosition, mSpeed*5);
		gl::color(mColor);
		gl::drawSolidRect(Rectf(mPosition.x+mOffset.x-5,
									mPosition.y-mStringSize.y-5,
									mPosition.x+mStringSize.x+mOffset.x+5, 
									mPosition.y+5));

		gl::color(Color::white());
		gl::drawStrokedRect(Rectf(mPosition.x+mOffset.x-5,
									mPosition.y-mStringSize.y-5,
									mPosition.x+mStringSize.x+mOffset.x+5, 
									mPosition.y+5));
		mFont->drawString(mWord, Vec2f(mPosition.x+mOffset.x,mPosition.y));
		
	}

	WordCloud::WordCloud(gl::TextureFontRef pFont)
	{
		mFont = pFont;

		for(int i=0;i<S_COUNT;++i)
		{

			float cx = lmap<float>(i,0,S_COUNT,-1,1);
			float cy = i<=S_COUNT*0.5f? lmap<float>(i,0,S_COUNT*0.5f,0,-1):lmap<float>(i,S_COUNT*0.5f,S_COUNT,-1,0);
			Vec2f cOffset(cx,cy);
			mWords.push_back(Wordicle(S_WORDS[i], Vec2f::zero(), cOffset, mFont));
		}
		mTarget = Vec2f(320,240);
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
			wit->Step(mTarget);
	}

	void WordCloud::Display()
	{
		gl::enableAlphaBlending();
		for(auto wit=mWords.begin();wit!=mWords.end();++wit)
			wit->Display();
		gl::disableAlphaBlending();
	}

	void WordCloud::SetTarget(Vec2f &pTarget)
	{
		mTarget.set(pTarget);
	}
}
