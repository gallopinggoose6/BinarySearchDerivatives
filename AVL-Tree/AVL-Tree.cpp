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

void traverse(Node* current) {
	std::cout << "Data: " << current->getData() << ",\tBallance Factor: " << static_cast<AVLNode*>(current)->getBalfactor() << ",\tOccurrences: " << current->getOccurrences() << "\n";
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

TEST_CASE("Tree Tree Creation and Deletion") {
    Tree* myTree = new Tree();
    REQUIRE(myTree->root == nullptr);
    delete myTree;
}

TEST_CASE("Tree Node Addition") {
    Tree* myTree = new Tree();

    myTree->add(10);
    REQUIRE(myTree->root != nullptr);
    REQUIRE(myTree->root->getData() == 10);
    REQUIRE(myTree->root->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode == nullptr);

    myTree->add(14);
    REQUIRE(myTree->root->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->getData() == 14);
    REQUIRE(myTree->root->rightNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode == nullptr);

    myTree->add(14);
    REQUIRE(myTree->root->rightNode->getOccurrences() == 2);
    REQUIRE(myTree->root->rightNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode == nullptr);

    myTree->add(5);
    REQUIRE(myTree->root->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->getData() == 5);
    REQUIRE(myTree->root->leftNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->leftNode == nullptr);

    myTree->add(20);
    REQUIRE(myTree->root->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->getOccurrences() == 1);
    REQUIRE(myTree->root->rightNode->rightNode->getData() == 20);
    REQUIRE(myTree->root->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->leftNode->leftNode == nullptr);

    myTree->add(13);
    REQUIRE(myTree->root->rightNode->leftNode != nullptr);
    REQUIRE(myTree->root->rightNode->leftNode->getOccurrences() == 1);
    REQUIRE(myTree->root->rightNode->leftNode->getData() == 13);
    REQUIRE(myTree->root->rightNode->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->leftNode->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->getData() == 20);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->getData() == 5);
    REQUIRE(myTree->root->leftNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode->rightNode == nullptr);

    myTree->add(1.5);
    REQUIRE(myTree->root->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->getData() == 5);
    REQUIRE(myTree->root->leftNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->leftNode->leftNode->getData() == 1.5);
    REQUIRE(myTree->root->leftNode->leftNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode->leftNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->getData() == 14);
    REQUIRE(myTree->root->rightNode->leftNode != nullptr);
    REQUIRE(myTree->root->rightNode->leftNode->getData() == 13);
    REQUIRE(myTree->root->rightNode->rightNode != nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->getData() == 20);
    REQUIRE(myTree->root->rightNode->leftNode->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode->leftNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode == nullptr);

    myTree->add(8);
    REQUIRE(myTree->root->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->getData() == 5);
    REQUIRE(myTree->root->leftNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode->rightNode != nullptr);
    REQUIRE(myTree->root->leftNode->leftNode != nullptr);
    REQUIRE(myTree->root->leftNode->rightNode->getData() == 8);
    REQUIRE(myTree->root->leftNode->rightNode->getOccurrences() == 1);
    REQUIRE(myTree->root->leftNode->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->leftNode->rightNode->rightNode == nullptr);

    std::vector<double> array = { 10, 5, 1.5, 8, 14, 13, 20 };

    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(8);
    REQUIRE(myTree->root->leftNode->rightNode->getOccurrences() == 2);
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(21);
    myTree->add(22);

    REQUIRE(myTree->root->rightNode->rightNode->rightNode->getData() == 21);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode->rightNode->getData() == 22);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode->rightNode->rightNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(myTree->root->rightNode->rightNode->getOccurrences() == 1);
    REQUIRE(myTree->root->rightNode->rightNode->rightNode->getOccurrences() == 1);

    delete myTree;
}

