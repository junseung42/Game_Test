#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <time.h>

#pragma region Function
void SetPosition();//커서 이동 함수
void Cursor_Info();//커서 깜박임 없음 함수
void ChangeColor();//컬러 함수
bool CheckCrash(int x, int y);//충돌 되면 true 아니면 false반환
void CheckCount(int x, int y);//충돌된 블럭의 개수 
#pragma endregion

#pragma region Color
enum Color
{
    Black,
    DarkBlue,
    DarkGreen,
    DarkCyan,
    DarkRed,
    DarkMagenta,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
};
#pragma endregion

#pragma region Map
#define Screen_Width_Size 12
#define Screen_Vertical_Size 21
int map[Screen_Vertical_Size][Screen_Width_Size] = {
    //1,2,3,4,5,6,7,8,9,0,1,2
     {1,0,0,0,0,0,0,0,0,0,0,1},//1
     {1,0,0,0,0,0,0,0,0,0,0,1},//2
     {1,0,0,0,0,0,0,0,0,0,0,1},//3
     {1,0,0,0,0,0,0,0,0,0,0,1},//4
     {1,0,0,0,0,0,0,0,0,0,0,1},//5
     {1,0,0,0,0,0,0,0,0,0,0,1},//6
     {1,0,0,0,0,0,0,0,0,0,0,1},//7
     {1,0,0,0,0,0,0,0,0,0,0,1},//8
     {1,0,0,0,0,0,0,0,0,0,0,1},//9
     {1,0,0,0,0,0,0,0,0,0,0,1},//0
     {1,0,0,0,0,0,0,0,0,0,0,1},//1
     {1,0,0,0,0,0,0,0,0,0,0,1},//2
     {1,0,0,0,0,0,0,0,0,0,0,1},//3
     {1,0,0,0,0,0,0,0,0,0,0,1},//4
     {1,0,0,0,0,0,0,0,0,0,0,1},//5
     {1,0,0,0,0,0,0,0,0,0,0,1},//6
     {1,0,0,0,0,0,0,0,0,0,0,1},//7
     {1,0,0,0,0,0,0,0,0,0,0,1},//8
     {1,0,0,0,0,0,0,0,0,0,0,1},//9
     {1,0,0,0,0,0,0,0,0,0,0,1},//0
     {1,1,1,1,1,1,1,1,1,1,1,1},//1
};
#pragma endregion
#pragma region HOLD_MAP
#define Hold_Screen_Width_Size 8
#define Hold_Screen_Vertical_Size 8
int Hold_map[Hold_Screen_Vertical_Size][Hold_Screen_Width_Size] = {
    //1,2,3,4,5,6,7,8
     {1,1,1,1,1,1,1,1},//1
     {1,0,0,0,0,0,0,1},//2
     {1,0,0,0,0,0,0,1},//3
     {1,0,0,0,0,0,0,1},//4
     {1,0,0,0,0,0,0,1},//5
     {1,0,0,0,0,0,0,1},//6
     {1,0,0,0,0,0,0,1},//7
     {1,1,1,1,1,1,1,1},//8
};
#pragma endregion
#pragma region NEXT_MAP
#define Next_Screen_Width_Size 8
#define Next_Screen_Vertical_Size 8
int Next_map[Next_Screen_Vertical_Size][Next_Screen_Width_Size] = {
    //1,2,3,4,5,6,7,8
     {1,1,1,1,1,1,1,1},//1
     {1,0,0,0,0,0,0,1},//2
     {1,0,0,0,0,0,0,1},//3
     {1,0,0,0,0,0,0,1},//4
     {1,0,0,0,0,0,0,1},//5
     {1,0,0,0,0,0,0,1},//6
     {1,0,0,0,0,0,0,1},//7
     {1,1,1,1,1,1,1,1},//8
};
#pragma endregion

#pragma region Logic
enum Scene
{
    LOGO,//메인메뉴
    START,//게임화면
    RESULT,//결과
    RECORD,//과거 점수확인
    EXIT//나가기
};
Scene scene;

void InitLogo();//메인메뉴
void UpdateLogo();
void ClearLogo();

