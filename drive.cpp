#include "C:\Users\sonya\vscode\winda\include\drive.h"

void PrintDriveList() {
     // Именованная константа для размера буфера
    constexpr DWORD BUFFER_SIZE = 1024; 

    // Буфер для хранения строк дисков
    char buffer[BUFFER_SIZE];

    // Получаем список дисков
    DWORD result = GetLogicalDriveStringsA(BUFFER_SIZE - 1, buffer); // оставили место для завершающего символа строки

    if (result == 0) {
        std::cerr << "Ошибка при получении списка дисков." << std::endl; // поток ошибок
    }

    std::cout << "Список доступных дисков:" << std::endl;

    // Переменная для итерации по буферу
    char* drive = buffer;

    // Перебираем все диски в буфере
    while (*drive != '\0') {
        std::cout << drive << std::endl;
        drive += strlen(drive) + 1; // Переходим к следующей строке
    }

}

void PrintDriveInfo(const char* drive) {
    // Определяем тип диска
    UINT driveType = GetDriveTypeA(drive);
    const char* typeStr = "Неизвестный";
    
    switch (driveType) {
        case DRIVE_FIXED: typeStr = "Жесткий диск"; break;
        case DRIVE_REMOVABLE: typeStr = "Съемный диск"; break;
        case DRIVE_CDROM: typeStr = "CD/DVD диск"; break;
        case DRIVE_RAMDISK: typeStr = "RAM диск"; break;
        case DRIVE_REMOTE: typeStr = "Сетевой диск"; break;
        case DRIVE_NO_ROOT_DIR: typeStr = "Недоступен"; break;
    }

    std::cout << "\nДиск: " << drive << std::endl;
    std::cout << "Тип диска: " << typeStr << std::endl;
    // Получаем информацию о томе диска
    char volumeName[MAX_PATH] = {0};
    char fileSystem[MAX_PATH] = {0};
    DWORD serialNumber = 0, maxComponentLen = 0, fileSystemFlags = 0;

    if (GetVolumeInformationA(drive, volumeName, MAX_PATH, &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystem, MAX_PATH)) { // путь тома, буфер тома, размер буфера тома, Указатель на серийный номер тома, указатель на максимальная длина имени файла на томе, флаги, определяющие характеристики файловой системы, буфер для имени файловой системы, его длина
        std::cout << "Метка тома: " << (volumeName[0] ? volumeName : "Нет") << std::endl;
        std::cout << "Файловая система: " << fileSystem << std::endl;
        std::cout << "Серийный номер: " << serialNumber << std::endl;

         // Выводим флаги файловой системы
    std::cout << "Флаги файловой системы: 0x" << std::hex << fileSystemFlags << std::dec << std::endl; // битовая маска, несколько флагов, описывающих особенности файловой системы 

    // Пример интерпретации флагов:
    if (fileSystemFlags & FILE_SUPPORTS_USN_JOURNAL) {
        std::cout << "- Поддержка USN журнала" << std::endl;
    }
    if (fileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS) {
        std::cout << "- Поддержка репарсинг точек" << std::endl;
    }
    if (fileSystemFlags & FILE_SUPPORTS_SPARSE_FILES) {
        std::cout << "- Поддержка разреженных файлов" << std::endl;
    }
    if (fileSystemFlags & FILE_VOLUME_IS_COMPRESSED) {
        std::cout << "- Том сжат" << std::endl;
    }
    if (fileSystemFlags & FILE_SUPPORTS_OBJECT_IDS) {
        std::cout << "- Поддержка идентификаторов объектов" << std::endl;
    }
    if (fileSystemFlags & FILE_SUPPORTS_ENCRYPTION) {
        std::cout << "- Поддержка шифрования" << std::endl;
    }
    } else {
        std::cout << "Не удалось получить информацию о томе." << std::endl;
    }

   ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
    
    // Получаем информацию о свободном и общем пространстве на диске
    if (GetDiskFreeSpaceExA(drive, &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
        // Вывод всех трех параметров
        std::cout << "Общий размер диска: " << totalBytes.QuadPart / (1024 * 1024 * 1024) << " ГБ" << std::endl;
        std::cout << "Свободное пространство: " << totalFreeBytes.QuadPart / (1024 * 1024 * 1024) << " ГБ" << std::endl;
        std::cout << "Доступное пространство для пользователя: " << freeBytesAvailable.QuadPart / (1024 * 1024 * 1024) << " ГБ" << std::endl;
    } else {
        std::cout << "Ошибка при получении информации о диске." << std::endl;
    }
}
