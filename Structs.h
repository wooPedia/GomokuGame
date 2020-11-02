
#ifndef _STRUCT_HEADER_
#define _STRUCT_HEADER_

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

namespace gomokuGame
{
	typedef uint16_t						     coordinate_type;      // x or y 좌표 타입
	typedef uint8_t							     idx_type;		       // index 타입
	typedef std::pair<coordinate_type, idx_type> coordinate_with_idx;  // <x or y, index>
	
	// 오목알이 놓일 좌표를 MyPoint로 전달하면
	// 오목판의 (X.first, Y.first) 좌표에 오목알을 그립니다.
	// IsBlack이 true라면 검은돌을, false라면 백돌을 그립니다.
	// 그리고 2차원 배열 board의 [X.second][Y.second] 인덱스에
	// 검은돌 혹은 백돌 데이터를 저장합니다.
	struct MyPoint
	{
		MyPoint(coordinate_with_idx x = {}, coordinate_with_idx y = {}, bool isBlack = false) : X(x), Y(y), IsBlack(isBlack) {}

		coordinate_with_idx X;
		coordinate_with_idx Y;
		bool IsBlack;
	};


	// UI 스레드에 버튼 그리기 메세지를 통해
	// 버튼을 그릴 때 해당 타입의 데이터를 사용합니다.
	struct InGameButtonInfo
	{
		InGameButtonInfo(int x, int y, int width, int height, HMENU buttonID, LPCWSTR buttonName)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
			, ButtonID(buttonID)
			, ButtonName(buttonName) 
		{
		}

		int X;
		int Y;
		int Width;
		int Height;
		HMENU ButtonID;
		LPCWSTR ButtonName;
	};


	// UI 스레드가 Player's Place 그리기 메세지를 통해
	// 영역을 그릴 때 해당 타입의 데이터를 사용합니다.
	struct InGamePPInfo
	{
		InGamePPInfo(int x, int y, int width, int height)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
		{
		}

		int X;
		int Y; 
		int Width;
		int Height;
	};

	struct ImageInfo
	{
		ImageInfo(float x, float y, float width, float height, Gdiplus::Image* image)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
			, Image(image)
		{
		}

		float X;
		float Y;
		float Width;
		float Height;
		Gdiplus::Image* Image;
	};

	struct TextInfo
	{
		TextInfo(long x, long y, long width, long height, const char* text)
			: X(x)
			, Y(y)
			, Width(width)
			, Height(height)
			, Text(text)
		{
		}

		long X;
		long Y;
		long Width;
		long Height;
		const char* Text;
	};
}


#endif // _STRUCT_HEADER_