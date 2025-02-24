#include "C:\Users\sonya\vscode\winda\include\directory.h"

void CreateCatalog(const char* dirName) {
    // Попытка создать каталог
    if (CreateDirectoryA(dirName, NULL)) { // путь к каталогу, права доступа (стандарт)
        std::cout << "Каталог " << dirName << " успешно создан." << std::endl;
    } else {
        DWORD error = GetLastError();
        std::cerr << "Ошибка при создании каталога: " << error << std::endl;
    }
}

void RemoveCatalog(const char* dirName){
    if (RemoveDirectoryA(dirName)) {
        std::cout << "Каталог был успешно удален." << std::endl;
    } else {
        DWORD error = GetLastError();
        std::cerr << "Ошибка при удалении каталога. Код ошибки: " << error << std::endl;
    }
}