void InitStart();//게임화면
void UpdateStart();
void ClearStart();

void InitResult();//결과
void UpdateResult();
void ClearResult();

void InitRecord();//과거 점수확인
void UpdateRecord();
void ClearRecord();

void InitExit();//나가기
void UpdateExit();
void ClearExit();
#pragma endregion

#pragma region Obj Pointer
struct Obj
{
    int x;
    int y;
    const char* String_shape;
    int Block_shape[7][4][4][4];
    int Random;
    int Block_Cut[4];
    int Value;
    int count;
    int Point_count;
    int point;
};
//LOGO
Obj* Logo_Player_UI = nullptr;//Player UI
Obj* Logo_Start_UI = nullptr;//START UI
Obj* Logo_Record_UI = nullptr;//RECORD UI
Obj* Logo_Exit_UI = nullptr;//EXIT UI

//START
Obj* Start_Shap_BLOCK_UI = nullptr;//block UI
Obj* Start_Random = nullptr;//블럭 램덤 생성
Obj* Start_Shap_BLOCK_Value = nullptr;
Obj* Start_Count = nullptr;
Obj* Start_Point_count = nullptr;
Obj* Start_point = nullptr;
Obj* Start_Next_value = nullptr;//다음블럭 기능
#pragma endregion

#pragma region Main
int main()
{
    Cursor_Info();

    srand((unsigned)time(NULL));

    scene = LOGO;

    InitLogo();

    while (1)
    {
        system("cls");

        switch (scene)
        {
        case 0://메인메뉴
            UpdateLogo();
            break;
        case 1://게임화면
            UpdateStart();
            break;
        case 2://결과
            UpdateResult();
            break;
        case 3://과거 점수확인
            break;
        case 4://나가기
            UpdateExit();
            break;
        default:
            break;
        }
        Sleep(50);
    }
    return 0;
}
#pragma endregion

