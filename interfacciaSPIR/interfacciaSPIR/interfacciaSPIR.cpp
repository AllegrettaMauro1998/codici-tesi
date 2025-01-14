// interfacciaSPIR.cpp : Definisce il punto di ingresso dell'applicazione.
#include <windows.h> 
#include "framework.h"
#include "interfacciaSPIR.h"
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>
#include <fstream> 
#include <shlobj.h>
#include <shellapi.h> 
#include <commdlg.h>
#include <set>

INT_PTR CALLBACK InputDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void ProcessDirectory(const wchar_t* directoryPath);
void ProcessFile(const wchar_t* filePath);
void ProcessSingleFile(const wchar_t* filePath);

#define MAX_LOADSTRING 100

//dichiarazione pulsanti
#define IDC_CONFERM_BUTTON 102
#define IDC_CATALOGO_BUTTON 103
#define IDC_ESTRAZIONE_BUTTON 104
#define IDC_MATCH_BUTTON 105

// Dichiarazione delle variabili globali
int i = 0;
HINSTANCE hInst;
HWND hcatalogo;
HWND hestrazione;
HWND hmatch;
HWND hConferma;
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Funzione per ottenere il percorso del Desktop
bool GetDesktopPath(wchar_t* desktopPath, size_t maxLen) {
    return SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath));
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_INTERFACCIASPIR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INTERFACCIASPIR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_INTERFACCIASPIR);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    switch (message) {
    case WM_CREATE:

        DragAcceptFiles(hWnd, TRUE);

        hcatalogo = CreateWindow(L"BUTTON", L"Creazione catalogo", WS_CHILD | WS_VISIBLE, 50, 50, 200, 30, hWnd, (HMENU)IDC_CATALOGO_BUTTON, hInst, nullptr);

        // Creazione del pulsante per la prossima immagine
        hestrazione = CreateWindow(L"BUTTON", L"estrazioni dati pinna", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 100, 150, 30, hWnd, (HMENU)IDC_ESTRAZIONE_BUTTON, hInst, nullptr);

        // Creazione del pulsante per cancellare l'immagine
        hmatch = CreateWindow(L"BUTTON", L"Matching", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 150, 150, 30, hWnd, (HMENU)IDC_MATCH_BUTTON, hInst, nullptr);

        hConferma = CreateWindow(L"BUTTON", L"conferma", WS_TABSTOP | SW_HIDE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 200, 150, 30, hWnd, (HMENU)IDC_CONFERM_BUTTON, hInst, nullptr);

        break;

    case WM_DROPFILES: {
        HDROP hDrop = (HDROP)wParam;
        wchar_t filePath[MAX_PATH];

        UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

        // Ottieni il percorso del primo file trascinato
        for (UINT i = 0; i < fileCount; ++i) {
            // Ottieni il percorso completo del file
            DragQueryFile(hDrop, i, filePath, MAX_PATH);

            // Elaborazione del file
            ProcessFile(filePath);
        }
        // Rilascia la memoria
        DragFinish(hDrop);
        break;
    }

    case WM_COMMAND: {
        wmId = LOWORD(wParam);  // Dichiarazione di wmId
        switch (wmId) {
        case IDC_CATALOGO_BUTTON: {
            // Codice per IDC_CATALOGO_BUTTON
            wchar_t catalogName[256];
            int result = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG_INPUT), hWnd, InputDialogProc, (LPARAM)catalogName);

            if (result == IDCANCEL || wcslen(catalogName) == 0) {
                MessageBox(hWnd, L"Operazione annullata o nome non inserito.", L"Errore", MB_OK | MB_ICONERROR);
                break;
            }

            wchar_t desktopPath[MAX_PATH];
            if (!GetDesktopPath(desktopPath, MAX_PATH)) {
                MessageBox(hWnd, L"Impossibile trovare il percorso del Desktop.", L"Errore", MB_OK | MB_ICONERROR);
                break;
            }

            wchar_t spirPath[MAX_PATH];
            wchar_t cataloguePath[MAX_PATH];
            wchar_t outputPath[MAX_PATH];
            wchar_t debugPath[MAX_PATH];

            swprintf_s(spirPath, L"%s\\SPIR.exe", desktopPath);
            swprintf_s(cataloguePath, L"%s\\%s", desktopPath, catalogName);
            swprintf_s(outputPath, L"%s\\fin-catalogue.cbor", desktopPath);
            swprintf_s(debugPath, L"%s\\%s_Debug", desktopPath, catalogName);

            int debugEnabled = MessageBox(hWnd, L"Vuoi abilitare il debug per il catalogo?", L"Debug", MB_YESNO | MB_ICONQUESTION);

            wchar_t command[1024];
            swprintf_s(command, L"\"%s\" build-fin-catalogue \"%s\" \"%s\"", spirPath, cataloguePath, outputPath);

            if (debugEnabled == IDYES) {
                wcscat_s(command, L" --debug ");
                wcscat_s(command, debugPath);
            }

            STARTUPINFO si = { sizeof(STARTUPINFO) };
            PROCESS_INFORMATION pi;
            ZeroMemory(&pi, sizeof(pi));

            if (CreateProcess(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                MessageBox(hWnd, L"Creazione catalogo avviata con successo.", L"Successo", MB_OK | MB_ICONINFORMATION);
            }
            else {
                MessageBox(hWnd, L"Errore nell'avvio del processo SPIR.exe. Verifica i percorsi e riprova.", L"Errore", MB_OK | MB_ICONERROR);
            }
            break;
        }
        case IDC_MATCH_BUTTON: {
            // Preparazione dei percorsi relativi
            wchar_t spirPath[MAX_PATH];
            wchar_t propertiesPath[MAX_PATH];
            wchar_t cataloguePath[MAX_PATH];

            // Ottieni il percorso del Desktop
            wchar_t desktopPath[MAX_PATH];
            if (!GetDesktopPath(desktopPath, MAX_PATH)) {
                MessageBox(hWnd, L"Impossibile trovare il percorso del Desktop.", L"Errore", MB_OK | MB_ICONERROR);
                break;
            }

            // Costruzione del percorso di ricerca per i file del Desktop
            std::wstring searchPath = desktopPath;
            searchPath.append(L"\\*"); // Cerca tutti i file nella directory

            // Variabili per la ricerca dei file
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);
            if (hFind == INVALID_HANDLE_VALUE) {
                MessageBox(hWnd, L"Impossibile accedere al Desktop.", L"Errore", MB_OK | MB_ICONERROR);
                break;
            }

            std::set<std::wstring> processedFiles;

            int counter = 0;
            do {
                
                if (counter >1 && counter > 1000) {
                    MessageBox(hWnd, L"Loop infinito rilevato durante la scansione.", L"Errore", MB_OK | MB_ICONERROR);
                    break;
                }

                // Ignora le directory speciali "." e ".."
                if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
                    // Costruzione del percorso assoluto del file corrente
                    std::wstring fileName = findFileData.cFileName;

                    // Controlla se il file è già stato elaborato
                    if (processedFiles.find(fileName) == processedFiles.end() && counter >1) {
                        // Debug: Salta il file già processato
                        wprintf(L"File già processato: %s\n", fileName.c_str());
                        continue;
                    }

                    // Aggiunge il file al set di file processati
                    processedFiles.insert(fileName);

                    std::wstring filePath = desktopPath;
                    filePath.append(L"\\").append(fileName);

                    // Verifica se è un file
                    if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                        // Debug: stampa il nome del file
                        wprintf(L"Processando file: %s\n", filePath.c_str());

                        // Costruzione dei percorsi assoluti per il matching
                        swprintf_s(spirPath, L"%s\\SPIR.exe", desktopPath);
                        swprintf_s(propertiesPath, L"%s\\fin-properties.cbor", desktopPath);
                        swprintf_s(cataloguePath, L"%s\\fin-catalogue.cbor", desktopPath);

                        // Costruzione del comando
                        wchar_t command[1024];
                        swprintf_s(command, L"cmd.exe /c \"%s match-fin %s %s & pause\"",
                            spirPath, propertiesPath, cataloguePath);

                        // Esecuzione del comando
                        STARTUPINFO si = { sizeof(STARTUPINFO) };
                        PROCESS_INFORMATION pi;
                        ZeroMemory(&pi, sizeof(pi));

                        if (CreateProcess(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
                            // Comando avviato con successo
                            CloseHandle(pi.hProcess);
                            CloseHandle(pi.hThread);
                        }
                        else {
                            // Errore nell'avvio del comando
                            MessageBox(hWnd, L"Errore nell'avvio del processo SPIR.exe. Verifica i percorsi e riprova.",
                                L"Errore", MB_OK | MB_ICONERROR);
                            break;
                        }
                    }
                    counter++;
                }
            } while (FindNextFile(hFind, &findFileData) != 0);

            // Gestione di errori in FindNextFile
            if (GetLastError() != ERROR_NO_MORE_FILES) {
                MessageBox(hWnd, L"Errore durante la scansione dei file nel Desktop.", L"Errore", MB_OK | MB_ICONERROR);
            }

            // Chiude il handle
            FindClose(hFind);

            // Messaggio finale
            MessageBox(hWnd, L"Matching completato per tutti i file.", L"Successo", MB_OK | MB_ICONINFORMATION);

            break;
        }

        case IDC_CONFERM_BUTTON: {
            break;
        }
        case IDC_ESTRAZIONE_BUTTON: {
            MessageBox(hWnd, L"Trascina i file o le cartelle per avviare l'estrazione.", L"Istruzioni", MB_OK | MB_ICONINFORMATION);
            break;
        }
        }
        break;

    case WM_DESTROY:
        DragAcceptFiles(hWnd, FALSE); // Disabilita il drag-and-drop
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
                   return 0;
    }
}

