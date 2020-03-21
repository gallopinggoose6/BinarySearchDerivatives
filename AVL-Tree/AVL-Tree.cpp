// AVL-Tree.cpp : Defines the entry point for the application.
//
#define CATCH_CONFIG_RUNNER

#include "framework.h"
#include "AVL-Tree.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <catch2/catch.hpp>
#include <stdlib.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int runCatchTests(int argc, char* const argv[]) {
    return Catch::Session().run(argc, argv);
}

void traverse(AVLNode* current) {
	std::cout << "Data: " << current->getData() << ",\tBallance Factor: " << current->getBalfactor() << ",\tOccurrences: " << current->getOccurrences() << "\n";
	if (current->rightNode != nullptr) traverse(current->rightNode);
	if (current->leftNode != nullptr) traverse(current->leftNode);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	AllocConsole();
	FILE* pCout;
	freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCout, "CONIN$", "r", stdin);

    std::vector<std::string> arguments = { };

    /*std::vector<char*> argv;
    for (const auto& arg : arguments) argv.push_back((char*)arg.data());
    argv.push_back(nullptr);*/

    char* argv[] = {
    (char*)"--dir",
    (char*)"/some_path/",
    NULL
    };

    if (TEST) {
        int result = runCatchTests(1, argv);
        std::cout << "Press ENTER to continue...";
        std::getchar();
        return result;
    }

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AVLTREE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AVLTREE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AVLTREE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_AVLTREE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

TEST_CASE("Tree Creation and Deletion") {
    AVL* myTree = new AVL();
    REQUIRE(myTree->root == nullptr);
    delete myTree;
}