#pragma region Function
void SetPosition(int x, int y) {//커서 이동 함수
    COORD pos;
    pos.X = x * 2;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Cursor_Info() {//커서 깜박이 없음 함수
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void ChangeColor(Color color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#pragma endregion

#pragma region Logic
#pragma region Logo
#pragma region InitLogo
void InitLogo()
{
    Logo_Player_UI = (Obj*)malloc(sizeof(Obj));
    Logo_Player_UI->x = 18;
    Logo_Player_UI->y = 10;
    Logo_Player_UI->String_shape = "▶";

    Logo_Start_UI = (Obj*)malloc(sizeof(Obj));
    Logo_Start_UI->x = 20;
    Logo_Start_UI->y = 10;
    Logo_Start_UI->String_shape = "START";

    Logo_Record_UI = (Obj*)malloc(sizeof(Obj));
    Logo_Record_UI->x = 20;
    Logo_Record_UI->y = 12;
    Logo_Record_UI->String_shape = "RECORD--없음";

    Logo_Exit_UI = (Obj*)malloc(sizeof(Obj));
    Logo_Exit_UI->x = 20;
    Logo_Exit_UI->y = 14;
    Logo_Exit_UI->String_shape = "EXIT";
}
#pragma endregion
#pragma region UpdateLogo
void UpdateLogo()
{
    SetPosition(30, 8);
    printf("조작법 -> 왼쪽으로 가기 = 왼쪽 방향키");
    SetPosition(30, 10);
    printf("       -> 오른쪽으로 가기 = 오른쪽 방향키");
    SetPosition(30, 12);
    printf("       -> 방향 돌리기 = 위쪽 방향키");
    SetPosition(30, 14);
    printf("       -> Hold = c");
    SetPosition(30, 16);
    printf("       -> 바로 내리기 = Space Bar");
#pragma region MAP
    for (int y = 0; y < Screen_Vertical_Size; y++) {
        for (int x = 0; x < Screen_Width_Size; x++) {
            switch (map[y][x])
            {
            case 0:
                break;
            case 1:
                SetPosition(x, y);
                printf("□");
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region 이동
    if (GetAsyncKeyState(VK_UP)) {
        Logo_Player_UI->y -= 2;
        if (Logo_Player_UI->y <= 9) {
            Logo_Player_UI->y = 10;
        }
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        Logo_Player_UI->y += 2;
        if (Logo_Player_UI->y >= 15) {
            Logo_Player_UI->y = 14;
        }
    }
#pragma endregion
#pragma region UI
    //Player UI
    SetPosition(Logo_Player_UI->x, Logo_Player_UI->y);
    printf(Logo_Player_UI->String_shape);
    //START UI
    SetPosition(Logo_Start_UI->x, Logo_Start_UI->y);
    printf(Logo_Start_UI->String_shape);
    //RECORD UI
    SetPosition(Logo_Record_UI->x, Logo_Record_UI->y);
    printf(Logo_Record_UI->String_shape);
    //EXIT UI
    SetPosition(Logo_Exit_UI->x, Logo_Exit_UI->y);
    printf(Logo_Exit_UI->String_shape);
#pragma endregion
#pragma region 설명
    SetPosition(20, 8);
    printf("선택 = ENTET키");
#pragma endregion
#pragma region 상호작용
    //상호작용
    if (Logo_Player_UI->x == 18 && Logo_Player_UI->y == 10 && GetAsyncKeyState(VK_RETURN)) {

        InitStart();
        scene = START;
        ClearLogo();
    }
    if (Logo_Player_UI->x == 18 && Logo_Player_UI->y == 14 && GetAsyncKeyState(VK_RETURN)) {
        scene = EXIT;
        ClearLogo();
    }
#pragma endregion
}
#pragma endregion
#pragma region ClearLogo
void ClearLogo()
{
    free(Logo_Player_UI);
    free(Logo_Start_UI);
    free(Logo_Record_UI);
    free(Logo_Exit_UI);
}
#pragma endregion
#pragma endregion
#pragma region Start
#pragma region InitStart
void InitStart()
{
#pragma region map 초기화
    for (int y = 0; y < Screen_Vertical_Size - 1; y++) {
        for (int x = 0; x < Screen_Width_Size - 1; x++) {
            if (map[y][x] != 1) {
                map[y][x] = 0;
            }
        }
    }
#pragma endregion
#pragma region BLOCK_UI
    Start_Shap_BLOCK_UI = (Obj*)malloc(sizeof(Obj));
    Start_Shap_BLOCK_UI->x = 5;//22;
    Start_Shap_BLOCK_UI->y = 0;//2;
    int block_shape[7][4][4][4] = {
        { // T모양 블럭
            {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {0,1,0,0}
            }
        },
        {    // 번개 블럭
            {
                {0,0,0,0},
                {0,1,1,0},
                {1,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {1,0,0,0},
                {1,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {1,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {1,0,0,0},
                {1,1,0,0},
                {0,1,0,0}
            }
        },
        {   // 번개 블럭 반대
            {
                {0,0,0,0},
                {1,1,0,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {1,0,0,0}
            },
            {
                {0,0,0,0},
                {1,1,0,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {1,0,0,0}
            }
        },
        {   // 1자형 블럭
            {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            }
        },
        {   // L자형 블럭
            {
                {0,0,0,0},
                {1,0,0,0},
                {1,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {1,1,0,0},
                {1,0,0,0},
                {1,0,0,0}
            },
            {
                {0,0,0,0},
                {1,1,1,0},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {0,0,0,0}
            }
        },
        {   // L자형 블럭 반대
            {
                {0,0,0,0},
                {0,0,1,0},
                {1,1,1,0},
                {0,0,0,0}
            },
            {
                {1,0,0,0},
                {1,0,0,0},
                {1,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {1,1,1,0},
                {1,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {1,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            }
        },
        {   // 네모 블럭
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        }
    };

    memcpy(Start_Shap_BLOCK_UI->Block_shape, block_shape, sizeof(block_shape));
#pragma endregion
#pragma region Random
    Start_Random = (Obj*)malloc(sizeof(Obj));
    Start_Random->Random = rand() % 7;
#pragma endregion
#pragma region BLOCK_Value
    Start_Shap_BLOCK_Value = (Obj*)malloc(sizeof(Obj));
    Start_Shap_BLOCK_Value->Value = 0;
#pragma endregion
#pragma region Count
    Start_Count = (Obj*)malloc(sizeof(Obj));
    Start_Count->count = 0;
#pragma endregion
#pragma region Point_count
    Start_Point_count = (Obj*)malloc(sizeof(Obj));
    Start_Point_count->Point_count = 0;
#pragma endregion
#pragma region Start_point
    Start_point = (Obj*)malloc(sizeof(Obj));
    Start_point->point = 0;
#pragma endregion
#pragma region Next_map
    Start_Next_value = (Obj*)malloc(sizeof(Obj));
    Start_Next_value->Value = 0;
#pragma endregion
}
#pragma endregion
#pragma region UpdateStart
void UpdateStart()
{
#pragma region 설명
    SetPosition(15, 8);
    printf("HOLD");
    SetPosition(21, 8);
    printf("NEXT BLOCK");
    SetPosition(15, 10);
    printf("점수 = %d", Start_point->point);
    SetPosition(15, 12);
    printf("조작법 -> 왼쪽으로 가기 = 왼쪽 방향키");
    SetPosition(15, 14);
    printf("       -> 오른쪽으로 가기 = 오른쪽 방향키");
    SetPosition(15, 16);
    printf("       -> 방향 돌리기 = 위쪽 방향키");
    SetPosition(15, 18);
    printf("       -> Hold = c");
    SetPosition(15, 20);
    printf("       -> 바로 내리기 = Space Bar");
#pragma endregion
#pragma region Map
    for (int y = 0; y < Screen_Vertical_Size; y++) {
        for (int x = 0; x < Screen_Width_Size; x++) {
            switch (map[y][x])
            {
            case 0:
                break;
            case 1:
                SetPosition(x, y);
                ChangeColor(Yellow);
                printf("□");
                ChangeColor(White);
                break;
            case 2:
                SetPosition(x, y);
                printf("■");
                break;
            case 3:
                SetPosition(x, y);
                printf("□");
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region Hold_Map
    for (int y = 0; y < Hold_Screen_Vertical_Size; y++) {
        for (int x = 0; x < Hold_Screen_Width_Size; x++) {
            switch (Hold_map[y][x])
            {
            case 0:
                break;
            case 1:
                ChangeColor(Yellow);
                SetPosition(x + Screen_Width_Size, y);
                printf("□");
                ChangeColor(White);
                break;
            case 2:
                SetPosition(x + Screen_Width_Size, y);
                printf("■");
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region Next_Map
    for (int y = 0; y < Next_Screen_Vertical_Size; y++) {
        for (int x = 0; x < Next_Screen_Width_Size; x++) {
            switch (Next_map[y][x])
            {
            case 0:
                break;
            case 1:
                ChangeColor(Yellow);
                SetPosition(x + Screen_Width_Size + Hold_Screen_Width_Size, y);
                printf("□");
                ChangeColor(White);
                break;
            case 2:
                SetPosition(x + Screen_Width_Size + Hold_Screen_Width_Size, y);
                printf("■");
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region 다음 블럭
    bool isNextMapEmpty = true;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (Next_map[3 + y][3 + x] == 2) {
                isNextMapEmpty = false;
                break;
            }
        }
    }

    if (isNextMapEmpty) {//도형이 없는경우
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {

                //초기화
                Next_map[3 + y][3 + x] = 0;

                //도형을 다음맵에 그리기
                if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                    Next_map[3 + y][3 + x] = 2;
                }

                //새로운 도형 만들기
                Start_Shap_BLOCK_UI->x = 5;
                Start_Shap_BLOCK_UI->y = 0;
                Start_Random->Random = rand() % 7;
                Start_Count->count = 0;
                Start_Next_value->Value = 1;
            }
        }
    }

    //위에 Value가 1이되면 바로 밑에if문이 실행되서 그런듯
    else if (Start_Next_value->Value) {//바닥에 닿거나 홀드일 경우(새로운 도형이 필요한 경우)
        int temp_shape[4][4] = { 0 };//임시저장 도형 초기화
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {

                //Next_map에 있는 도형을 임시저장공간에다가 그리기
                if (Next_map[3 + y][3 + x] == 2) {
                    temp_shape[y][x] = 1;
                }

                //Next_map 초기화
                Next_map[3 + y][3 + x] = 0;

                //플레이맵에 있는 도형을 Next_map맵에 그리기
                if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                    Next_map[3 + y][3 + x] = 2;
                }
            }
        }

        //플레이맵에 임시 저장한 도형으로 교체
        for (int r = 0; r < 7; r++) {
            for (int v = 0; v < 4; v++) {
                bool isMatch = true;
                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        if (temp_shape[y][x] != Start_Shap_BLOCK_UI->Block_shape[r][v][y][x]) {//하나라도 불일치 하다면 나감
                            isMatch = false;
                            break;//x루프 탈출
                        }
                    }//여기로
                    if (!isMatch) {//자동으로 참
                        break;//y루프탈출
                    }
                }//여기로
                if (isMatch) {//r, v를 써야되기 때문에 여기까지만 나가기
                    Start_Random->Random = r;
                    Start_Shap_BLOCK_Value->Value = v;
                }
            }
        }
        Start_Next_value->Value = 0;
    }
#pragma endregion
#pragma region 그리기
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                SetPosition(Start_Shap_BLOCK_UI->x + x, Start_Shap_BLOCK_UI->y + y);
                printf("■");
            }
        }
    }
#pragma endregion
#pragma region 도형 이동경로
    for (int y = 0; y < Screen_Vertical_Size - 1; y++) {
        for (int x = 0; x < Screen_Width_Size - 1; x++) {
            if (map[y][x] == 3) {
                map[y][x] = 0;
            }
        }
    }
    int Befor_y = Start_Shap_BLOCK_UI->y;
    while (!CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1)) {
        Start_Shap_BLOCK_UI->y++;//블록을 아래로 이동
    }
    //Start_Shap_BLOCK_UI->y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
    if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1) == true) {
        if (1) {
            // 현재 블록 저장
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                        map[y + Start_Shap_BLOCK_UI->y - 1][x + Start_Shap_BLOCK_UI->x] = 3;
                    }
                }
            }
        }
    }
    Start_Shap_BLOCK_UI->y = Befor_y;
#pragma endregion
#pragma region 내리기
    if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1) == true) return;
    Sleep(200);
    Start_Shap_BLOCK_UI->y++;
#pragma endregion
#pragma region 바닥에 닿으면 블럭 처리
    if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1) == true) {
        if (1) {
            // 현재 블록 저장
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                        map[y + Start_Shap_BLOCK_UI->y - 1][x + Start_Shap_BLOCK_UI->x] = 2;
                    }
                }
            }
            Start_Shap_BLOCK_UI->x = 5;
            Start_Shap_BLOCK_UI->y = 0;
            Start_Random->Random = rand() % 7;
            Start_Count->count = 0;
            Start_Next_value->Value = 1;
        }
    }
#pragma endregion
#pragma region Hold
    if (GetAsyncKeyState(0x43)) {
        // Hold_map의 상태를 확인
        bool isHoldMapEmpty = true;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (Hold_map[3 + y][3 + x] == 2) {
                    isHoldMapEmpty = false;
                    break;
                }
            }
        }

        if (isHoldMapEmpty) {//도형이 없을 경우
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {

                    //맵 초기화
                    Hold_map[3 + y][3 + x] = 0;

                    //도형을 홀드맵에 그리기
                    if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                        Hold_map[3 + y][3 + x] = 2;
                    }
                }
            }


            //새로운 도형 랜덤 생성
            Start_Count->count = 0;
            Start_Random->Random = rand() % 7;
            Start_Shap_BLOCK_UI->x = 5;
            Start_Shap_BLOCK_UI->y = 0;
            Start_Next_value->Value = 1;
        }
        else {//도형이 있을경우 
            int temp_shape[4][4] = { 0 };//임시저장 도형 초기화
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {

                    //홀드맵에 있는 도형을 임시저장공간에다가 그리기
                    if (Hold_map[3 + y][3 + x] == 2) {
                        temp_shape[y][x] = 1;
                    }

                    //홀드맵 초기화
                    Hold_map[3 + y][3 + x] = 0;

                    //플레이맵에 있는 도형을 홀드맵에 그리기
                    if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                        Hold_map[3 + y][3 + x] = 2;
                    }
                }
            }

            //플레이 맵에 임시 저장한 도형으로 교체
            for (int r = 0; r < 7; r++) {
                for (int v = 0; v < 4; v++) {
                    bool isMatch = true;
                    for (int y = 0; y < 4; y++) {
                        for (int x = 0; x < 4; x++) {
                            if (temp_shape[y][x] != Start_Shap_BLOCK_UI->Block_shape[r][v][y][x]) {//하나라도 불일치 하다면 나감
                                isMatch = false;
                                break;//x루프 탈출
                            }
                        }//여기로
                        if (!isMatch) {//자동으로 참
                            break;//y루프탈출
                        }
                    }//여기로
                    if (isMatch) {//r, v를 써야되기 때문에 여기까지만 나가기
                        Start_Random->Random = r;
                        Start_Shap_BLOCK_Value->Value = v;
                    }
                }
            }
        }
    }
