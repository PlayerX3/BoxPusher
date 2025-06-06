// BoxPusher.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
using namespace std;

char getInput();
bool updateGame(char input, char map[5][8], char rmap[5][8], int target[2][2], int &x, int &y);
void draw(char map[5][8], bool isFinished);
bool isFinished(char map[5][8], int target[2][2]);

int main()
{
    char rmap[5][8] = {
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '.', '.', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
    };
    char map[5][8] = {
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '.', '.', ' ', 'p', ' ', '#'},
        {'#', ' ', 'o', 'o', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
    };
    int x = 1;
    int y = 5;
    int target[2][2]{
        {1, 2},
        {1, 3}
    };
    bool isFinish = false;

    draw(map, isFinish);
    while (true) {
        char opt = getInput();
        isFinish = updateGame(opt, map, rmap, target, x, y);
        draw(map, isFinish);
        if (isFinish) {
            break;
        }
    }
}

char getInput() {
    char c;
    cin >> c;
    return c;
}

bool updateGame(char input, char map[5][8], char rmap[5][8], int target[2][2], int& x, int& y) {
    int bx = 0, by = 0;
    switch (input) {
    case 'a':
        bx = 0;
        by = -1;
        break;
    case 'd':
        bx = 0;
        by = 1;
        break;
    case 'w':
        bx = -1;
        by = 0;
        break;
    case 's':
        bx = 1;
        by = 0;
        break;
    default:
        break;
    }
    int xx, yy;
    xx = x + bx;
    yy = y + by;
    cout << xx << " " << yy << endl;
    switch (map[xx][yy]) {
    case '#':
        break;
    case 'o':
        bx += xx;
        by += yy;
        if (map[bx][by] == '#' || map[bx][by] == 'o') {
            break;
        }
        else {
            map[bx][by] = 'o';
        }
    case '.':
    case ' ':
        map[x][y] = rmap[x][y];
        x = xx;
        y = yy;
        map[x][y] = 'p';
        if (isFinished(map, target)) {
            map[x][y] = rmap[x][y];
            map[x][y] = 'p';
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void draw(char map[5][8], bool isFinished) {
    system("cls");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    if (isFinished) {
        cout << "Congratulation! You win!";
    }
    else {
        cout << "left: a\nright: d\nup: w\ndown: s\nPress your option:";
    }
    
}

bool isFinished(char map[5][8], int target[2][2]) {
    //draw(map, false);
    for (int i = 0; i < 2; i++) {
        if (map[target[i][0]][target[i][1]] != 'o') {
            return false;
        }
    }
    return true;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
