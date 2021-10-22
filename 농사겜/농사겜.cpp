// 농사겜.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#pragma warning(disable :4996)
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <cmath>

char f_1[30] = { "괭이 내구도 수리    " }, s_1[30] = { "낫 내구도 수리     " }, f_2[30] = { "괭이 업그레이드     " }, s_2[30] = { "낫 업그레이드      " }, f_3[30] = { "씨앗 구매         " }, s_3[30] = { "물뿌리개 업그레이드 " }, f_4[30] = { "비료 구매         " }, s_4[30] = { "판매          " }, hoe[] = "hoe", scythe[] = "scythe", watering_can[] = "watering can", seed[] = "seed";
int i, j, instore = 0, ground[20][20], p_y = 9, p_x = 9, cur_time = 0, piggy = 100, warning_time = 0, water_left = 100, max_water_left, hoe_durability = 20, scythe_durability = 20, k, max_hoe_durability = 20, max_scythe_durability = 20, render_time = 0, h_money_needed = 20, s_money_needed = 20, selected_tool = 1;
float s_button_n = 1;
char warnig_message[50],space, no_h_d[] = "no enough durability (hoe)", no_s_d[] = { "no enough durability (scythe)" }, no_money[] = "no enough money", empty[50] = { NULL, },s_tool[20];
int buy = 0, page = 0, dot_$[12][10] = { {0,0,0,0,1,1,0,0,0,0},{0,0,1,1,1,1,1,1,0,0},{0,1,1,0,1,1,0,1,1,0},{0,1,1,0,1,1,0,1,1,0},{0,1,1,0,1,1,0,0,0,0},{0,0,1,1,1,1,0,0,0,0},{0,0,0,0,1,1,1,1,0,0},{0,0,0,0,1,1,0,1,1,0},{0,1,1,0,1,1,0,1,1,0},{0,1,1,0,1,1,0,1,1,0},{0,0,1,1,1,1,1,1,0,0},{0,0,0,0,1,1,0,0,0,0}, };

typedef struct plant {
    int t_s;//time start
    int t_h;//time harvested
    int p_k;//plant kind
    int g_s=0;//ground status
    bool i_w=0;//is_watered
}pnt;

typedef struct button {
    char first[30];
    char second[30];
}bt;

bt b_store[4];

pnt land[20][20] = {0,};

void CursorView(char show)//커서숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void b_interact(){
    
}