#pragma endregion
#pragma region 이동
    if (GetAsyncKeyState(VK_RIGHT)) {
#pragma region 도형 이동경로
        for (int y = 0; y < Screen_Vertical_Size - 1; y++) {
            for (int x = 0; x < Screen_Width_Size - 1; x++) {
                if (map[y][x] == 3) {
                    map[y][x] = 0;
                }
            }
        }

        int Befor_y_R = Start_Shap_BLOCK_UI->y;
        while (!CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1)) {
            Start_Shap_BLOCK_UI->y++;//블록을 아래로 이동
        }
        //Start_Shap_BLOCK_UI->y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1) == true) {
            if (1) {
                // 현재 블록 저장
                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                            map[y + Start_Shap_BLOCK_UI->y - 1][x + Start_Shap_BLOCK_UI->x] = 3;
                        }
                    }
                }
            }
        }
        Start_Shap_BLOCK_UI->y = Befor_y_R;
#pragma endregion
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == false) {
            Start_Shap_BLOCK_UI->x += 1;
        }
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == true) {
            Start_Shap_BLOCK_UI->x -= 1;
        }
    }
    if (GetAsyncKeyState(VK_LEFT)) {
#pragma region 도형 이동경로
        for (int y = 0; y < Screen_Vertical_Size - 1; y++) {
            for (int x = 0; x < Screen_Width_Size - 1; x++) {
                if (map[y][x] == 3) {
                    map[y][x] = 0;
                }
            }
        }

        int Befor_y_L = Start_Shap_BLOCK_UI->y;
        while (!CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1)) {
            Start_Shap_BLOCK_UI->y++;//블록을 아래로 이동
        }
        //Start_Shap_BLOCK_UI->y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1) == true) {
            if (1) {
                // 현재 블록 저장
                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                            map[y + Start_Shap_BLOCK_UI->y - 1][x + Start_Shap_BLOCK_UI->x] = 3;
                        }
                    }
                }
            }
        }
        Start_Shap_BLOCK_UI->y = Befor_y_L;
