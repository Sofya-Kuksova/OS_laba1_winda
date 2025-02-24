#ifndef DRIVE_H // проверяет, не был ли этот файл уже включён ранее (Include guard )
#define DRIVE_H // Если ещё не определён, его определяет

#include <windows.h>
#include <iostream>

void PrintDriveList();
void PrintDriveInfo(const char* drive);

#endif // DRIVE_H // Закрытие include guard (ifndef)