TEST_CASE("Node Addition") {
    AVL* myTree = new AVL();
    AVLNode** root = &myTree->root;

    myTree->add(10, *root);
    REQUIRE(*root != nullptr);
    REQUIRE((*root)->getBalfactor() == 0);
    REQUIRE((*root)->getData() == 10);
    REQUIRE((*root)->getOccurrences() == 1);
    REQUIRE((*root)->leftNode == nullptr);
    REQUIRE((*root)->rightNode == nullptr);

    myTree->add(14, *root);
    REQUIRE((*root)->getBalfactor() == 1);
    REQUIRE((*root)->rightNode != nullptr);
    REQUIRE((*root)->rightNode->getBalfactor() == 0);
    REQUIRE((*root)->rightNode->getData() == 14);
    REQUIRE((*root)->rightNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode == nullptr);

    myTree->add(14, *root);
    REQUIRE((*root)->getBalfactor() == 1);
    REQUIRE((*root)->rightNode->getOccurrences() == 2);
    REQUIRE((*root)->rightNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode == nullptr);
    
    myTree->add(5, *root);
    REQUIRE((*root)->getBalfactor() == 0);
    REQUIRE((*root)->leftNode != nullptr);
    REQUIRE((*root)->leftNode->getBalfactor() == 0);
    REQUIRE((*root)->leftNode->getData() == 5);
    REQUIRE((*root)->leftNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->leftNode == nullptr);
    
    myTree->add(20, *root);
    REQUIRE((*root)->getBalfactor() == 1);
    REQUIRE((*root)->rightNode != nullptr);
    REQUIRE((*root)->rightNode->getBalfactor() == 1);
    REQUIRE((*root)->rightNode->rightNode != nullptr);
    REQUIRE((*root)->rightNode->rightNode->getOccurrences() == 1);
    REQUIRE((*root)->rightNode->rightNode->getData() == 20);
    REQUIRE((*root)->rightNode->rightNode->getBalfactor() == 0);
    REQUIRE((*root)->rightNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode->rightNode == nullptr);
    REQUIRE((*root)->leftNode->leftNode == nullptr);
    
    myTree->add(13, *root);
    REQUIRE((*root)->getBalfactor() == 1);
    REQUIRE((*root)->rightNode->getBalfactor() == 0);
    REQUIRE((*root)->rightNode->leftNode != nullptr);
    REQUIRE((*root)->rightNode->leftNode->getOccurrences() == 1);
    REQUIRE((*root)->rightNode->leftNode->getData() == 13);
    REQUIRE((*root)->rightNode->leftNode->getBalfactor() == 0);
    REQUIRE((*root)->rightNode->leftNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->leftNode->leftNode == nullptr);
    REQUIRE((*root)->rightNode->rightNode != nullptr);
    REQUIRE((*root)->rightNode->rightNode->getData() == 20);
    REQUIRE((*root)->rightNode->rightNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->rightNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode != nullptr);
    REQUIRE((*root)->leftNode->getData() == 5);
    REQUIRE((*root)->leftNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode->rightNode == nullptr);

    myTree->add(1.5, *root);
    REQUIRE((*root)->getBalfactor() == 0);
    REQUIRE((*root)->leftNode != nullptr);
    REQUIRE((*root)->leftNode->getData() == 5);
    REQUIRE((*root)->leftNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode->getBalfactor() == -1);
    REQUIRE((*root)->leftNode->leftNode != nullptr);
    REQUIRE((*root)->leftNode->rightNode == nullptr);
    REQUIRE((*root)->leftNode->leftNode->getData() == 1.5);
    REQUIRE((*root)->leftNode->leftNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode->leftNode->getBalfactor() == 0);
    REQUIRE((*root)->leftNode->leftNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode->leftNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode != nullptr);
    REQUIRE((*root)->rightNode->getData() == 14);
    REQUIRE((*root)->rightNode->leftNode != nullptr);
    REQUIRE((*root)->rightNode->leftNode->getData() == 13);
    REQUIRE((*root)->rightNode->rightNode != nullptr);
    REQUIRE((*root)->rightNode->rightNode->getData() == 20);
    REQUIRE((*root)->rightNode->leftNode->leftNode == nullptr);
    REQUIRE((*root)->rightNode->leftNode->rightNode == nullptr);
    REQUIRE((*root)->rightNode->rightNode->leftNode == nullptr);
    REQUIRE((*root)->rightNode->rightNode->rightNode == nullptr);

    myTree->add(8, *root);
    REQUIRE((*root)->getBalfactor() == 0);
    REQUIRE((*root)->leftNode != nullptr);
    REQUIRE((*root)->leftNode->getData() == 5);
    REQUIRE((*root)->leftNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode->getBalfactor() == 0);
    REQUIRE((*root)->leftNode->rightNode != nullptr);
    REQUIRE((*root)->leftNode->leftNode != nullptr);
    REQUIRE((*root)->leftNode->rightNode->getData() == 8);
    REQUIRE((*root)->leftNode->rightNode->getBalfactor() == 0);
    REQUIRE((*root)->leftNode->rightNode->getOccurrences() == 1);
    REQUIRE((*root)->leftNode->rightNode->leftNode == nullptr);
    REQUIRE((*root)->leftNode->rightNode->rightNode == nullptr);
    
    std::vector<double> array = {10, 5, 1.5, 8, 14, 13, 20};

    REQUIRE(myTree->preOrderTraversal() == array);
    
    myTree->add(8, *root);
    REQUIRE((*root)->leftNode->rightNode->getOccurrences() == 2);
    REQUIRE(myTree->preOrderTraversal() == array);

    delete myTree;
}

