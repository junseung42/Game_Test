#include "Stage.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

void Stage::Init()
{
    player_x = 4;//플레이어의 초기 좌표
    player_y = 8;

    apple_x = 12;//사과의 초기 좌표
    apple_y = 8;

    head = new Node;//꼬리 할당
    head->tail_x = 0;
    head->tail_y = 0;

    count = 0;

    direction = 0;//기본방향 오른쪽
}

void Stage::Update()
{
    Sleep(80);
#pragma region 맵 표현
    for (int y = 0; y < Screen_Vertical_Size; y++)
    {
        for (int x = 0; x < Screen_Width_Size; x++)
        {
            switch (map[y][x])
            {
            case 0:
                break;
            case 1://벽
                DoubleBuffer::Get()->WriteBuffer(x, y, "■", Yellow);
                break;
            case 2://뱀 머리
                DoubleBuffer::Get()->WriteBuffer(x, y, "★", White);
                break;
            case 3://뱀 꼬리
                DoubleBuffer::Get()->WriteBuffer(x, y, "※", White);
                break;
            case 4://사과
                DoubleBuffer::Get()->WriteBuffer(x, y, "♥", White);
                break;
            default:
                break;
            }
        }
    }
#pragma endregion
#pragma region 이동
    if (GetAsyncKeyState(VK_RIGHT))
    {
        direction = 0;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        direction = 1;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        direction = 2;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        direction = 3;
    }

    switch (direction)
    {
    case RIGHT:
        print();
        player_x++;
        break;
    case LEFT:
        print();
        player_x--;
        break;
    case UP:
        print();
        player_y--;
        break;
    case DOWN:
        print();
        player_y++;
        break;
    default:
        break;
    }
#pragma endregion
#pragma region 충돌처리
    if (map[player_y][player_x] == 1 || map[player_y][player_x] == 3)
    {
        SceneManager::Get()->result_value = 0;
        SceneManager::Get()->SetScene(RESULT);
        return;
    }
#pragma endregion  
#pragma region 맵 초기화
    for (int y = 1; y < Screen_Vertical_Size - 1; y++)
    {
        for (int x = 1; x < Screen_Width_Size - 1; x++)
        {
            map[y][x] = 0;
        }
    }
#pragma endregion
#pragma region 맵에 값 넣기
    map[player_y][player_x] = 2;//뱀의 머리
    map[apple_y][apple_x] = 4;//사과
    Node* temp = head;
    while (temp->next != nullptr) {//head는 플레이어의 값이 들어가 있으니깐 항상 다음 노드부터 검사
        map[temp->tail_y][temp->tail_x] = 3;//뱀의 꼬리
        temp = temp->next;
    }
#pragma endregion
#pragma region 사과 먹으면 생기는 일
    if (apple_x == player_x && apple_y == player_y)//플레이어와 사과의 좌표가 같다면
    {
        count++;
        Node* test = new Node;//추가할 노드 할당
        Node* temp = head;
        while (temp->next != nullptr)//마지막 노드를 찾는 로직
        {
            temp = temp->next;
        }
        temp->next = test;//마지막 노드 뒤쪽에 추가할 노드의 주소를 저장

        test->tail_x = temp->tail_x;//마지막 노드의 좌표값 = 마지막 전 노드의 좌표 값
        test->tail_y = temp->tail_y;//마지막 노드의 좌표값 = 마지막 전 노드의 좌표 값

        bool tf = true;
        while (tf)
        {
            apple_x = 1 + (rand() % 17);
            apple_y = 1 + (rand() % 17);
            if (map[apple_y][apple_x] != 1 && map[apple_y][apple_x] != 2 && map[apple_y][apple_x] != 3)
            {
                tf = false;
            }
        }
    }
#pragma endregion
    if (count >= 288)
    {
        SceneManager::Get()->result_value = 1;
        SceneManager::Get()->SetScene(RESULT);
        return;
    }
}

#pragma region 이동 로직
void Stage::print()
{
    //머리부분의 좌표값은 player이 갖고있고 꼬리부분은 노드가 가지고 있음 즉(head는 첫 꼬리의 좌표를 가지고 있음)
    Node* temp = head;
    //뱀의 머리부분은 노드가 아니니깐 while문 밖에 설정 해두고
    //while문 안에는 뱀의 꼬리 즉 노드들 끼리만 값을 설정
    int a_x = player_x;//뱀의 머리
    int a_y = player_y;

    while (temp->next != nullptr)
    {
        int b_x = temp->tail_x;//뒤에있는 값을 임시저장
        int b_y = temp->tail_y;

        temp->tail_x = a_x;//앞에있는 값을 뒤쪽에 저장
        temp->tail_y = a_y;

        a_x = b_x;//꼬리 부분이 다시 기준점(머리)가 되면서 계속 값을 전달
        a_y = b_y;

        temp = temp->next;
    }
}
#pragma endregion