INT_PTR CALLBACK InputDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static wchar_t* inputName;

    switch (message) {
    case WM_INITDIALOG:
        // Salva il puntatore al nome in inputName
        inputName = (wchar_t*)lParam;
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            // Ottieni il testo dal campo di input
            GetDlgItemText(hDlg, IDC_INPUT_NAME, inputName, 256);
            EndDialog(hDlg, IDOK); // Chiudi la finestra di dialogo
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL); // Chiudi la finestra di dialogo senza salvare
            return TRUE;
        }
        break;
    }

    return FALSE;
}

void ProcessFile(const wchar_t* filePath)
{
    // Controlla se è una directory o un file
    DWORD attributes = GetFileAttributes(filePath);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        MessageBox(NULL, L"Errore nel leggere il file o la cartella.", L"Errore", MB_OK | MB_ICONERROR);
        return;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY) {
        // È una directory, estrai i file contenuti
        ProcessDirectory(filePath);
    }
    else {
        // È un file singolo
        ProcessSingleFile(filePath);
    }
}

// Funzione per elaborare un singolo file
void ProcessSingleFile(const wchar_t* filePath)
{
    // Mostra un messaggio con il nome del file che stai elaborando
    wchar_t message[1024];
    swprintf_s(message, L"Elaborazione del file:\n%s", filePath);
    MessageBox(NULL, message, L"File Elaborato", MB_OK | MB_ICONINFORMATION);

    // Nome del file senza estensione
    wchar_t fileName[256];
    wcsncpy_s(fileName, filePath, _TRUNCATE);
    wchar_t* dotPos = wcsrchr(fileName, L'.');
    if (dotPos) {
        *dotPos = L'\0';  // Rimuovi l'estensione per ottenere il nome base
    }

    // Costruzione dei percorsi relativi per l'estrazione
    wchar_t spirPath[MAX_PATH];
    wchar_t photoPath[MAX_PATH];
    wchar_t outputPath[MAX_PATH];
    wchar_t debugPath[MAX_PATH];

    // Ottieni il percorso del Desktop
    wchar_t desktopPath[MAX_PATH];
    if (!GetDesktopPath(desktopPath, MAX_PATH)) {
        MessageBox(NULL, L"Impossibile trovare il percorso del Desktop.", L"Errore", MB_OK | MB_ICONERROR);
        return; // Termina l'elaborazione
    }


   
    // Costruzione dei percorsi assoluti per SPIR.exe e i file associati
    swprintf_s(spirPath, L"%s\\SPIR.exe", desktopPath);
    swprintf_s(photoPath, L"%s.png", fileName);
    swprintf_s(outputPath, L"%s\\fin-properties.cbor", desktopPath);
    swprintf_s(debugPath, L"%s-debug.png", fileName);

    // Chiedo all'utente se vuole abilitare il debug
    int debugEnabled = MessageBox(NULL, L"Vuoi abilitare il debug per l'estrazione delle proprietà?", L"Debug", MB_YESNO | MB_ICONQUESTION);

    // Costruzione del comando per eseguire SPIR.exe
    wchar_t command[1024];
    if (debugEnabled == IDYES) {
        if (i == 0)
        {
            swprintf_s(command, 1024, L"\"%s\" extract-fin-properties \"%s\" \"%s\" --debug \"%s\"",
                spirPath, photoPath, outputPath, debugPath);
            i++;
        }else
        {
        // Caso in cui i != 0
        swprintf_s(command, 1024, L"\"%s\" extract-fin-properties \"%s\" \"%s%d\" --debug \"%s\"",
            spirPath, photoPath, outputPath, i, debugPath);
        i++;
        }
    }
    else {
        if (i == 0) {
            swprintf_s(command, 1024, L"\"%s\" extract-fin-properties \"%s\" \"%s\"",
                spirPath, photoPath, outputPath);
            i++;
        }
        else {
            // Caso in cui i != 0
            swprintf_s(command, 1024, L"\"%s\" extract-fin-properties \"%s\" \"%s%d\"",
                spirPath, photoPath, outputPath, i);
            i++;
        }
    }

    // Esegui il comando
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Comando avviato con successo
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        MessageBox(NULL, L"Estratto proprietà del file con successo.", L"Successo", MB_OK | MB_ICONINFORMATION);
    }
    else {
        // Errore nell'avvio del processo
        MessageBox(NULL, L"Errore nell'avvio del processo SPIR.exe. Verifica i percorsi e riprova.", L"Errore", MB_OK | MB_ICONERROR);
    }
}

// Funzione per elaborare una directory
void ProcessDirectory(const wchar_t* directoryPath)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Costruisci il percorso per cercare tutti i file nella directory
    std::wstring searchPath = directoryPath;
    searchPath.append(L"\\*"); // Aggiunge \* per cercare tutto nella directory

    hFind = FindFirstFile(searchPath.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, L"Errore durante l'accesso alla cartella.", L"Errore", MB_OK | MB_ICONERROR);
        return;
    }

    do {
        // Escludo le directory "." e ".."
        if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
            std::wstring fullPath = directoryPath;
            fullPath.append(L"\\").append(findFileData.cFileName);

            // Verifico se è un file o una directory
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Ricorsione: processa le sottodirectory
                ProcessDirectory(fullPath.c_str());
            }
            else {
                // Processa il file
                if (wcsstr(findFileData.cFileName, L"debug") == nullptr) {
                    // Processa il file se non contiene "debug"
                    ProcessSingleFile(fullPath.c_str());
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}