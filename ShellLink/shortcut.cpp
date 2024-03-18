#include <ShellLink/shortcut.h>

namespace WindowsShortcut {

ShortcutProperties::~ShortcutProperties() {

    if (this->TargetPath) delete[] this->TargetPath;
    if (this->Description) delete[] this->Description;
    if (this->Arguments) delete[] this->Arguments;
    if (this->WorkingDirectory) delete[] this->WorkingDirectory;
    if (this->RelativePath) delete[] this->RelativePath;
    if (this->IconLocation) delete[] this->IconLocation;
    if (this->IconIndex) delete this->IconIndex;

}

void ShortcutProperties::SetTargetPath(wchar_t* target_path) {

    this->TargetPath = target_path;

}

void ShortcutProperties::SetDescription(wchar_t* description) {

    this->Description = description;

}

void ShortcutProperties::SetArguments(wchar_t* arguments) {

    this->Arguments = arguments;

}

void ShortcutProperties::SetWorkingDirectory(wchar_t* working_directory) {

    this->WorkingDirectory = working_directory;

}

void ShortcutProperties::SetRelativePath(wchar_t* relative_path) {

    this->RelativePath = relative_path;

}

void ShortcutProperties::SetIconLocation(wchar_t* location, int* index) {

    this->IconLocation = location;
    this->IconIndex = index;

}

Shortcut::Shortcut() {

    // Initialize the COM library for use.
    if (CoInitializeEx(NULL, COINIT_APARTMENTTHREADED) != S_OK) {

        std::cout << "\nCoInitialize() failed.\n";
        throw std::runtime_error("CoInitialize() failed.");

    }

    // Initialize IShellLinkW pointer to null.
    Shortcut::ISL = NULL;

    // Get a pointer to the IShellLink interface.
    this->CCI = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&this->ISL);

}

Shortcut::~Shortcut() {

    // Uninitialize the COM library.
    CoUninitialize();

    // Delete Shortcut->ShortcutProperties struct.
    delete this->Properties;

}

void Shortcut::SetArguments(const wchar_t* arguments) {
    if (arguments) this->Properties->SetArguments(arguments);
}

void Shortcut::SetDescription(const wchar_t* description) {
    if (description) this->Properties->SetDescription(description);
}

void Shortcut::SetIconLocation(const wchar_t* location, int index) {}

void Shortcut::SetPath(const wchar_t* path) {
    if (path) this->Properties->SetPath(path);
}

bool Shortcut::ValidPath(const wchar_t* path) {

    std::ifstream file(path);
    if (file.good()) {
        return 1;
    } else { return 0; }

}

wchar_t* Shortcut::GetArguments() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t* szBuf = new wchar_t[MAX_PATH];
    HRESULT hres;

    hres = this->ISL->GetArguments(szBuf, MAX_PATH);
    if (hres != S_OK) {
        std::cout << "\nGetArguments() failed: " << hres;
        delete[] szBuf;
        return NULL;
    }

    if (szBuf) {
        return szBuf;
    } else { 
        delete[] szBuf;
        return NULL; 
    }

    delete[] szBuf;
    return NULL;
}

wchar_t* Shortcut::GetDescription() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t* szBuf = new wchar_t[MAX_PATH];
    HRESULT hres;

    hres = this->ISL->GetDescription(szBuf, MAX_PATH);
    if (hres != S_OK) {
        std::cout << "\nGetDescription() failed: " << hres;
        delete[] szBuf;
        return NULL;
    }

    if (szBuf) {
        return szBuf;
    } else { 
        delete[] szBuf;
        return NULL; 
    }

    delete[] szBuf;
    return NULL;
}

wchar_t* Shortcut::GetIconLocation() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t* szBuf = new wchar_t[MAX_PATH];
    int iIndex = 0;
    HRESULT hres;

    hres = this->ISL->GetIconLocation(szBuf, MAX_PATH, &iIndex);
    if (hres != S_OK) {
        std::cout << "\nGetIconLocation() failed: " << hres;
        delete[] szBuf;
        return NULL;
    }

    if (szBuf) {
        return szBuf;
    } else { 
        delete[] szBuf;
        return NULL; 
    }

    delete[] szBuf;
    return NULL;
}

int* Shortcut::GetIconIndex() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t szBuf[MAX_PATH] = {0}; // won't be used, so it doesn't need heap-allocated.
    int* iIndex = new int(0);
    HRESULT hres;

    hres = this->ISL->GetIconLocation(szBuf, MAX_PATH, iIndex);
    if (hres != S_OK) {
        std::cout << "\nShortcut::GetIconIndex() : GetIconLocation() failed: " << hres;
        delete iIndex;
        return NULL;
    }

    if (iIndex) {
        return iIndex;
    } else { 
        delete iIndex;
        return NULL; 
    }

    delete iIndex;
    return NULL;

}

