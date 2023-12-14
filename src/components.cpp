#include "components.h"
/*
void Game::SetCfgPath()
{
	// Open native file dialog
	OPENFILENAME ofn;
	char szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrInitialDir = defaultPath;
	ofn.lpstrFilter = "All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {

		strcpy_s(cfgPath, sizeof(cfgPath), szFile);
	}
}*/

void Game::SetCfgPath() {
    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        std::cerr << "Error initializing COM: " << std::hex << hr << std::endl;
        return;
    }

    // Create the File Open dialog COM object
    IFileDialog* pFileDialog;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
    if (FAILED(hr)) {
        std::cerr << "Error creating File Open dialog: " << std::hex << hr << std::endl;
        CoUninitialize();
        return;
    }

    // Set options for the dialog
    DWORD dwOptions;
    hr = pFileDialog->GetOptions(&dwOptions);
    if (SUCCEEDED(hr)) {
        pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS);
    }

    // Show the dialog
    hr = pFileDialog->Show(NULL);
    if (SUCCEEDED(hr)) {
        // Get the selected folder
        IShellItem* pItem;
        hr = pFileDialog->GetResult(&pItem);
        if (SUCCEEDED(hr)) {
            PWSTR pszPath;
            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
            if (SUCCEEDED(hr)) {
                std::wstring selectedFolder(pszPath);
                CoTaskMemFree(pszPath);
                pItem->Release();
                pFileDialog->Release();
                CoUninitialize();
                cfgPath = selectedFolder;
            }
            pItem->Release();
        }
    }

    // Release the dialog COM object
    //pFileDialog->Release();

    // Uninitialize COM
    CoUninitialize();

    return;
}