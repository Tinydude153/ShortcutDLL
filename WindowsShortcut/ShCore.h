#pragma once
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
#include "pch.h"

namespace WindowsShortcut {

    struct ShortcutProperties {

        ~ShortcutProperties();

        // All properties are heap allocated for simple destructor.
        wchar_t* TargetPath = 0;
        wchar_t* Description = 0;
        wchar_t* Arguments = 0;
        wchar_t* WorkingDirectory = 0;
        wchar_t* RelativePath = 0;
        wchar_t* IconLocation = 0;
        int* IconIndex = 0;

        void SetTargetPath(const wchar_t* target_path);
        wchar_t* GetTargetPath();
        void SetDescription(const wchar_t* description);
        wchar_t* GetDescription();
        void SetArguments(const wchar_t* arguments);
        wchar_t* GetArguments();
        void SetWorkingDirectory(const wchar_t* working_directory);
        wchar_t* GetWorkingDirectory();
        void SetRelativePath(const wchar_t* relative_path);
        wchar_t* GetRelativePath();
        void SetIconLocation(const wchar_t* icon_location);
        wchar_t* GetIconLocation();
        int* GetIconIndex();

    };

    class Shortcut {

    private:
        // Validates the existence of a path.
        bool ValidPath(const wchar_t* path);
        // Used at the beginning of CreateShortcut() and ResolveShortcut()
        bool CoInit();

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

        // Every get function returns a heap allocated buffer of the result if not null.
        wchar_t* GetArguments();
        wchar_t* GetDescription();
        wchar_t* GetIconLocation();
        int* GetIconIndex();
        wchar_t* GetPath();
        wchar_t* GetWorkingDirectory();

    };

} // Namespace WindowsShortcut 

#endif
