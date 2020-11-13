/*
	��ü ����ȭ�� ���� ��¿� ��Ʈ�� Ŭ�����Դϴ�.
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
		void WriteInBuffer(uint16_t data);
		void WriteInBuffer(bool data);

		// ����ȭ�� ������ Ÿ���� �� ���� ��� �����ε��� �߰��մϴ�.
		// i.e. void WriteInBuffer(uint32_t num);


		void ClearBuffer();

	private:
		void reallocBuffer(const size_t newSizeInByte);

		char*    mBuffer;	 /* ���� */
		uint32_t mHead;		 /* ���ۿ� Write�� ���� ��ġ (�׻� ���� size�� ����) */
		size_t   mCapacity;	 /* ������ �� ũ�� */
	};
}


/*
		     -----------------------
	mBuffer | d | a | t | a |   |   |
		     -----------------------
			  0   1   2   3   4   5      6
					          ��          ��		
				            mHead    mCapacity
*/