void SidePrint(int n) {//옆애 갈피 출력
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 10 << 4);
    if (n == 0)printf("     ");
    printf("%5s\n", "농장");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 6 << 4);
    if (n == 1)printf("     ");
    printf("%5s\n", "상점");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 9 << 4);
    if (n == 2)printf("     ");
    printf("%5s\n", "스텟");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14 << 4);
    if (n == 3)printf("     ");
    printf("%5s\n", "은행");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void render() {//랜더링
    system("mode con: cols=120 lines=30");
    int key;
    system("@cls || clear");
    
    if (instore != 1) {
        //땅 랜더링
        if (page == 0) {
            SidePrint(page);
            for (i = 0; i < 20; i++) {
                printf("             ");
                for (j = 0; j < 20; j++) {
                    if (clock() - warning_time > 2000) {
                        strcpy_s(warnig_message, empty);
                    }
                    if (i == p_y && j == p_x) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        printf("■");
                    }
                    else {
                        switch (land[j][i].g_s)
                        {
                        case 0:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 << 4);
                            printf("  ");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            break;
                        case 1:
                            if (land[j][i].i_w == 1) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 << 4);
                                printf("  ");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            }
                            else {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 << 4);
                                printf("  ");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            }
                            break;
                        case 2:
                            if (land[j][i].i_w == 1) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | 6 << 4);
                                printf("ㆍ");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            }
                            else {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | 8 << 4);
                                printf("ㆍ");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                            }
                            break;
                        case 3:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3 | 6 << 4);
                            printf("⊙");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                            break;
                        case 4:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3 | 6 << 4);
                            printf("♤");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            break;
                        case 5:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3 | 6 << 4);
                            printf("♠");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            break;
                        }
                    }
                    if (i == 0 && j == 19) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                  ┌──────────────────────────┐   ");
                    }
                    else if (i == 1 && j == 19) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                  │   piggy : %14d │  ", piggy);
                    }
                    else if (i == 2 && j == 19) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                  └──────────────────────────┘  ");

                    }
                    else if (i == 5 && j == 19) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        printf("                 %30s", warnig_message);
                    }
                    else if (i == 10 && j == 19) {
                        switch (selected_tool)
                        {
                        case 0:
                            printf("                        hoe_durability");
                            break;
                        case 1:
                            printf("                        scythe_durability");
                            break;
                        case 2:
                            printf("                        water_left");
                            break;
                        }
                    }
                    else if (i == 11 && j == 19) {
                        switch (selected_tool)
                        {
                        case 0:
                            strcpy_s(s_tool, hoe);
                            break;
                        case 1:
                            strcpy_s(s_tool, scythe);
                            break;
                        case 2:
                            strcpy_s(s_tool, watering_can);
                            break;
                        case 3:
                            strcpy_s(s_tool, seed);
                            break;
                        }



                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                        switch (selected_tool)
                        {
                        case 0:
                            printf("                      [");
                            for (k = 1; k < 21; k++) {
                                if (k < hoe_durability / ((float)max_hoe_durability / 20) + 1) {
                                    if ((hoe_durability / ((float)max_hoe_durability / 20) + 1) == 0)
                                    {
                                        printf(" ");
                                    }
                                    else {
                                        printf("=");
                                    }
                                }
                                else {
                                    printf(" ");
                                }
                            }
                            printf("]");
                            break;
                        case 1:
                            printf("                      [");
                            for (k = 1; k < 21; k++) {
                                if (k < scythe_durability / ((float)max_scythe_durability / 20) + 1) {
                                    if ((scythe_durability / ((float)max_scythe_durability / 20) + 1) == 0)
                                    {
                                        printf(" ");
                                    }
                                    else {
                                        printf("=");
                                    }
                                }
                                else {
                                    printf(" ");
                                }
                            }
                            printf("]");
                            break;
                        case 2:
                            printf("                      [");
                            for (k = 1; k < 21; k++) {
                                if (k < water_left / ((float)max_water_left / 20) + 1) {
                                    if ((water_left / ((float)max_water_left / 20) + 1) == 0)
                                    {
                                        printf(" ");
                                    }
                                    else {
                                        printf("=");
                                    }
                                }
                                else {
                                    printf(" ");
                                }
                            }
                            printf("]");

                            break;
                        }

                    }
                    else if (i == 16 && j == 19) {

                        printf("                      selected_tool:%s", s_tool);
                    }

                }
                printf("\n");
            }
        }
    }
    else if(page==1){//상점 랜더링
    SidePrint(page);
        for (i = 1; i < 5; i++) {//버튼, 돈 랜더링 (읽지 말 것)
            if (i == (round(s_button_n / 2))) {
                if ((int)s_button_n % 2 == 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("             ┌──────────────────────────┐  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ");
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                ┌──────────────────────────┐ \n");
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("             │      %20s│  ", b_store[i - 1].first);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("┃      %20s┃ ", b_store[i - 1].second);
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                │   piggy : %14d │  \n", piggy);
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("             │                          │  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("┃                          ┃ ");
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("                └──────────────────────────┘  \n");
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("             └──────────────────────────┘  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("             ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("┌──────────────────────────┐  ");
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("               ┌──────────────────────────┐ \n");
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("             ┃      % 20s┃  ", b_store[i - 1].first);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("│      % 20s│  ", b_store[i - 1].second);
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("               │   piggy : %14d │  \n", piggy);
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("             ┃                          ┃  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("│                          │  ");
                    if (i == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                        printf("               └──────────────────────────┘  \n");
                    }
                    else {
                        printf("\n");
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛  ");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    printf("└──────────────────────────┘  \n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                printf("             ┌──────────────────────────┐  ");
                printf("┌──────────────────────────┐  ");
                if (i == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    printf("               ┌──────────────────────────┐ \n");
                }
                else {
                    printf("\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                printf("             │      % 20s│  ", b_store[i - 1].first);
                printf("│      % 20s│  ", b_store[i - 1].second);
                if (i == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    printf("               │   piggy : %14d │  \n", piggy);
                }
                else {
                    printf("\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                printf("             │                          │  ");
                printf("│                          │  ");
                if (i == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    printf("               └──────────────────────────┘  \n");
                }
                else {
                    printf("\n");
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                printf("             └──────────────────────────┘  ");
                printf("└──────────────────────────┘  \n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        }
            if (buy == 1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);  

            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        switch ((int)s_button_n)
        {
        
        case 1:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    괭이 내구도 수리  (20c)                                                             │  \n             │  괭이의 내구도를 20만큼 채웁니다.                           괭이 내구도:%3d/%3d        │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", hoe_durability, max_hoe_durability, " ");
            break;
        case 2:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │     낫 내구도 수리  (20c)                                                              │  \n             │   낫의 내구도를 20만큼 채웁니다.                            낫 내구도:%3d/%3d          │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", scythe_durability, max_scythe_durability, " ");
            break;
        case 3:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │     괭이 내구도 업그레이드  (%3dc)                                                     │  \n             │   괭이의 최대 내구도를 +5 합니다.                   현재 최대 괭이 내구도:%3d          │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ",h_money_needed, max_hoe_durability, " ");
            break;
        case 4:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    낫 내구도 업그레이드  (%3dc)                                                        │  \n             │   낫의 최대 내구도를 +5 합니다.                       현재 최대 낫 내구도:%3d          │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ",s_money_needed, max_scythe_durability, " ");

            break;
        case 5:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    --준비중--   (??c)                                                                  │  \n             │                                  --아직 준비중입니다--                                 │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", " ");
            break;
        case 6:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    --준비중--   (??c)                                                                  │  \n             │                                  --아직 준비중입니다--                                 │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", " ");

            break;
        case 7:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    --준비중--   (??c)                                                                  │  \n             │                                  --아직 준비중입니다--                                 │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", " ");

            break;
        case 8:
            printf("\n\n");
            printf("             ┌────────────────────────────────────────────────────────────────────────────────────────┐  \n             │    --준비중--   (??c)                                                                  │  \n             │                                  --아직 준비중입니다--                                 │  \n             │%-88s│  \n             └────────────────────────────────────────────────────────────────────────────────────────┘  ", " ");
            break;
        }                    
        if (buy == 1) {
            buy = 0;
            Sleep(50);
            render();
        }

        /*for (int i = 0; i < 67; i++) {
            cut_2[i] = item_desc[(int)s_button_n - 1][i + 67];
            if (cut_2[i] == -2)cut_2[i] = NULL;
        }    - 전희준 - */
        CursorView(0);
    }
    if (page == 2) {//스텟 렌더링
    SidePrint(page);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n\n\n\t\t\t물뿌리기 ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 7 << 4);
    printf("  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 8 << 4);
    printf("        ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    if (page == 3) {//은행 랜더링
        SidePrint(page);
        for (i = 0; i < 12; i++) {
            printf("                                                       ");
            for (j = 0; j < 10; j++) {
                if (dot_$[i][j]) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14 << 4);
                    printf(" ");
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}

void map_load() {//로드
    int line[21];
    FILE* fp = fopen("map_ground.txt", "r");
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            fscanf(fp, " %d",&line[i]);
            land[i][j].g_s = line[i];
            }
        
    }
    fclose(fp);
    FILE* fpp = fopen("map_water.txt", "r");
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            fscanf(fpp,"%d", &line[i]);
            land[i][j].i_w = line[i];
        }
    }
    fclose(fpp);
    FILE* fps = fopen("player_stat.txt", "r");
    fscanf(fps, "%d %d %d %d %d %d %d %d %d", &piggy, &max_water_left, &water_left, &scythe_durability, &max_scythe_durability, &hoe_durability, &max_hoe_durability, &h_money_needed, &s_money_needed);
    fclose(fps);
    render();
}

void save_all() {//세이브
    system("@cls || clear");
    
    FILE* fp = fopen("map_ground.txt", "w");
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {

            fprintf(fp, " %d", land[i][j].g_s);
        }
        fprintf(fp, "\n");
        
    }
    fclose(fp);

    FILE* fpp = fopen("map_water.txt", "w");
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {

            fprintf(fpp, " %d", land[i][j].i_w);
        }
        fprintf(fp, "\n");
        
    }
    fclose(fpp);
    FILE* fps = fopen("player_stat.txt", "w");
    fprintf(fps, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",piggy,max_water_left,water_left,scythe_durability,max_scythe_durability,hoe_durability,max_hoe_durability,h_money_needed,s_money_needed);
    fclose(fps);
    printf("saved!");
    render();

}

void _plant() {//심기
    if(land[p_x][p_y].g_s==0){
        if (hoe_durability > 0) {
            land[p_x][p_y].g_s = 1;
            land[p_x][p_y].t_h=0;
            hoe_durability--;
            render();
        }
        else {
            strcpy_s(warnig_message, no_h_d);
            warning_time = clock();
            render();
        }
    }
}

void _seed() {//심기
    if (land[p_x][p_y].g_s == 1) {
        if (piggy > 0) {
            land[p_x][p_y].g_s = 2;
            if (land[p_x][p_y].i_w != 0) {
                land[p_x][p_y].t_s = clock();
            }
            piggy -= 5;
            render();
        }
        else {
            strcpy_s(warnig_message, no_money);
            warning_time = clock();
            render();
        }
    }
}

void harvest() {//수확
    if (land[p_x][p_y].g_s == 5) {
        if (scythe_durability > 0) {
            if (land[p_x][p_y].t_h == 1) {
                land[p_x][p_y].g_s = 0;
            }
            else {
                land[p_x][p_y].g_s = 1;
                land[p_x][p_y].t_h++;
            }

            land[p_x][p_y].i_w = 0;
            piggy += 10;
            render();
            scythe_durability--;
        }
        else {
            strcpy_s(warnig_message, no_s_d);
            warning_time = clock();
            render();
        }

    }
}

void t_check() {//고정 업데이트
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            if (land[j][i].g_s > 1 && land[j][i].g_s < 5) {
                cur_time = clock();
                if (cur_time - land[j][i].t_s >= 3000) {
                    if (land[j][i].g_s == 2) {
                        if (land[j][i].i_w == 1) {
                            land[j][i].g_s++;
                            land[j][i].t_s = cur_time;
                        }
                    }
                    else {
                        land[j][i].g_s++;
                        land[j][i].t_s = cur_time;

                    }




                }
            }
        }
    }
}

void b_set() {//상점 버튼 세팅
    strcpy_s(b_store[0].first, f_1);
    strcpy_s(b_store[0].second, s_1);
    strcpy_s(b_store[1].first, f_2);
    strcpy_s(b_store[1].second, s_2);
    strcpy_s(b_store[2].first, f_3);
    strcpy_s(b_store[2].second, s_3);
    strcpy_s(b_store[3].first, f_4);
    strcpy_s(b_store[3].second, s_4);
}

void s_interact(){//상점 상호작용
    switch ((int)s_button_n)
    {
    case 1:
        if (piggy >= 25) {
            if (hoe_durability != max_hoe_durability) {
                piggy -= 20;
                hoe_durability += 20;
                if (hoe_durability > max_hoe_durability)
                    hoe_durability = hoe_durability - (hoe_durability % max_hoe_durability);
                buy = 1;
                render();
            }
        }
        break;
    case 2:
        if (piggy >= 25) {
            if (scythe_durability != max_scythe_durability) {
                piggy -= 20;
                scythe_durability += 20;
                if (scythe_durability > max_scythe_durability)
                    scythe_durability = scythe_durability - (scythe_durability % max_scythe_durability);
                buy = 1;
                render();
            }
        }
        break;
    case 3:
        if (piggy >= h_money_needed+5) {
            piggy -= h_money_needed;
            max_hoe_durability += 5;
            h_money_needed += 50;
            if (hoe_durability != max_hoe_durability) {
                hoe_durability = max_hoe_durability;
            }
            buy = 1;
            render();
        }
        break;
    case 4:
        if (piggy >= s_money_needed+5) {
            piggy -= s_money_needed;
            max_scythe_durability += 5;
            s_money_needed += 50;
            if (scythe_durability != max_scythe_durability) {
                scythe_durability = max_scythe_durability;
            }
            buy = 1;
            render();
        }
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    }


}

void water() {//물주기
    if (land[p_x][p_y].g_s == 1) {
        land[p_x][p_y].i_w = 1;

    }
    else if (land[p_x][p_y].g_s == 2) {
        land[p_x][p_y].i_w = 1;
        land[p_x][p_y].t_s = clock();
        render();
    }
}

void use() {//손에 든 템 사용
    switch (selected_tool)
    {
    case 0:
        if (page==0)
            _plant();
        break;
    case 1:
        if (page == 0)
            harvest();
        break;
    case 2:
        if (page == 0)
            water();
        break;
    case 3:
        if (page == 0) {
            _seed();
        }
    }

}

int main()
{
    int ren_time;
    ren_time = clock();
    b_set();
    render();
    int key;
    while (1) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key)
            {
            case 'h':
            case 'H':
                page++;
                page %= 4;
                if (page == 1) {
                    instore = 1;
                }
                else
                    instore = 0;
           
                
                render();
                break;
            case 'p':
            case 'P':
                use();
                break;
            case 's':
            case 'S':
                if (p_y < 19) {
                    if (page == 0) {
                        p_y++;
                        render();
                    }
                }
                break;
            case 'x':
            case 'X':
                map_load();
                break;
            case 'z':
            case 'Z':
                save_all();
                break;
            case 65:
            case 97:
                if (page == 0) {
                    if (p_x > 0) {
                        p_x--;
                        render();
                    }
                }
                break;
            case 68:
            case 100:
                if (page == 0) {
                    if (p_x < 19) {
                        p_x++;
                        render();
                    }
                }
                break;
            case 87:
            case 119:
                if (page == 0) {
                    if (p_y > 0) {
                        p_y--;
                        render();
                    }
                }
                break;
            case 224:

                key = _getch();
                switch (key)
                {
                case 77://오른쪽
                    if (instore) {
                        if ((int)s_button_n % 2 != 0)
                            s_button_n++;
                    }
                    else if(page==0){
                        if(selected_tool<3)
                        selected_tool++;
                    }
                    break;
                case 75://왼쪽
                    if (instore) {
                        if ((int)s_button_n % 2 != 1)
                            s_button_n--;
                    }
                    else if(page == 0){
                        if(selected_tool>0)
                        selected_tool--;
                    }
                    break;
                case 80://아래
                    if (instore) {
                        s_button_n += 2;
                    }
                    break;
                case 72://위
                    if (instore) {
                        s_button_n -= 2;
                    }
                    break;
                }
                if (s_button_n <= 0) {
                    s_button_n += 8;
                }
                else if (s_button_n > 8) {
                    s_button_n = (int)s_button_n % 8;
                }
                    render();

                break;
            case 13:
                if (instore) {
                    s_interact();
                }
                break;


            }

        }
        if (clock() - ren_time >= 1000) {//식물 업데이트
            t_check();
            if (!instore) {
                render();

            }
            ren_time = clock();
        }

    }

}
