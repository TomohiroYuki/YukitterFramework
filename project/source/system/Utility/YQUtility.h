#pragma once
#include <DirectXMath.h>
#include <string>
#include <cstdlib>


#define _CRT_SECURE_NO_WARNINGS
namespace YQUtility
{
#include "source\math\yuki_math.h"
	class YQUtility
	{
	public:
		YQUtility() {}
		~YQUtility() {}
	private:
	public:
		static VECTORIII GetSlearpPos(VECTORIII&p1, VECTORIII&p2, float t)
		{
			std::string a;
			char* hooge = "aaaaaa";
			char zz[234];
			a = "add";
			a = hooge;
			a = zz;

		}
		static wchar_t* FindExtention(int strlen, wchar_t* str)
		{
			int n = strlen;
			int count = 0;
			while ((n--)>0)
			{
				count++;
				if (str[n] == L'.')
				{
					return &str[n+1];
				}
			}
			count= count;
			return nullptr;
		}

		static const std::wstring ConnectFilePathAndTextureName(wchar_t* filepath, wchar_t* texture_name)
		{
			std::wstring path; 
			path = filepath;
		
			int result=static_cast<int>(path.rfind(L"/"));
			if(result!=-1)
			{
				path.erase(path.begin()+result + 1, path.end());
			}
			else
			{
				result= static_cast<int>(path.rfind(L"\\"));
				if (result != -1)
				{
					path.erase(path.begin() + result + 1, path.end());
				}
			}
			std::wstring tex_string;
			tex_string = texture_name;
			result = static_cast<int>(tex_string.rfind(L"/"));
			if (result != -1)
			{
				tex_string.erase(tex_string.begin(), tex_string.begin()+result);
			}
			else
			{
				result = static_cast<int>(tex_string.rfind(L"\\"));
				if (result != -1)
				{
					tex_string.erase(tex_string.begin(), tex_string.begin() + result+1);
				}
			}
			
			std::wstring fullpath;
			fullpath = path + tex_string;
			return fullpath;
		
		}

		static  wchar_t* ChangeToWcharFromChar(const char* filename)
		{
			size_t len = strlen(filename);
			wchar_t w_filename[128];
			setlocale(LC_ALL, "japanese");
			mbstowcs_s(&len,w_filename , 128, filename, _TRUNCATE);
			return w_filename;
		}
		static const char* ChangeToCharFromWchar(const wchar_t* filename)
		{
			size_t len = wcslen(filename);
		
			char c_filename[128];
			

			setlocale(LC_CTYPE, "jpn");

			wcstombs_s(&len, c_filename,128, filename, _TRUNCATE);
			
			return c_filename;

		}
	};

}