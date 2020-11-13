#pragma once

#define CLEAR_PACKET(packet) packet = 0x00;

// �ð� �ʰ��� ���� ������ ��� ���� 4��Ʈ�� 15�� ����
#define SET_TIMEOVER(packet) packet = (unsigned char)(0x0f | packet)

// packet�� ���� 4��Ʈ�� ���� 1 �Ǵ� 0���� ����
#define SET_GAMEOVER(packet, bIsGameOver) packet = (bIsGameOver ? (unsigned char)(0x01 | packet) : (unsigned char)(0x00 | packet))

// packet�� ���� 4��Ʈ�� ���� 1 �Ǵ� 0���� ����
#define SET_WINNER(packet, bBlackWin)     packet = (bBlackWin   ? (unsigned char)(0x10 | packet) : (unsigned char)(0x00 | packet))

// packet�� ���� 4��Ʈ ���� ����ϴ�.
#define GET_GAMEOVER(packet) ( (unsigned char)(0xff & packet) )

// packet�� ���� 4��Ʈ ���� ����ϴ�.
// ����� true�� ��� Player1�� winner�Դϴ�.
#define GET_WINNER(packet) ( (unsigned char)(0xff & (packet >> 4)) )