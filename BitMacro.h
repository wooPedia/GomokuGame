#pragma once

#define CLEAR_PACKET(packet) packet = 0x00;

// 시간 초과로 인한 종료일 경우 하위 4비트를 15로 설정
#define SET_TIMEOVER(packet) packet = (unsigned char)(0x0f | packet)

// packet의 하위 4비트의 값을 1 또는 0으로 설정
#define SET_GAMEOVER(packet, bIsGameOver) packet = (bIsGameOver ? (unsigned char)(0x01 | packet) : (unsigned char)(0x00 | packet))

// packet의 상위 4비트의 값을 1 또는 0으로 설정
#define SET_WINNER(packet, bBlackWin)     packet = (bBlackWin   ? (unsigned char)(0x10 | packet) : (unsigned char)(0x00 | packet))

// packet의 하위 4비트 값을 얻습니다.
#define GET_GAMEOVER(packet) ( (unsigned char)(0xff & packet) )

// packet의 상위 4비트 값을 얻습니다.
// 결과가 true일 경우 Player1이 winner입니다.
#define GET_WINNER(packet) ( (unsigned char)(0xff & (packet >> 4)) )