#pragma endregion
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == false) {
            Start_Shap_BLOCK_UI->x -= 1;
        }
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == true) {
            Start_Shap_BLOCK_UI->x += 1;
        }
    }
    if (GetAsyncKeyState(VK_UP)) {
        Start_Shap_BLOCK_Value->Value++;//형태변환
        if (Start_Shap_BLOCK_Value->Value >= 4) {
            Start_Shap_BLOCK_Value->Value = 0;
        }
        if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == true) {
            if (Start_Shap_BLOCK_UI->x <= 5) {//왼쪽
                CheckCount(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y);
                Start_Shap_BLOCK_UI->x += Start_Count->count;
                Start_Count->count = 0;
            }
            if (Start_Shap_BLOCK_UI->x >= 8) {//오른쪽
                CheckCount(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y);
                Start_Shap_BLOCK_UI->x -= Start_Count->count;
                Start_Count->count = 0;
            }
            if (Start_Shap_BLOCK_UI->y >= 17) {//아래
                CheckCount(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y);
                Start_Shap_BLOCK_UI->y -= Start_Count->count;
                Start_Count->count = 0;
            }
        }
    }
    if (GetAsyncKeyState(VK_SPACE)) {
        while (!CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y + 1)) {
            Start_Shap_BLOCK_UI->y++;//블록을 아래로 이동
        }
        Start_Shap_BLOCK_UI->y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
    }
