#ifndef __WORDICLE_H__
#define __WORDICLE_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace std;

class Wordicle
{
public:
	Wordicle();
	Wordicle(string pWord, Vec2f pPosition);
	~Wordicle();

	void SetWord(string pWord);
	void Step(Vec2f pTarget);
	void Display();

private:
	float mSpeed;
	Vec2f mPosition;
	Vec2f mVelocity;
	Vec2f mAcceleration;
	string mWord;
};

class WordCloud
{
public:
	WordCloud();
	WordCloud(vector<Wordicle> pWords);
	~WordCloud();

	void Add();
	void Step();
	void Display();
	void SetTarget();
private:
	vector<Wordicle> mWords;
	Vec2f mTarget;
}
#endif