TEST_CASE("Tree Removing Nodes") {
    Tree* myTree = new Tree();
    myTree->add(10);
    myTree->add(5);
    myTree->add(1.5);
    myTree->add(8);
    myTree->add(14);
    myTree->add(13);
    myTree->add(20);
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

TEST_CASE("Tree Finding Nodes") {
    Tree* myTree = new Tree();
    REQUIRE(myTree->find(0) == nullptr);
    REQUIRE(myTree->find(1) == nullptr);
    REQUIRE(myTree->find(42) == nullptr);
    REQUIRE(myTree->find(-20) == nullptr);
    myTree->add(64);
    REQUIRE(myTree->find(64) != nullptr);
    REQUIRE(myTree->find(30) == nullptr);
    REQUIRE(myTree->find(102) == nullptr);
    myTree->add(42);
    myTree->add(10);
    myTree->add(200);
    REQUIRE(myTree->find(42) != nullptr);
    REQUIRE(myTree->find(10) != nullptr);
    REQUIRE(myTree->find(200) != nullptr);
    REQUIRE(myTree->find(0) == nullptr);
    REQUIRE(myTree->find(30) == nullptr);
    REQUIRE(myTree->find(50) == nullptr);
    REQUIRE(myTree->find(70) == nullptr);
    REQUIRE(myTree->find(300) == nullptr);
    delete myTree;
}

////////////////////////////// AVL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

TEST_CASE("AVL Tree Creation and Deletion") {
    AVL* myTree = new AVL();
    REQUIRE(myTree->root == nullptr);
    delete myTree;
}

TEST_CASE("AVL Node Addition") {
    AVL* myTree = new AVL();

    myTree->add(10);
    REQUIRE(static_cast<AVLNode*>(myTree->root) != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getData() == 10);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode == nullptr);

    myTree->add(14);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root->rightNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->getData() == 14);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode == nullptr);

    myTree->add(14);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->getOccurrences() == 2);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode == nullptr);
    
    myTree->add(5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root->leftNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getData() == 5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode == nullptr);
    
    myTree->add(20);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root->rightNode)->getBalfactor() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->getData() == 20);
    REQUIRE(static_cast<AVLNode*>(myTree->root->rightNode->rightNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode == nullptr);
    
    myTree->add(13);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root->rightNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->getData() == 13);
    REQUIRE(static_cast<AVLNode*>(myTree->root->rightNode->leftNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->getData() == 20);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getData() == 5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode == nullptr);

    myTree->add(1.5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getData() == 5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root->leftNode)->getBalfactor() == -1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode->getData() == 1.5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root->leftNode->leftNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->getData() == 14);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->getData() == 13);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->getData() == 20);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->leftNode->rightNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->rightNode->rightNode->rightNode == nullptr);

    myTree->add(8);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getData() == 5);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root->leftNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->leftNode != nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode->getData() == 8);
    REQUIRE(static_cast<AVLNode*>(myTree->root->leftNode->rightNode)->getBalfactor() == 0);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode->getOccurrences() == 1);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode->leftNode == nullptr);
    REQUIRE(static_cast<AVLNode*>(myTree->root)->leftNode->rightNode->rightNode == nullptr);
    
    std::vector<double> array = {10, 5, 1.5, 8, 14, 13, 20};

    REQUIRE(myTree->preOrderTraversal() == array);
    
    myTree->add(8);
    REQUIRE((static_cast<AVLNode*>(myTree->root))->leftNode->rightNode->getOccurrences() == 2);
    REQUIRE(myTree->preOrderTraversal() == array);
    delete myTree;
}

TEST_CASE("AVL Removing Nodes") {
    AVL* myTree = new AVL();
    myTree->add(10);
    myTree->add(5);
    myTree->add(1.5);
    myTree->add(8);
    myTree->add(14);
    myTree->add(13);
    myTree->add(20);
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

TEST_CASE("AVL Finding Nodes") {
    AVL* myTree = new AVL();
    REQUIRE(myTree->find(0) == nullptr);
    REQUIRE(myTree->find(1) == nullptr);
    REQUIRE(myTree->find(42) == nullptr);
    REQUIRE(myTree->find(-20) == nullptr);
    myTree->add(64);
    REQUIRE(myTree->find(64) != nullptr);
    REQUIRE(myTree->find(30) == nullptr);
    REQUIRE(myTree->find(102) == nullptr);
    myTree->add(42);
    myTree->add(10);
    myTree->add(200);
    REQUIRE(myTree->find(42) != nullptr);
    REQUIRE(myTree->find(10) != nullptr);
    REQUIRE(myTree->find(200) != nullptr);
    REQUIRE(myTree->find(0) == nullptr);
    REQUIRE(myTree->find(30) == nullptr);
    REQUIRE(myTree->find(50) == nullptr);
    REQUIRE(myTree->find(70) == nullptr);
    REQUIRE(myTree->find(300) == nullptr);
    delete myTree;
}

TEST_CASE("Left Rotation & Right Rotation w/ Children") {
    AVL* myTree = new AVL();
    myTree->add(130);
    std::vector<double> array = { 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(140);
    array = { 130, 140, };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(150);
    array = { 140, 130, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(135);
    array = { 140, 130, 135, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(137);
    array = { 140, 135, 130, 137, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //actually a right rotation, but this is a convenient place to test it.
    myTree->add(120);
    array = { 135, 130, 120, 140, 137, 150 };
    REQUIRE(myTree->preOrderTraversal() == array);
}

TEST_CASE("Right Rotation & Left Rotation w/ Children") {
    AVL* myTree = new AVL();
    myTree->add(130);
    std::vector<double> array = { 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(120);
    array = { 130, 120 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(110);
    array = { 120, 110, 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(125);
    array = { 120, 110, 130, 125 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(127);
    array = { 120, 110, 127, 125, 130 };
    REQUIRE(myTree->preOrderTraversal() == array);

    //actually left rotation (w/ children)
    myTree->add(140);
    array = { 127, 120, 110, 125, 130, 140 };
    REQUIRE(myTree->preOrderTraversal() == array);
    
    delete myTree;
}

TEST_CASE("Right Left Rotation") {
    AVL* myTree = new AVL();

    myTree->add(13);
    std::vector<double> array = { 13 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(27);
    array = { 13, 27 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(16);
    array = { 16, 13, 27 };
    REQUIRE(myTree->preOrderTraversal() == array);

    delete myTree;
}

TEST_CASE("Left Right Rotation") {
    AVL* myTree = new AVL();

    myTree->add(213);
    std::vector<double> array = { 213 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(28);
    array = { 213, 28 };
    REQUIRE(myTree->preOrderTraversal() == array);

    myTree->add(29);
    array = { 29, 28, 213 };
    REQUIRE(myTree->preOrderTraversal() == array);

    delete myTree;
}