#include "DoubleBuffer.h"

DoubleBuffer* DoubleBuffer::instance = nullptr;

//버퍼 초기화
void DoubleBuffer::InitBuffer()
{
	//현재 스크린 index값은 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : 화면 크기
	COORD size = { BufferWidth, BufferHeight };

	//창 크기 왼쪽 : 0, 위쪽 : 0 오른쪽 : 80 - 1, 아래쪽 : 40 - 1
	SMALL_RECT rect = { 0,0,BufferWidth - 1, BufferHeight - 1 };

	//0번 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[0], size);//창에 나타나는 화면 버퍼 크기
	//0번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);//창 크기 / 색 적용할때와 같은 함수

	//1번 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[1], size);//창에 나타나는화면 버퍼 크기
	//1번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);////창 크기 / 색 적용할때와 같은 함수

	CONSOLE_CURSOR_INFO info;	//콘솔 커서 정보 구조체 / (커서깜박임과 같은 구조)
	info.dwSize = 1;			//커서 크기
	info.bVisible = FALSE;		//커서 안보이게

	//0 & 1 각각의 버퍼에 커서 정보 등록
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

//버퍼 뒤집기 0->1 1->0
void DoubleBuffer::FlipBuffer()
{
	//해당 버퍼 활성화
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0]->[1] / [1]->[0]
	screenIndex = !screenIndex;
}

//버퍼 창 깨끗이
void DoubleBuffer::ClearBuffer()
{
	//시작 위치
	//pos.x = 0; pos.y = 0;
	COORD pos = { 0,0 };
	//매개변수 값 넣어줄려고
	DWORD dw;

	//화면을 ' '로 채움
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

//문자열 원하는 위치에 써주기 & 색깔 까지
//WriteBuffer(x좌표, y좌표, 문자열, 색깔 인덱스)
void DoubleBuffer::WriteBuffer(int x, int y, const char* shape, int color)
{
	//위치 설정
//pos.x = x * 2; pos.y = y;
	COORD pos = { x * 2, y };

	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);

	//색깔 바꿔주기
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//매개변수 값을 넣기 위해
	DWORD dw;

	//해당 버퍼에 쓰기
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

//버퍼 해제
void DoubleBuffer::CloseBuffer()
{
	//버퍼 닫기
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}