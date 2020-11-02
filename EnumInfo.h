#ifndef _ENUM_HEADER_
#define _ENUM_HEADER_

namespace gomokuGame
{
	enum eWindowInfo
	{
		WND_WIDTH = 1400	  /* 윈도우 가로(타이틀 및 바 제외 작업 영역) */
		, WND_HEIGHT = 840    /* 윈도우 세로(타이틀 및 바 제외 작업 영역) */
		, WND_START_X = 300   /* 윈도우 시작 좌표(x) */
		, WND_START_Y = 100   /* 윈도우 시작 좌표(y) */
	};

	enum eStartMenuInfo
	{
		  BTN_WIDTH = 120												 /* 시작 메뉴 버튼 너비 */
		, BTN_HEIGHT = 40												 /* 시작 메뉴 버튼 높이 */
		, BTN_TO_BTN = 10												 /* 버튼과 버튼 사이의 거리 */
		, BTN_X = (WND_WIDTH / 2) - (BTN_WIDTH / 2)						 /* 버튼의 X 좌표    */
		, BTN_Y = (WND_HEIGHT - (BTN_HEIGHT * 3 + BTN_TO_BTN * 2)) / 2	 /* 첫 버튼의 Y 좌표 */
		, BTN_DISTANCE = BTN_HEIGHT + BTN_TO_BTN						 /* 한 버튼의 Y 좌표로부터 다른 버튼의 Y 좌표 까지의 거리 */
	};

	static_assert(BTN_X >= 0 && BTN_Y >= 0, "Check button's size");
	static_assert(BTN_DISTANCE >= BTN_HEIGHT, "Each button will be overlapped");


	// 오목판의 각 교차점에만 돌을 놓을 수 있습니다.
	// 각 교차점과 2차원 배열의 각 요소가 대응됩니다.
	// 편의성을 위해 교차점으로부터 상하좌우 일정 거리 이내를 
	// 클릭해도 해당 교차점에 돌이 놓아지도록 하였습니다.
	enum eBoardInfo
	{
		BD_LENGTH = 16,												/* 오목판의 한 변의 길이		 */
		BD_WIDTH = 720,												/* 오목판의 가로 길이(고정)	 */
		BD_HEIGHT = 720,											/* 오목판의 세로 길이(고정)	 */
		BD_BEGIN_X = WND_WIDTH / 2 - BD_WIDTH / 2,					/* 오목판의 시작 모서리 x 좌표 */
		BD_BEGIN_Y = WND_HEIGHT / 2 - BD_HEIGHT / 2,				/* 오목판의 시작 모서리 y 좌표 */
		BD_BEGIN_INDEX = 0,											/* 오목판의 시작 인덱스		 */
		BD_END_INDEX = BD_LENGTH - 1,								/* 오목판의 마지막 인덱스	     */
		BD_DISTANCE_DOT_TO_DOT = 43,								/* 오목판의 각 교차점과의 거리 */

		BD_VALID_CLICK_DISTANCE = 15,								/* 바둑알이 놓여지는 좌표로부터 마우스 클릭이 유효한 거리 */
		BD_DISTANCE_BEGIN_TO_00 = 38,								/* 오목판의 시작 모서리와 0행 0열까지의 고정 거리        */
		BD_BEGIN_COORDI_X = BD_BEGIN_X + BD_DISTANCE_BEGIN_TO_00, 	/* 오목판의 0행 0열에 대응하는 시작 좌표 */
		BD_BEGIN_COORDI_Y = BD_BEGIN_Y + BD_DISTANCE_BEGIN_TO_00, 	/* 오목판의 0행 0열에 대응하는 시작 좌표 */
	};

	static_assert((BD_WIDTH < WND_WIDTH) && (BD_HEIGHT < WND_HEIGHT), "Board size must be smaller than window size");
	static_assert(BD_WIDTH == 720 && BD_HEIGHT == 720, "Board's size must be fixed for 720x720");

