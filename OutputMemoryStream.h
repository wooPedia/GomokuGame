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
<<<<<<< HEAD
		void WriteInBuffer(uint16_t data);
		void WriteInBuffer(bool data);
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

		// ����ȭ�� ������ Ÿ���� �� ���� ��� �����ε��� �߰��մϴ�.
		// i.e. void WriteInBuffer(uint32_t num);

<<<<<<< HEAD

		void ClearBuffer();

=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
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