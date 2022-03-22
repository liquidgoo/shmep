#include "Engine.h"
#include "PlaceholderSprite.h"
#include "Camera.h"
#include "Transform.h"
#include "PlayerController.h"
#include "SimplePhysics.h"
#include "Gravity.h"
#include "EnemySpawner.h"
#include "CollisionHandler.h"
#include "Scene.h"
#include "GameObject.h"
#include "StartGameScript.h"
#include "RectangleCollider.h"
#include "BitmapSprite.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Engine engine;
RECT clientRect;

void mainSceneSetup() {
    GameObject* player = new GameObject();
    player->tag = "Player";
    player->transform->scale = { 0.5, 0.5 };
    player->addComponent(BitmapSprite::getInstance("Assets\\ship1.bmp"));

    SimplePhysics* playerPhysics = new SimplePhysics();
    PlayerController* playerController = new PlayerController();
    Gravity* playerGravity = new Gravity();
    playerController->playerPhysics = playerPhysics;
    playerGravity->physics = playerPhysics;
    player->addComponent(playerController);
    player->addComponent(playerPhysics);
    player->addComponent(playerGravity);
    player->addComponent(new RectangleCollider(BitmapSprite::getInstance("Assets\\ship1.bmp")->size/2));
    player->addComponent(new CollisionHandler());

    EnemySpawner* spawner = new EnemySpawner();
    spawner->player = player;
    player->addComponent(spawner);

    engine.scene->addGameObject(player);

    Camera* cam = new Camera();
    GameObject* camObject = new GameObject();
    camObject->tag = "Camera";
    cam->inGameSize = { 400, 225 };
    cam->viewPortRect = { 0, 0, 1, 1 };
    camObject->addComponent(cam);
    camObject->transform->position = player->getSprite()->size / 4 - cam->inGameSize / 2;
    engine.scene->camObjects.push_back(camObject);

    player->addChild(camObject);

}



void startGameSetup() {
    GameObject* listener = new GameObject();
    listener->addComponent(new StartGameScript());
    engine.scene->addGameObject(listener);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"SHMEP";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"SHMEP",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);



    std::srand(std::time(0));
    engine.scene = new Scene();
    startGameSetup();


    MSG msg = { };
    while (true)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        engine.update();
        InvalidateRect(hwnd, NULL, false);
    }
    return 0;
}

HBITMAP hBitmap;
BITMAP bmp;

void paintBack(HDC hdc) {
    if (hBitmap == NULL) return;
    if (engine.scene->camObjects.empty()) return;
    POINT pos;
    Transform t = engine.scene->camObjects[0]->getWorldTransform();
    pos.x =(long) t.position.x % bmp.bmWidth;
    pos.y =(long) t.position.y % bmp.bmHeight;
    HDC bitmapHdc = CreateCompatibleDC(hdc);
    SelectObject(bitmapHdc, hBitmap);
    for (int i = -1; i < 3; i++) {
        for (int j = -1; j < 2; j++) {

            BitBlt(hdc, clientRect.right - pos.x + bmp.bmWidth * i, clientRect.bottom + pos.y+ bmp.bmHeight * j, bmp.bmWidth, bmp.bmHeight, bitmapHdc, 0, 0, SRCCOPY);
        }
    }
    DeleteDC(bitmapHdc);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        hBitmap = (HBITMAP)LoadImageA(NULL, "Assets\\back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(hBitmap, sizeof(bmp), &bmp);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_ERASEBKGND:
        break;
    case WM_SIZE:
        GetClientRect(hwnd, &clientRect);
        engine.clientRect = clientRect;
        break;
    case WM_MOUSEMOVE:
        GetCursorPos(&engine.cursorPos);
        ScreenToClient(hwnd, &engine.cursorPos);
        break;
    case WM_LBUTTONDOWN:
        engine.lmbPress = true;
        break;
    case WM_LBUTTONUP:
        engine.lmbPress = false;
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT     ps;
        HDC             hdc;
        HDC             bufferHDC;
        HBITMAP          hBufferBitmap;

        hdc = BeginPaint(hwnd, &ps);

        bufferHDC = CreateCompatibleDC(hdc);
        
        hBufferBitmap = CreateCompatibleBitmap(hdc, clientRect.right * 3, clientRect.bottom * 3);
        SelectObject(bufferHDC, hBufferBitmap);
        RECT bufRect = { clientRect.right * 3, clientRect.bottom * 3 };
        //FillRect(bufferHDC, &bufRect,(HBRUSH) GetStockObject(WHITE_BRUSH));
        paintBack(bufferHDC);

        SetGraphicsMode(bufferHDC, GM_ADVANCED);
        

        engine.paint(bufferHDC);
        ModifyWorldTransform(bufferHDC, NULL, MWT_IDENTITY);
        SetGraphicsMode(bufferHDC, GM_COMPATIBLE);

        BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, bufferHDC, clientRect.right, clientRect.bottom, SRCCOPY);

        DeleteObject(hBufferBitmap);
        DeleteDC(bufferHDC);

        EndPaint(hwnd, &ps);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 1;
}