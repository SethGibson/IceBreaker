#ifndef __WORDS_H__
#define __WORDS_H__

#include "cinder/app/AppNative.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"

using namespace ci;
using namespace std;

namespace Words
{
	class Wordicle
	{
	public:
		//Wordicle();
		Wordicle(const gl::TextureFontRef &pFont);
		Wordicle(string pWord, Vec2f pPosition, const gl::TextureFontRef &pFont);
		~Wordicle();

		void SetWord(string pWord);
		void Step(Vec2f &pTarget);
		void Display();

	private:
		float mSpeed;
		string mWord;

		Vec2f mPosition;
		Vec2f mVelocity;
		ColorA mColor;

		const gl::TextureFontRef &mFont;
	};

	class WordCloud
	{
	public:
		WordCloud(gl::TextureFontRef pFont);
		WordCloud(vector<Wordicle> pWords);
		WordCloud(vector<string> pWords);
		WordCloud(string *pWords, int pCount);
		~WordCloud();

		void AddWord();
		void Step();
		void Display();
		void SetTarget(Vec2f &pTarget);
	private:
		vector<Wordicle> mWords;
		Vec2f mTarget;
		gl::TextureFontRef mFont;
	};
}
#endif