/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef WINDOWS_PLANTFORM_MACRO_H
#define WINDOWS_PLANTFORM_MACRO_H

#include <windows.h>

#include <minwindef.h>

#ifdef DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif

/**
 * @brief Convert char string to LPCWSTR, windows platform only
 * @param charArray The pointer of const char array 
 */
#define CHAR2LPCWSTR(charArray) (convertCharArrayToLPCWSTR(charArray))


static auto convertCharArrayToLPCWSTR(const char *charArray) -> wchar_t *
{
    auto *wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

#endif