#pragma endregion   
#pragma region 블럭 채우면 처리
    for (int y = Screen_Vertical_Size - 1; y >= 0; y--) {
        Start_Point_count->Point_count = 0;
        for (int x = 1; x < Screen_Width_Size - 1; x++) {
            if (map[y][x] == 2) {
                Start_Point_count->Point_count++;
            }
        }
        if (Start_Point_count->Point_count >= 10) {//1칸씩만 지움
            Start_point->point += 1;
            for (int x = 0; y - x >= 0; x++) {//다 차있는 행부터 위쪽 행이 얼마나 남아있는지 계산
                for (int z = 1; z < Screen_Width_Size - 1; z++) {//x축
                    if (y - x - 1 >= 0) {
                        map[y - x][z] = map[y - x - 1][z];//위쪽행을 아래쪽으로 덮기
                    }
                    else {
                        map[y - x][z] = 0;//가장 위쪽값 쓰래기값 방지
                    }
                }
            }

        }
    }
#pragma endregion
#pragma region 게임 오버
    if (CheckCrash(Start_Shap_BLOCK_UI->x, Start_Shap_BLOCK_UI->y) == true) {
        SetPosition(20, 3);
        printf("!!게임 오버!!");
        InitResult(); // 결과 초기화
        scene = RESULT; // 결과로 전환
        ClearStart(); // 메모리 해제
    }