	enum ePlayerPlaceInfo
	{
		PP_WIDTH = 240,							 /* 플레이어  영역의 너비   */
		PP_HEIGHT = 640,						 /* 플레이어  영역의 높이   */
		PP1_X = (BD_BEGIN_X - PP_WIDTH) / 2,	 /* 플레이어1 영역의 X 좌표 */
		PP2_X = WND_WIDTH - (PP1_X + PP_WIDTH),	 /* 플레이어2 영역의 X 좌표 */
		PP_Y = BD_BEGIN_Y,						 /* 플레이어  영역의 Y 좌표 */
	};

	enum eInGameButtonInfo
	{
		IGB_DISTANCE_PP_TO_READY = 20,								 /* 플레이어 영역과 Ready 버튼 사이의 거리 */
		IGB_P1_READY_X = PP1_X,										 /* Player1 Ready 버튼의 X 좌표 */
		IGB_P2_READY_X = PP2_X,										 /* Player2 Ready 버튼의 X 좌표 */
		IGB_READY_Y = PP_Y + PP_HEIGHT + IGB_DISTANCE_PP_TO_READY,	 /* Ready 버튼의 Y 좌표     */
		IGB_READY_WIDTH  = PP_WIDTH,								 /* Ready 버튼의 가로 길이  */
		IGB_READY_HEIGHT = 60,										 /* Ready 버튼의 세로 길이  */

		IGB_EXIT_WIDTH = 100,										 /* Exit 버튼의 가로   */
		IGB_EXIT_HEIGHT = 30,										 /* Exit 버튼의 세로   */
		IGB_EXIT_X = (WND_WIDTH / 2) - (IGB_EXIT_WIDTH / 2),		 /* Exit 버튼의 X 좌표 */
		IGB_EXIT_Y = 20												 /* Exit 버튼의 Y 좌표 */
	};

	static_assert(PP_HEIGHT + IGB_DISTANCE_PP_TO_READY + IGB_READY_HEIGHT == BD_HEIGHT, "both objects's height is not same.");


	enum ePlayerInfo
	{
		PI_PLAYER1_X = PP1_X + 45,
		PI_PLAYER2_X = PP2_X + 45,
		PI_PLAYER_Y = PP_Y + 45,
		PI_PLAYER_WIDTH = 150,
		PI_PLAYER_HEIGHT = 450,

		PI_P1_ID_X = PI_PLAYER1_X,
		PI_P2_ID_X = PI_PLAYER2_X,
		PI_P_ID_Y  = PI_PLAYER_Y + PI_PLAYER_HEIGHT + 20,
		PI_P_ID_WIDTH = PI_PLAYER_WIDTH,
		PI_P_ID_HEIGHT = 30
	};

	enum eStoneInfo
	{
		ST_LENGTH = 36,						/* 바둑알의 한 변의 길이 */
		ST_WIN_CONDITION_COUNT = 5,			/* 바둑알이 연속 5개 놓이면 승리합니다. */
		ST_FOR_CENTER_POS = ST_LENGTH / 2	/* (x, y)에 이 값을 더하면 (x, y)가 바둑알의 중심이 됩니다. */
	};

	static_assert(ST_LENGTH == 36, "Stone's size must be fixed for 36");



	enum eButtonID 
	{ 
		BT_CREATE_ROOM = 0,  /* "방 만들기"    */
		BT_ENTER_ROOM,		 /* "랜덤 방 입장" */
		BT_EXIT, 			 /* "게임 종료"    */
		BT_COUNT, 			 /* 버튼의 개수    */

		BT_READY = 10,       /* "Ready"      */
		BT_START,	         /* "Game Start" */
	};

	enum class eMode 
	{ 
		MD_BEGIN_SCREEN = 0,  /* 시작 화면    */
		MD_BEFORE_START,	  /* 게임 시작 전 */
		MD_ING,				  /* 게임 중		 */
		MD_END				  /* 게임 끝		 */
	};

	enum class ePhase
	{
		PH_SERVER_1 = 0,      /* 방 생성 상태   */
		PH_SERVER_2,	      /* 상대 입장 상태 */
		PH_CLIENT_1		      /* 클라 입장 상태 */
	};

	
}

#endif // _Enum_Header_