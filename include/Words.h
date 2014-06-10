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
		Wordicle(string pWord, Vec2f pPosition, Vec2f pOffset, const gl::TextureFontRef &pFont);
		~Wordicle();

		void SetWord(string pWord);
		void Step(Vec2f &pFaceCenter, Vec2f &pFaceSize);
		void Display();

	private:
		float mSpeed;
		string mWord;

		Vec2f mPosition;
		Vec2f mVelocity;
		Vec2f mStringSize;
		Vec2f mOffset;
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
		void SetFaceCenter(Vec2f &pFaceCenter);
		void SetFaceSize(Vec2f &pFaceSize);
	private:
		vector<Wordicle> mWords;
		Vec2f mFaceCenter;
		Vec2f mFaceSize;
		gl::TextureFontRef mFont;
	};
}
#endif