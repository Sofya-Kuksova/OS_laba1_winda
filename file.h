#ifndef FILE_H
#define FILE_H

#include <windows.h>
#include <iostream>
#include <iomanip>  // Для setw и setfill
#include <sstream>
#include <vector>

void CreateF(const char* filePath);
void CopyF(const char* source, const char* destination);
void MoveF(const char* oldPath, const char* newPath);
void MoveAndReplaceF(const char* source, const char* destination);
void GetAttributesF(const char* filePath);
void SetAttributesF(const char* filePath);
void GetInformationF(const char* filePath);
void GetTimeF(const char* filePath);
void SetTimeF(const char* filePath);

#endif