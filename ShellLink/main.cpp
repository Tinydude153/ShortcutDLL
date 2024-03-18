#include <ShellLink/shortcut.h>

/*
int main() {

    if (CoInitializeEx(NULL, COINIT_APARTMENTTHREADED) != S_OK) {

        std::cout << "\nCoInitialize() failed.\n";
        return 1; 

    }

    HRESULT cci;
    IShellLinkW* psl;

    // Get a pointer to the IShellLink interface.
    cci = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
    if (cci == S_OK) {

        IPersistFile* ipf;

        // LPCOLESTR == const wchar_t*
        // LPCSTR == const char*
        const wchar_t* filepath = L"C:\\Users\\MinimaDudus\\Desktop\\loveme.lnk";
        LPCWSTR path = L"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";
        psl->SetPath(path);
        psl->SetDescription((LPCWSTR)L"love me...");

        // Query IShellLink for the IPersistFile interface, used for saving the shortcut in 
        // persistent storage.
        cci = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ipf);
        if (cci == S_OK) {

            WCHAR wsz[MAX_PATH];

            // Ensure string is unicode.
            //MultiByteToWideChar(CP_ACP, 0, )

            cci = ipf->Save(filepath, true);
            ipf->Release();

        }
        psl->Release();

    }

    return cci;
}
*/

/*
int main() {

    try {

        Shortcut shortcut;
        if (!shortcut.CreateShortcut(
            L"C:\\Users\\MinimaDudus\\Desktop\\test.lnk",
            L"C:\\Program Files\\BraveSoftware\\Brave-Browser\\Application\\brave.exe",
            L"Please don't hate me...",
            NULL,
            L"C:\\Program Files\\BraveSoftware\\Brave-Browser\\Application",
            L"C:\\Program Files\\BraveSoftware\\Brave-Browser\\Application"
        )) {

            std::cout << "\nCreateShortcut() failed.";
            return 0;

        }

        if (!shortcut.ResolveShortcut(L"C:\\Users\\MinimaDudus\\Desktop\\test.lnk")) {

            std::cout << "\nResolveShortcut() failed.";
            return 0;

        }
        std::wcout << L'\n' << shortcut.Properties->TargetPath;

    } catch (std::exception& e) {
        std::cout << "\nException thrown: " << e.what();
        return 0;
    }

    return 0;
}
*/

int main() {

    try {

        WindowsShortcut::Shortcut shortcut;
        if (!shortcut.CreateShortcut(
            L"C:\\Intel\\test.lnk",
            NULL,
            L"Please don't hate me...",
            NULL,
            NULL,
            NULL
        )) {

            std::cout << "\nCreateShortcut() failed.";
            return 0;

        }

        /*
        if (!shortcut.ResolveShortcut(L"C:\\Users\\MinimaDudus\\Desktop\\test.lnk")) {

            std::cout << "\nResolveShortcut() failed.";
            return 0;

        }
        std::wcout << L'\n' << shortcut.Properties->TargetPath;
        */

    } catch (std::exception& e) {
        std::cout << "\nException thrown: " << e.what();
        return 0;
    }

    return 0;
}