TEST_CASE("Removing Nodes") {
    AVL* myTree = new AVL();
    myTree->add(10, myTree->root);
    myTree->add(5, myTree->root);
    myTree->add(1.5, myTree->root);
    myTree->add(8, myTree->root);
    myTree->add(14, myTree->root);
    myTree->add(13, myTree->root);
    myTree->add(20, myTree->root);
    std::vector<double> array = { 10, 5, 1.5, 8, 14, 13, 20 };
    REQUIRE(myTree->preOrderTraversal() == array);
    
    //Nonexistant Nodes
    myTree->remove(19);
    REQUIRE(myTree->preOrderTraversal() == array);

    //zero leafs
    myTree->remove(1.5);
    array = { 10, 5, 8, 14, 13, 20 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //2 leafs
    myTree->remove(14);
    array = { 10, 5, 8, 20, 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //1 leaf

    myTree->remove(5);
    array = { 10, 8, 20, 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->remove(20);
    array = { 10, 8, 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->remove(10);
    array = { 13, 8 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->remove(8);
    array = { 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->remove(13);
    REQUIRE(myTree->root == nullptr);

    delete myTree;
}

TEST_CASE("Finding Nodes") {
    AVL* myTree = new AVL();
    REQUIRE(myTree->find(0, myTree->root) == false);
    REQUIRE(myTree->find(1, myTree->root) == false);
    REQUIRE(myTree->find(42, myTree->root) == false);
    REQUIRE(myTree->find(-20, myTree->root) == false);
    myTree->add(64, myTree->root);
    REQUIRE(myTree->find(64, myTree->root) == true);
    REQUIRE(myTree->find(30, myTree->root) == false);
    REQUIRE(myTree->find(102, myTree->root) == false);
    myTree->add(42, myTree->root);
    myTree->add(10, myTree->root);
    myTree->add(200, myTree->root);
    REQUIRE(myTree->find(42, myTree->root) == true);
    REQUIRE(myTree->find(10, myTree->root) == true);
    REQUIRE(myTree->find(200, myTree->root) == true);
    REQUIRE(myTree->find(0, myTree->root) == false);
    REQUIRE(myTree->find(30, myTree->root) == false);
    REQUIRE(myTree->find(50, myTree->root) == false);
    REQUIRE(myTree->find(70, myTree->root) == false);
    REQUIRE(myTree->find(300, myTree->root) == false);
    delete myTree;
}

TEST_CASE("Left Rotation & Right Rotation w/ Children") {
    AVL* myTree = new AVL();
    myTree->add(130, myTree->root);
    std::vector<double> array = { 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(140, myTree->root);
    array = { 130, 140, };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(150, myTree->root);
    array = { 140, 130, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(135, myTree->root);
    array = { 140, 130, 135, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(137, myTree->root);
    array = { 140, 135, 130, 137, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //actually a right rotation, but this is a convenient place to test it.
    myTree->add(120, myTree->root);
    array = { 135, 130, 120, 140, 137, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);
}

TEST_CASE("Right Rotation & Left Rotation w/ Children") {
    AVL* myTree = new AVL();
    myTree->add(130, myTree->root);
    std::vector<double> array = { 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(120, myTree->root);
    array = { 130, 120 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(110, myTree->root);
    array = { 120, 110, 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(125, myTree->root);
    array = { 120, 110, 130, 125 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(127, myTree->root);
    array = { 120, 110, 127, 125, 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //actually left rotation (w/ children)
    myTree->add(140, myTree->root);
    array = { 127, 120, 110, 125, 130, 140 };
    REQUIRE(myTree->preOrderTraversal() == array);
    
    delete myTree;
}

TEST_CASE("Right Left Rotation") {
    AVL* myTree = new AVL();

    myTree->add(13, myTree->root);
    std::vector<double> array = { 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(27, myTree->root);
    array = { 13, 27 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(16, myTree->root);
    array = { 16, 13, 27 };
    REQUIRE(myTree->preOrderTraversal() == array);

    delete myTree;
}

TEST_CASE("Left Right Rotation") {
    AVL* myTree = new AVL();

    myTree->add(213, myTree->root);
    std::vector<double> array = { 213 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(28, myTree->root);
    array = { 213, 28 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(29, myTree->root);
    array = { 29, 28, 213 };
    REQUIRE(myTree->preOrderTraversal() == array);

    delete myTree;
}