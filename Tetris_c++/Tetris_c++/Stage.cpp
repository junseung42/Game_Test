#include "Stage.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"
#include "TetrisMap.h"
#include <cstring>
#include <string> 

void Stage::Init()
{
#pragma region block_shape
    //임시배열
    int temp[7][4][4][4] = {
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
    // temp 배열을 block_shape에 복사
    memcpy(block_shape, temp, sizeof(temp));
#pragma endregion
#pragma region map 초기화
    for (int y = 0; y < Screen_Vertical_Size - 1; y++)
    {
        for (int x = 0; x < Screen_Width_Size - 1; x++)
        {
            if (TetrisMap::Get()->map[y][x] != 1)
            {
                TetrisMap::Get()->map[y][x] = 0;
            }
        }
    }
#pragma endregion
    block_x = 5;//블럭의 x값
    block_y = 0;//블럭의 y값
    block_random = rand() % 7;//블럭의 7가지 모양
    block_value = 0;//블럭의 회전 상태
    blocK_count = 0;//벽 밖으로 나간 블럭의 갯수 체크
    block_point = 0;//테트리스 점수
    block_pointcount = 0;//1줄에 몇개의 블럭이 차있는지 체크
    block_neednext = 0;//새로운 블럭이 필요한 경우 1 = 필요, 0 = 불필요
}

void Stage::Update()
{
#pragma region 설명
    DoubleBuffer::Get()->WriteBuffer(15, 8, "HOLD", White);
    DoubleBuffer::Get()->WriteBuffer(21, 8, "NEXT BLOCK", White);
    string scoreText = "점수 = " + to_string(block_point);
    DoubleBuffer::Get()->WriteBuffer(15, 10, scoreText.c_str(), White);
    DoubleBuffer::Get()->WriteBuffer(15, 10, "", White);
    DoubleBuffer::Get()->WriteBuffer(15, 12, "조작법 -> 왼쪽으로 가기 = 왼쪽 방향키", White);
    DoubleBuffer::Get()->WriteBuffer(15, 14, "       -> 오른쪽으로 가기 = 오른쪽 방향키", White);
    DoubleBuffer::Get()->WriteBuffer(15, 16, "       -> 방향 돌리기 = 위쪽 방향키", White);
    DoubleBuffer::Get()->WriteBuffer(15, 18, "       -> Hold = c", White);
    DoubleBuffer::Get()->WriteBuffer(15, 20, "       -> 바로 내리기 = Space Bar", White);
#pragma endregion
#pragma region Next_block
    bool isNextMapEmpty = true;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (TetrisMap::Get()->Next_map[3 + y][3 + x] == 2)
            {
                isNextMapEmpty = false;
                break;
            }
        }
    }

    if (isNextMapEmpty)//도형이 없는경우
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {

                //초기화
                TetrisMap::Get()->Next_map[3 + y][3 + x] = 0;

                //도형을 홀드맵에 그리기
                if (block_shape[block_random][block_value][y][x] == 1)
                {
                    TetrisMap::Get()->Next_map[3 + y][3 + x] = 2;
                }

                //새로운 블력 생성
                block_x = 5;
                block_y = 0;
                block_random = rand() % 7;
                block_value = 0;
                blocK_count = 0;
            }
        }
    }
    //이거는 이상한듯
    else if (block_neednext)//바닥에 닿거나 홀드일 경우(새로운 도형이 필요한 경우)
    {
        int temp_shape[4][4] = { 0 };//임시저장 도형 초기화
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {

                //Next_map에 있는 도형을 임시저장공간에다가 그리기
                if (TetrisMap::Get()->Next_map[3 + y][3 + x] == 2)
                {
                    temp_shape[y][x] = 1;
                }

                //Next_map 초기화
                TetrisMap::Get()->Next_map[3 + y][3 + x] = 0;

                //Next_map에 있는 도형을 홀드맵에 그리기
                if (block_shape[block_random][block_value][y][x] == 1)
                {
                    TetrisMap::Get()->Next_map[3 + y][3 + x] = 2;
                }
            }
        }

        //Next_map에 임시 저장한 도형으로 교체
        for (int r = 0; r < 7; r++)
        {
            for (int v = 0; v < 4; v++)
            {
                bool isMatch = true;
                for (int y = 0; y < 4; y++)
                {
                    for (int x = 0; x < 4; x++)
                    {
                        if (temp_shape[y][x] != block_shape[r][v][y][x])//하나라도 불일치 하다면 나감
                        {
                            isMatch = false;
                            break;//x루프 탈출
                        }
                    }//여기로
                    if (!isMatch)//자동으로 참
                    {
                        break;//y루프탈출
                    }
                }//여기로
                if (isMatch)//r, v를 써야되기 때문에 여기까지만 나가기
                {
                    block_random = r;
                    block_value = v;
                }
            }
        }
        block_neednext = 0;
    }
