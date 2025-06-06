// BoxPusher.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <map>
using namespace std;

enum Object {
    OBJ_UNKNOWN,

    OBJ_SPACE,
    OBJ_WALL,
    OBJ_TARGET,
    OBJ_PLAYER,
    OBJ_PLAYER_ON_TARGET,
    OBJ_BOX,
    OBJ_BOX_ON_TARGET,
};

void gameContinue();
void gameFinsihed();
char getInput();
void updateGame(char input, Object* sMap, int width, int height, int& px, int& py, int& numFreeBox);
int transPosAbs(int x, int y, int width);
void draw(const Object* sMap, int width, int height);
Object dictFind(char c);
int transPosX(int position, int width);
int transPosY(int position, int width);
void initialization(const char map[], int width, Object* state, int &px, int &py, int &numFreeBox);

const map<char, Object> dictChar2Object{
    {' ', OBJ_SPACE},
    {'#', OBJ_WALL},
    {'.', OBJ_TARGET},
    {'p', OBJ_PLAYER},
    {'P', OBJ_PLAYER_ON_TARGET},
    {'o', OBJ_BOX},
    {'O', OBJ_BOX_ON_TARGET},
};

const char listIndex2Char[] = { '*', ' ', '#', '.' , 'p' , 'P' , 'o' , 'O' };

const char gMap[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########\n\
";

const int gWidth = 8;
const int gHeight = 5;

int main()
{
    bool isFinish = false;
    int px, py, numFreeBox = 0;
    Object* sMap = new Object[gWidth * gHeight];

    initialization(gMap, gWidth, sMap, px, py, numFreeBox);
    while (true) {
        draw(sMap, gWidth, gHeight);
        if (!numFreeBox) {
            break;
        }
        gameContinue();
        //cout << numFreeBox << endl;
        char opt = getInput();
        updateGame(opt, sMap, gWidth, gHeight, px, py, numFreeBox);
    }
    gameFinsihed();
    delete[] sMap;
    sMap = 0;

    return 0;
}

void gameContinue() {
    cout << "Press w a s d to move the player:";
}

void gameFinsihed() {
    cout << "Congratulation! You Finsih the Game!" << endl;
}

char getInput() {
    char c;
    cin >> c;
    return c;
}

void updateGame(char input, Object* sMap, int width, int height, int& px, int& py, int& numFreeBox) {
    int dx = 0, dy = 0;
    int tAbs;
    switch (input) {
    case 'a':
        dy = -1;
        break;
    case 'd':
        dy = 1;
        break;
    case 'w':
        dx = -1;
        break;
    case 's':
        dx = 1;
        break;
    default:
        break;
    }
    int nx, ny;
    nx = px + dx;
    ny = py + dy;
    //cout << nx << " " << ny << " " << transPosAbs(nx, ny, width) << endl;
    switch (sMap[transPosAbs(nx, ny, width)]) {
    case OBJ_WALL:
        break;
    case OBJ_BOX:
    case OBJ_BOX_ON_TARGET:
        dx += nx;
        dy += ny;
        tAbs = transPosAbs(dx, dy, width);
        if (sMap[tAbs] == OBJ_WALL || sMap[tAbs] == OBJ_BOX || sMap[tAbs] == OBJ_BOX_ON_TARGET) {
            break;
        }
        else if (sMap[tAbs] == OBJ_TARGET) {
            sMap[tAbs] = OBJ_BOX_ON_TARGET;
            numFreeBox--;
        }
        else {
            sMap[tAbs] = OBJ_BOX;
        }
    case OBJ_TARGET:
    case OBJ_SPACE:
        tAbs = transPosAbs(px, py, width);
        sMap[tAbs] = (sMap[tAbs] == OBJ_PLAYER_ON_TARGET) ? OBJ_TARGET : OBJ_SPACE;
        px = nx;
        py = ny;

        tAbs = transPosAbs(px, py, width);
        if (sMap[tAbs] == OBJ_BOX_ON_TARGET || sMap[tAbs] == OBJ_TARGET) {
            if (sMap[tAbs] == OBJ_BOX_ON_TARGET) {
                numFreeBox++;
            }
            sMap[tAbs] = OBJ_PLAYER_ON_TARGET;
        }
        else {
            sMap[tAbs] = OBJ_PLAYER;
        }
        break;
    default:
        break;
    }
}

int transPosAbs(int x, int y, int width) {
    return x * width + y;
}

void draw(const Object* sMap, int width, int height) {
    system("cls");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << listIndex2Char[sMap[transPosAbs(i, j, width)]];
            //cout << transPosAbs(i, j, width);
        }
        cout << endl;
    }
}

Object dictFind(char c) {
    auto iter = dictChar2Object.find(c);
    if (iter != dictChar2Object.end()) {
        return iter->second;
    }
    else {
        return OBJ_UNKNOWN;
    }
}

int transPosX(int position, int width) {
    return position / width;
}

int transPosY(int position, int width) {
    return position % width;
}

void initialization(const char map[], int width, Object* state, int &px, int &py, int &numFreeBox) {
    int pointer_map = 0;
    int pointer_state = 0;
    while (map[pointer_map]) {
        Object tObj = dictFind(map[pointer_map]);
        if (tObj != OBJ_UNKNOWN) {
            state[pointer_state] = tObj;
            if (tObj == OBJ_PLAYER || tObj == OBJ_PLAYER_ON_TARGET) {
                px = transPosX(pointer_state, width);
                py = transPosY(pointer_state, width);
            }
            else if (tObj == OBJ_TARGET) {
                numFreeBox++;
            }
            pointer_state++;
        }
        pointer_map++;
        //cout << pointer_state << " " << pointer_map << endl;
        //char x;
        //cin >> x;
    }
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
