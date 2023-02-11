#pragma once
#include <iostream>
#include <wtypes.h>
using namespace std;

string ReadRegistryValue(HKEY hKey, const string& path, const string& valueName)
{
    HKEY hOpenedKey;
    LONG result = RegOpenKeyExA(hKey, path.c_str(), 0, KEY_READ, &hOpenedKey);
    if (result != ERROR_SUCCESS) {
        cout << "RegOpenKeyExA failed with error: " << result << endl;
        system("pause");
        return string();
    }

    DWORD valueType;
    DWORD valueSize;
    result = RegQueryValueExA(hOpenedKey, valueName.c_str(), 0, &valueType, 0, &valueSize);
    if (result != ERROR_SUCCESS) {
        cout << "RegQueryValueExA failed with error: " << result << endl;
        system("pause");
        RegCloseKey(hOpenedKey);
        return string();
    }

    if (valueType != REG_SZ) {
        cout << "Unexpected value type: " << valueType << endl;
        system("pause");
        RegCloseKey(hOpenedKey);
        return string();
    }

    char* value = new char[valueSize];
    result = RegQueryValueExA(hOpenedKey, valueName.c_str(), 0, &valueType, (BYTE*)value, &valueSize);
    if (result != ERROR_SUCCESS) {
        cout << "RegQueryValueExA failed with error: " << result << endl;
        system("pause");
        delete[] value;
        RegCloseKey(hOpenedKey);
        return string();
    }

    string valueStr(value, valueSize - 1);
    delete[] value;
    RegCloseKey(hOpenedKey);

    return valueStr;
}