#pragma endregion
}
#pragma endregion
#pragma region ClearStart
void ClearStart()
{
    free(Start_Shap_BLOCK_UI);
    free(Start_Random);
    free(Start_Shap_BLOCK_Value);
    free(Start_Count);
    free(Start_Point_count);
    free(Start_Next_value);
}
#pragma endregion
#pragma endregion
#pragma region Result
void InitResult()
{
}

void UpdateResult()
{
    SetPosition(10, 10);
    printf("!!게임 오버!!");
    SetPosition(10, 12);
    printf("점수 = %d", Start_point->point);
    Sleep(4000);
    InitLogo();
    scene = LOGO;
    ClearResult();
}

void ClearResult()
{
    free(Start_point);
}
#pragma endregion
#pragma region Record
void InitRecord()
{
}

void UpdateRecord()
{
}

void ClearRecord()
{
}
#pragma endregion
#pragma region Exit
void InitExit()
{
}

void UpdateExit()
{
    exit(0);
}

void ClearExit()
{
}
#pragma endregion

#pragma region CheckCrash
bool CheckCrash(int x, int y) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                int t = map[y + Start_Shap_BLOCK_UI->y][x + Start_Shap_BLOCK_UI->x];
                if (t == 1 || t == 2) {// 벽일 때, 블럭일 때
                    return true;//벽이나 블럭이면 true 반환
                }
            }
        }
    }
    return false;//아니면 false 반환
}
#pragma endregion
#pragma region CheckCount
void CheckCount(int x, int y) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (Start_Shap_BLOCK_UI->Block_shape[Start_Random->Random][Start_Shap_BLOCK_Value->Value][y][x] == 1) {
                int t = map[y + Start_Shap_BLOCK_UI->y][x + Start_Shap_BLOCK_UI->x];
                if (t == 1 || t == 2) {// 벽일 때, 블럭일 때
                    Start_Count->count++;
                }
            }
        }
    }
}
#pragma endregion
#pragma endregion