#pragma endregion
#pragma region 블럭의 이동경로 표현
    for (int y = 0; y < Screen_Vertical_Size - 1; y++)
    {
        for (int x = 0; x < Screen_Width_Size - 1; x++)
        {
            if (TetrisMap::Get()->map[y][x] == 3)
            {
                TetrisMap::Get()->map[y][x] = 0;
            }
        }
    }
    int Befor_y = block_y;
    while (!CheckCrash(block_x, block_y + 1))
    {
        block_y++;//블록을 아래로 이동
    }
    //Start_Shap_BLOCK_UI->y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
    if (CheckCrash(block_x, block_y + 1) == true)
    {
        if (1)
        {
            // 현재 블록 저장
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    if (block_shape[block_random][block_value][y][x] == 1)
                    {
                        TetrisMap::Get()->map[block_y + y - 1][block_x + x] = 3;
                    }
                }
            }
        }
    }
    block_y = Befor_y;
#pragma endregion
#pragma region 블럭 표현
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (block_shape[block_random][block_value][y][x] == 1)
            {
                DoubleBuffer::Get()->WriteBuffer(block_x + x, block_y + y, "■", White);
            }
        }
    }
#pragma endregion
#pragma region Map 표현
    for (int y = 0; y < Screen_Vertical_Size; y++) {
        for (int x = 0; x < Screen_Width_Size; x++) {
            switch (TetrisMap::Get()->map[y][x])
            {
            case 0:
                break;
            case 1:
                DoubleBuffer::Get()->WriteBuffer(x, y, "□", Yellow);
                break;
            case 2:
                DoubleBuffer::Get()->WriteBuffer(x, y, "■", White);
                break;
            case 3:
                DoubleBuffer::Get()->WriteBuffer(x, y, "□", White);
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region Hold_map 표현
    for (int y = 0; y < Hold_Screen_Vertical_Size; y++) {
        for (int x = 0; x < Hold_Screen_Width_Size; x++) {
            switch (TetrisMap::Get()->Hold_map[y][x])
            {
            case 0:
                break;
            case 1:
                DoubleBuffer::Get()->WriteBuffer(x + Screen_Width_Size, y, "□", Yellow);
                break;
            case 2:
                DoubleBuffer::Get()->WriteBuffer(x + Screen_Width_Size, y, "■", White);
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region Next_map 표현
    for (int y = 0; y < Next_Screen_Vertical_Size; y++) {
        for (int x = 0; x < Next_Screen_Width_Size; x++) {
            switch (TetrisMap::Get()->Next_map[y][x])
            {
            case 0:
                break;
            case 1:
                DoubleBuffer::Get()->WriteBuffer(x + Screen_Width_Size + Hold_Screen_Width_Size, y, "□", Yellow);
                break;
            case 2:
                DoubleBuffer::Get()->WriteBuffer(x + Screen_Width_Size + Hold_Screen_Width_Size, y, "■", White);
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region 블럭 내리기
    //block_y + 1 = 벽 위에 블럭을 놓고싶음
    //block_y = 벽 이랑 충돌되게 블럭을 놓고싶음
    if (CheckCrash(block_x, block_y + 1) == true)//벽이나 블럭화된곳에 충돌이 일어나면 실행
    {
        return;//블록 이동 중단
    }
    else//충돌이 없으면
    {
        Sleep(200);
        block_y++;//블록 한 칸 아래로 이동
    }
#pragma endregion
#pragma region 바닥에 닿으면 블럭 처리
    if (CheckCrash(block_x, block_y + 1) == true)
    {
        if (1)
        {
            // 현재 블록 저장
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    if (block_shape[block_random][block_value][y][x] == 1)
                    {
                        //block_y + y - 1를 한 이유는 block_y + y이렇게 하면 벽이랑 충돌 나기 때문
                        TetrisMap::Get()->map[block_y + y - 1][block_x + x] = 2;//닿은 블럭을 맵에 2값으로 넣어 처리
                    }
                }
            }

            //새로운 블력 생성
            block_x = 5;
            block_y = 0;
            block_random = rand() % 7;
            block_value = 0;
            blocK_count = 0;
            block_neednext = 1;
        }
    }
#pragma endregion
#pragma region Hold
    if (GetAsyncKeyState(0x43))
    {
        // Hold_map에 도형이 없으면 ture, 있으면 false
        bool isHoldMapEmpty = true;
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (TetrisMap::Get()->Hold_map[3 + y][3 + x] == 2)
                {
                    isHoldMapEmpty = false;
                    break;
                }
            }
        }

        if (isHoldMapEmpty) {//도형이 없을 경우
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    //맵 초기화
                    TetrisMap::Get()->Hold_map[3 + y][3 + x] = 0;

                    //도형을 홀드맵에 그리기
                    if (block_shape[block_random][block_value][y][x] == 1)
                    {
                        TetrisMap::Get()->Hold_map[3 + y][3 + x] = 2;
                    }
                }
            }

            //새로운 블럭 생성
            block_x = 5;
            block_y = 0;
            block_random = rand() % 7;
            block_value = 0;
            blocK_count = 0;
            block_neednext = 1;
        }
        else //도형이 있을경우 
        {
            int temp_shape[4][4] = { 0 };//임시저장 도형 초기화
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {

                    //홀드맵에 있는 도형을 임시저장공간에다가 그리기
                    if (TetrisMap::Get()->Hold_map[3 + y][3 + x] == 2)
                    {
                        temp_shape[y][x] = 1;
                    }

                    //홀드맵 초기화
                    TetrisMap::Get()->Hold_map[3 + y][3 + x] = 0;

                    //플레이맵에 있는 도형을 홀드맵에 그리기
                    if (block_shape[block_random][block_value][y][x] == 1)
                    {
                        TetrisMap::Get()->Hold_map[3 + y][3 + x] = 2;
                    }
                }
            }

            //플레이 맵에 임시 저장한 도형으로 교체
            for (int r = 0; r < 7; r++)
            {
                for (int v = 0; v < 4; v++)
                {
                    bool isMatch = true;
                    for (int y = 0; y < 4; y++)
                    {
                        for (int x = 0; x < 4; x++)
                        {
                            if (temp_shape[y][x] != block_shape[r][v][y][x])//하나라도 불일치 하다면 나감
                            {
                                isMatch = false;
                                break;//x루프 탈출
                            }
                        }//여기로
                        if (!isMatch)//자동으로 참
                        {
                            break;//y루프탈출
                        }
                    }//여기로
                    if (isMatch)//r, v를 써야되기 때문에 여기까지만 나가기
                    {
                        block_random = r;
                        block_value = v;
                    }
                }
            }
        }
    }
#pragma endregion
#pragma region 블럭 이동
    if (GetAsyncKeyState(VK_RIGHT) & 0x8001)//block_x좌표를 오른쪽으로 이동
    {
        if (CheckCrash(block_x, block_y) == false)
        {
            block_x += 1;
        }
        if (CheckCrash(block_x, block_y) == true)
        {
            block_x -= 1;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8001)//block_x좌표를 왼쪽으로 이동
    {
        if (CheckCrash(block_x, block_y) == false)
        {
            block_x -= 1;
        }
        if (CheckCrash(block_x, block_y) == true)
        {
            block_x += 1;
        }
    }
    if (GetAsyncKeyState(VK_UP) & 0x8001)//형태변환
    {
        block_value++;
        if (block_value >= 4)
        {
            block_value = 0;
        }

        if (CheckCrash(block_x, block_y) == true)//형태변환시 충돌이 일어나면
        {
            if (block_x <= 5)//왼쪽 충돌시
            {
                CheckCount(block_x, block_y);
                block_x += blocK_count;//나간 블럭의 개수만큼 x값 옮김
                blocK_count = 0;
            }
            if (block_x >= 8)//오른쪽 충돌시
            {
                CheckCount(block_x, block_y);
                block_x -= blocK_count;//나간 블럭의 개수만큼 x값 옮김
                blocK_count = 0;
            }
            if (block_y >= 17)//아래 충돌시 
            {
                CheckCount(block_x, block_y);
                block_y -= blocK_count;//나간 블럭의 개수만큼 y값 옮김
                blocK_count = 0;
            }
        }
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8001)//block_y좌표를 바로 내리기
    {
        while (!CheckCrash(block_x, block_y + 1))
        {
            block_y++;//블록을 아래로 이동
        }
        block_y--;//마지막으로 이동한 위치는 충돌하므로 한 칸 위로 조정
    }
#pragma endregion
#pragma region 블럭 채우면 처리
    for (int y = Screen_Vertical_Size - 1; y >= 0; y--)
    {
        block_pointcount = 0;
        for (int x = 1; x < Screen_Width_Size - 1; x++)
        {
            if (TetrisMap::Get()->map[y][x] == 2)
            {
                block_pointcount++;
            }
        }
        if (block_pointcount >= 10)//1줄이 다 차있다면
        {
            block_point += 1;//점수를 올림
            for (int x = 0; y - x >= 0; x++)//다 차있는 행부터 위쪽 행이 얼마나 남아있는지 계산
            {
                for (int z = 1; z < Screen_Width_Size - 1; z++)//x축
                {
                    if (y - x - 1 >= 0)
                    {
                        TetrisMap::Get()->map[y - x][z] = TetrisMap::Get()->map[y - x - 1][z];//위쪽행을 아래쪽으로 덮기
                    }
                    else
                    {
                        TetrisMap::Get()->map[y - x][z] = 0;//가장 위쪽값 쓰래기값 방지
                    }
                }
            }
        }
    }
#pragma endregion
#pragma region 게임 오버
    if (CheckCrash(5, 0) == true)
    {
        SceneManager::Get()->SetScene(RESULT);
    }
#pragma endregion
}

#pragma region CheckCrash
//블럭이 벽, 블럭화된곳 에 충돌이 일어났는지 체크
bool Stage::CheckCrash(int x, int y)//현재 도형이 벽이나 블럭화된곳 에 곂치면 ture, 아니면 false
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (block_shape[block_random][block_value][y][x] == 1)
            {
                int t = TetrisMap::Get()->map[block_y + y][block_x + x];
                if (t == 1 || t == 2)//1 = 벽일 때, 2 = 블럭화 된곳
                {
                    return true;//벽이나 블럭화된곳 이면 true 반환
                }
            }
        }
    }
    return false;
}
#pragma endregion
#pragma region CheckCount
//블럭의 모양을 바꿀때 블럭의 도형이 얼마나 벽 밖으로 나갔는지 체크
void Stage::CheckCount(int x, int y)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (block_shape[block_random][block_value][y][x] == 1)
            {
                int t = TetrisMap::Get()->map[block_y + y][block_x + x];
                if (t == 1 || t == 2)//1 = 벽일 때, 2 = 블럭화 된곳
                {
                    blocK_count++;//벽 밖으로 나간 블럭의 갯수 체크
                }
            }
        }
    }
}
#pragma endregion