/*
	객체 직렬화를 위한 출력용 스트림 클래스입니다.
*/

#pragma once

#include <memory>

namespace gomokuGame
{
	class OutputMemoryStream final
	{
	public:
		OutputMemoryStream();
		~OutputMemoryStream();

		const char* GetBuffer() const;
		size_t GetSize() const;

		void WriteInBuffer(const void* pArg, size_t sizeInByte);
		void WriteInBuffer(uint8_t data);

		// 직렬화할 데이터 타입이 더 있을 경우 오버로딩을 추가합니다.
		// i.e. void WriteInBuffer(uint32_t num);

	private:
		void reallocBuffer(const size_t newSizeInByte);

		char*    mBuffer;	 /* 버퍼 */
		uint32_t mHead;		 /* 버퍼에 Write할 시작 위치 (항상 현재 size와 동일) */
		size_t   mCapacity;	 /* 버퍼의 총 크기 */
	};
}


/*
		     -----------------------
	mBuffer | d | a | t | a |   |   |
		     -----------------------
			  0   1   2   3   4   5      6
					          ↑          ↑		
				            mHead    mCapacity
*/