wchar_t* Shortcut::GetPath() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t* szBuf = new wchar_t[MAX_PATH];
    HRESULT hres;

    hres = this->ISL->GetPath(szBuf, MAX_PATH, NULL, SLGP_RAWPATH);
    if (hres != S_OK) {
        std::cout << "\nGetPath() failed: " << hres;
        delete[] szBuf;
        return NULL;
    }

    if (szBuf) {
        return szBuf;
    } else { 
        delete[] szBuf;
        return NULL; 
    }

    delete[] szBuf;
    return NULL;
}

wchar_t* Shortcut::GetWorkingDirectory() {

    // MAX_PATH is a macro for the Windows' path size limit, 260.
    wchar_t* szBuf = new wchar_t[MAX_PATH];
    HRESULT hres;

    hres = this->ISL->GetWorkingDirectory(szBuf, MAX_PATH);
    if (hres != S_OK) {
        std::cout << "\nGetWorkingDirectory() failed: " << hres;
        delete[] szBuf;
        return NULL;
    }

    if (szBuf) {
        return szBuf;
    } else { 
        return NULL; 
        delete[] szBuf;
    }

    delete[] szBuf;
    return NULL;
}

bool Shortcut::CreateShortcut(
        const wchar_t* LnkPath, 
        const wchar_t* TargetPath, 
        const wchar_t* Desc, 
        const wchar_t* Arguments,
        const wchar_t* WorkingDir,
        const wchar_t* RelativePath
    ) {

    if (this->CCI == S_OK) {

        IPersistFile* IPF;

        if (TargetPath) {
            if (this->ISL->SetPath(TargetPath) != S_OK) {
                std::cout << "\nSetPath(\"" << TargetPath << "\")" << " failed\n";
                return 0;
            } 
        }
        if (Desc) {
            if (this->ISL->SetDescription(Desc) != S_OK) {
                std::cout << "\nSetDescription(\"" << Desc << "\")" << " failed\n";
                return 0;
            }
        }
        if (Arguments) {
            if (this->ISL->SetArguments(Arguments) == S_OK) {
                std::cout << "\nSetArguments(\"" << Arguments << "\")" << " failed\n";
                return 0;
            }
        }
        if (WorkingDir) {
            if (this->ISL->SetWorkingDirectory(WorkingDir) != S_OK) {
                std::cout << "\nSetWorkingDirectory(\"" << WorkingDir << "\")" << " failed\n";
                return 0;
            }
        }
        if (RelativePath) {
            if (this->ISL->SetRelativePath(RelativePath, 0) != S_OK) {
                std::cout << "\nSetRelativePath(\"" << RelativePath << "\")" << " failed\n";
                return 0;
            }
        }

        // Query IShellLink for the IPersistFile interface, used for saving the shortcut in 
        // persistent storage. 
        this->CCI = this->ISL->QueryInterface(IID_IPersistFile, (LPVOID*)&IPF);
        if (this->CCI == S_OK) {

            this->CCI = IPF->Save(LnkPath, true);
            IPF->Release();
            return 1;

        } else {

            std::cout << "\nQueryInterface() failed: " << CCI;
            return 0;

        }

    } else {

        std::cout << "\nIShellLink class initialization failed: " << CCI;
        return 0;

    }

    return 0;

}

bool Shortcut::ResolveShortcut(const wchar_t* LnkPath) {

    if (LnkPath == NULL) return 0;
    if (!Shortcut::ValidPath(LnkPath)) {

        std::cout << "\nInvalid file path.";
        return 0;

    }

    if (this->CCI == S_OK) {

        IPersistFile* IPF;

        this->CCI = this->ISL->QueryInterface(IID_IPersistFile, (void**)&IPF);
        if (this->CCI == S_OK) {

            this->CCI = IPF->Load(LnkPath, STGM_READWRITE);
            if (this->CCI == S_OK) {

                this->CCI = this->ISL->Resolve(GetDesktopWindow(), SLR_NO_UI);
                if (this->CCI == S_OK) {

                    this->resolved = true;
                    this->Properties->SetTargetPath(this->GetPath());
                    this->Properties->SetDescription(this->GetDescription());
                    this->Properties->SetArguments(this->GetArguments());
                    this->Properties->SetWorkingDirectory(this->GetWorkingDirectory());
                    this->Properties->SetIconLocation(this->GetIconLocation());
                    this->Properties->IconIndex = this->GetIconIndex();
                    return 1;

                } else {

                    std::cout << "\nIShellLink->Resolve() failed: " << CCI;
                    return 0;

                }

            } else {

                std::cout << "\nIPersistFile->Load() failed: " << CCI;
                return 0;

            }

        } else {

            std::cout << "\nQueryInterface() failed: " << CCI;
            return 0;

        }

    } else {

        std::cout << "\nIShellLink class initialization failed: " << CCI;
        return 0;

    }

    return 0;

}

} // Namespace WindowsShortcut