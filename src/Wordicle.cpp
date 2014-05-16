#include "Wordicle.h"

Wordicle::Wordicle()
{
}

Wordicle::Wordicle(string pWord, Vec2f pPosition)
{
	mPosition = pPosition;
	mVelocity = Vec2f::zero();
	mWord = pWord;
	mSpeed = pWord.length();
}

Wordicle::~Wordicle()
{
}

void Wordicle::step()
{
	Vec2f cMousePos = 
}

void Wordicle::display()
{
}