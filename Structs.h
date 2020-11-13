
#ifndef _STRUCT_HEADER_
#define _STRUCT_HEADER_

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

namespace gomokuGame
{
	typedef uint16_t						     coordinate_type;      // x or y ��ǥ Ÿ��
	typedef uint8_t							     idx_type;		       // index Ÿ��
	typedef std::pair<coordinate_type, idx_type> coordinate_with_idx;  // <x or y, index>
	
	// ������� ���� ��ǥ�� MyPoint�� �����ϸ�
	// �������� (X.first, Y.first) ��ǥ�� ������� �׸��ϴ�.
	// IsBlack�� true��� ��������, false��� �鵹�� �׸��ϴ�.
	// �׸��� 2���� �迭 board�� [X.second][Y.second] �ε�����
	// ������ Ȥ�� �鵹 �����͸� �����մϴ�.
	struct MyPoint
	{
		MyPoint(coordinate_with_idx x = {}, coordinate_with_idx y = {}, bool isBlack = false) : X(x), Y(y), IsBlack(isBlack) {}

		coordinate_with_idx X;
		coordinate_with_idx Y;
		bool IsBlack;
	};


	// UI �����忡 ��ư �׸��� �޼����� ����
	// ��ư�� �׸� �� �ش� Ÿ���� �����͸� ����մϴ�.
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


	// UI �����尡 Player's Place �׸��� �޼����� ����
	// ������ �׸� �� �ش� Ÿ���� �����͸� ����մϴ�.
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