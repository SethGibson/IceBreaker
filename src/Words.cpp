#include "Words.h"
#include "cinder/Rand.h"

string S_WORDS[] = {"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dogs", "lorem", "ipsum", "dolor", "sit", "amet"};

namespace Words
{
	Wordicle::Wordicle()
	{
		int cid = randInt(9);		
		mPosition = Vec2f::zero();
		mVelocity = Vec2f::zero();
		mWord = S_WORDS[cid];
		mSpeed = mWord.length();
	}

	Wordicle::Wordicle(string pWord, Vec2f pPosition)
	{
		mPosition = pPosition;
		mVelocity = Vec2f::zero();
		mWord = pWord;
		mSpeed = pWord.length()+randFloat(0.25f,2.0f);
		mColor = ColorA(randFloat(1), randFloat(1), randFloat(1), randFloat(0.1f,0.5f));
	}

	Wordicle::~Wordicle()
	{
	}

	void Wordicle::Step(Vec2f &pTarget)
	{
		
		Vec2f cAccel = pTarget-mPosition;
		cAccel.normalize();
		cAccel*=(mSpeed*0.1f);
		
		mVelocity+=cAccel;
		mVelocity.limit(mSpeed);
		mPosition+=mVelocity;
	}

	void Wordicle::Display()
	{
		gl::color(mColor);
		gl::drawSolidCircle(mPosition, mSpeed*5);
		gl::color(Color::white());
		gl::drawStrokedCircle(mPosition, mSpeed*5);
	}

	WordCloud::WordCloud()
	{
		for(int i=0;i<13;++i)
			mWords.push_back(Wordicle(S_WORDS[i], Vec2f::zero()));
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
