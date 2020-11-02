#ifndef _ENUM_HEADER_
#define _ENUM_HEADER_

namespace gomokuGame
{
	enum eWindowInfo
	{
		WND_WIDTH = 1400	  /* ������ ����(Ÿ��Ʋ �� �� ���� �۾� ����) */
		, WND_HEIGHT = 840    /* ������ ����(Ÿ��Ʋ �� �� ���� �۾� ����) */
		, WND_START_X = 300   /* ������ ���� ��ǥ(x) */
		, WND_START_Y = 100   /* ������ ���� ��ǥ(y) */
	};

	enum eStartMenuInfo
	{
		  BTN_WIDTH = 120												 /* ���� �޴� ��ư �ʺ� */
		, BTN_HEIGHT = 40												 /* ���� �޴� ��ư ���� */
		, BTN_TO_BTN = 10												 /* ��ư�� ��ư ������ �Ÿ� */
		, BTN_X = (WND_WIDTH / 2) - (BTN_WIDTH / 2)						 /* ��ư�� X ��ǥ    */
		, BTN_Y = (WND_HEIGHT - (BTN_HEIGHT * 3 + BTN_TO_BTN * 2)) / 2	 /* ù ��ư�� Y ��ǥ */
		, BTN_DISTANCE = BTN_HEIGHT + BTN_TO_BTN						 /* �� ��ư�� Y ��ǥ�κ��� �ٸ� ��ư�� Y ��ǥ ������ �Ÿ� */
	};

	static_assert(BTN_X >= 0 && BTN_Y >= 0, "Check button's size");
	static_assert(BTN_DISTANCE >= BTN_HEIGHT, "Each button will be overlapped");


	// �������� �� ���������� ���� ���� �� �ֽ��ϴ�.
	// �� �������� 2���� �迭�� �� ��Ұ� �����˴ϴ�.
	// ���Ǽ��� ���� ���������κ��� �����¿� ���� �Ÿ� �̳��� 
	// Ŭ���ص� �ش� �������� ���� ���������� �Ͽ����ϴ�.
	enum eBoardInfo
	{
		BD_LENGTH = 16,												/* �������� �� ���� ����		 */
		BD_WIDTH = 720,												/* �������� ���� ����(����)	 */
		BD_HEIGHT = 720,											/* �������� ���� ����(����)	 */
		BD_BEGIN_X = WND_WIDTH / 2 - BD_WIDTH / 2,					/* �������� ���� �𼭸� x ��ǥ */
		BD_BEGIN_Y = WND_HEIGHT / 2 - BD_HEIGHT / 2,				/* �������� ���� �𼭸� y ��ǥ */
		BD_BEGIN_INDEX = 0,											/* �������� ���� �ε���		 */
		BD_END_INDEX = BD_LENGTH - 1,								/* �������� ������ �ε���	     */
		BD_DISTANCE_DOT_TO_DOT = 43,								/* �������� �� ���������� �Ÿ� */

		BD_VALID_CLICK_DISTANCE = 15,								/* �ٵϾ��� �������� ��ǥ�κ��� ���콺 Ŭ���� ��ȿ�� �Ÿ� */
		BD_DISTANCE_BEGIN_TO_00 = 38,								/* �������� ���� �𼭸��� 0�� 0�������� ���� �Ÿ�        */
		BD_BEGIN_COORDI_X = BD_BEGIN_X + BD_DISTANCE_BEGIN_TO_00, 	/* �������� 0�� 0���� �����ϴ� ���� ��ǥ */
		BD_BEGIN_COORDI_Y = BD_BEGIN_Y + BD_DISTANCE_BEGIN_TO_00, 	/* �������� 0�� 0���� �����ϴ� ���� ��ǥ */
	};

	static_assert((BD_WIDTH < WND_WIDTH) && (BD_HEIGHT < WND_HEIGHT), "Board size must be smaller than window size");
	static_assert(BD_WIDTH == 720 && BD_HEIGHT == 720, "Board's size must be fixed for 720x720");

	enum ePlayerPlaceInfo
	{
		PP_WIDTH = 240,							 /* �÷��̾�  ������ �ʺ�   */
		PP_HEIGHT = 640,						 /* �÷��̾�  ������ ����   */
		PP1_X = (BD_BEGIN_X - PP_WIDTH) / 2,	 /* �÷��̾�1 ������ X ��ǥ */
		PP2_X = WND_WIDTH - (PP1_X + PP_WIDTH),	 /* �÷��̾�2 ������ X ��ǥ */
		PP_Y = BD_BEGIN_Y,						 /* �÷��̾�  ������ Y ��ǥ */
	};

	enum eInGameButtonInfo
	{
		IGB_DISTANCE_PP_TO_READY = 20,								 /* �÷��̾� ������ Ready ��ư ������ �Ÿ� */
		IGB_P1_READY_X = PP1_X,										 /* Player1 Ready ��ư�� X ��ǥ */
		IGB_P2_READY_X = PP2_X,										 /* Player2 Ready ��ư�� X ��ǥ */
		IGB_READY_Y = PP_Y + PP_HEIGHT + IGB_DISTANCE_PP_TO_READY,	 /* Ready ��ư�� Y ��ǥ     */
		IGB_READY_WIDTH  = PP_WIDTH,								 /* Ready ��ư�� ���� ����  */
		IGB_READY_HEIGHT = 60,										 /* Ready ��ư�� ���� ����  */

		IGB_EXIT_WIDTH = 100,										 /* Exit ��ư�� ����   */
		IGB_EXIT_HEIGHT = 30,										 /* Exit ��ư�� ����   */
		IGB_EXIT_X = (WND_WIDTH / 2) - (IGB_EXIT_WIDTH / 2),		 /* Exit ��ư�� X ��ǥ */
		IGB_EXIT_Y = 20												 /* Exit ��ư�� Y ��ǥ */
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
		ST_LENGTH = 36,						/* �ٵϾ��� �� ���� ���� */
		ST_WIN_CONDITION_COUNT = 5,			/* �ٵϾ��� ���� 5�� ���̸� �¸��մϴ�. */
		ST_FOR_CENTER_POS = ST_LENGTH / 2	/* (x, y)�� �� ���� ���ϸ� (x, y)�� �ٵϾ��� �߽��� �˴ϴ�. */
	};

	static_assert(ST_LENGTH == 36, "Stone's size must be fixed for 36");



	enum eButtonID 
	{ 
		BT_CREATE_ROOM = 0,  /* "�� �����"    */
		BT_ENTER_ROOM,		 /* "���� �� ����" */
		BT_EXIT, 			 /* "���� ����"    */
		BT_COUNT, 			 /* ��ư�� ����    */

		BT_READY = 10,       /* "Ready"      */
		BT_START,	         /* "Game Start" */
	};

	enum class eMode 
	{ 
		MD_BEGIN_SCREEN = 0,  /* ���� ȭ��    */
		MD_BEFORE_START,	  /* ���� ���� �� */
		MD_ING,				  /* ���� ��		 */
		MD_END				  /* ���� ��		 */
	};

	enum class ePhase
	{
		PH_SERVER_1 = 0,      /* �� ���� ����   */
		PH_SERVER_2,	      /* ��� ���� ���� */
		PH_CLIENT_1		      /* Ŭ�� ���� ���� */
	};

	
}

#endif // _Enum_Header_