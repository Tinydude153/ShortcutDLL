#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <Windows.h>
#include <objidl.h>
#include <objbase.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <strsafe.h>
#include <iostream>
#include <fstream>
#include <exception>

namespace WindowsShortcut {

struct ShortcutProperties {

    ~ShortcutProperties();
    wchar_t* TargetPath = 0;
    wchar_t* Description = 0;
    wchar_t* Arguments = 0;
    wchar_t* WorkingDirectory = 0;
    wchar_t* RelativePath = 0;
    wchar_t* IconLocation = 0;
    int* IconIndex = 0;
    void SetTargetPath(wchar_t* target_path);
    void SetDescription(wchar_t* description);
    void SetArguments(wchar_t* arguments);
    void SetWorkingDirectory(wchar_t* working_directory);
    void SetRelativePath(wchar_t* relative_path);
    void SetIconLocation(wchar_t* icon_location);

};

class Shortcut {

    private:
    bool ValidPath(const wchar_t* path);

    public:
    HRESULT CCI;
    IShellLinkW* ISL;
    ShortcutProperties* Properties = new ShortcutProperties;
    bool resolved = false;
    Shortcut();
    ~Shortcut();
    bool CreateShortcut(
        const wchar_t* LnkPath, 
        const wchar_t* TargetPath, 
        const wchar_t* Desc, 
        const wchar_t* Arguments,
        const wchar_t* WorkingDir,
        const wchar_t* RelativePath
    );
    bool ResolveShortcut(const wchar_t* LnkPath);
    wchar_t* GetArguments();
    wchar_t* GetDescription();
    wchar_t* GetIconLocation();
    int* GetIconIndex();
    wchar_t* GetPath();
    wchar_t* GetWorkingDirectory();
    
};

} // Namespace WindowsShortcut 

#endif