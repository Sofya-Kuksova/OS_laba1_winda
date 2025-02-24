#include "C:\Users\sonya\vscode\winda\include\file.h"

void CreateF(const char* filePath){
      HANDLE hFile = CreateFileA( // дескриптор (указатель на объект (ссылка на файл))
        filePath,               // Путь к файлу
        GENERIC_WRITE,          // Разрешение на запись
        0,                      // Без совместного доступа
        NULL,                   // Атрибуты безопасности (NULL - по умолчанию)
        CREATE_NEW,             // Создать новый файл (если файл уже существует — ошибка) (CREATE_ALWAYS)
        FILE_ATTRIBUTE_NORMAL,  // Обычный файл
        NULL                    // Без шаблонного файла
    );

      if (hFile == INVALID_HANDLE_VALUE) { // содержит не допустимый дескриптор
        std::cerr << "Ошибка при создании файла: " << GetLastError() << std::endl;
    } else {
        std::cout << "Файл успешно создан!" << std::endl;
        CloseHandle(hFile);  // Закрываем дескриптор файла (утечка памяти)
    }
}

void CopyF(const char* source, const char* destination){
    if (CopyFileA(source, destination, TRUE)) {  // если файл уже есть, выдаст ошибку; FALSE - перезапишет
        std::cout << "Файл успешно скопирован!" << std::endl;
    } else {
        std::cerr << "Ошибка при копировании файла. Код: " << GetLastError() << std::endl;
    }
}

void MoveF(const char* oldPath, const char* newPath){
    if (MoveFileExA(oldPath, newPath, MOVEFILE_COPY_ALLOWED)) {
        std::cout << "Файл успешно перемещен." << std::endl;
    } else {
        std::cout << "Ошибка при перемещении файла. Код ошибки: " << GetLastError() << std::endl;
    }
}

void MoveAndReplaceF(const char* source, const char* destination) {
    if (MoveFileExA(source, destination, MOVEFILE_REPLACE_EXISTING)) {
        std::cout << "Файл успешно перезаписан!\n";
    } else {
        std::cout << "Ошибка при перезаписи файла: " << GetLastError() << "\n";
    }
}

void GetAttributesF(const char* filePath){
    DWORD attributes = GetFileAttributesA(filePath); // битовая маска атрибутов 
    
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        std::cerr << "Ошибка при получении атрибутов файла. Код: " << GetLastError() << std::endl;
    }
    else {
    std::cout << "Атрибуты файла: " << std::hex << attributes << std::dec << std::endl;
    if (attributes & FILE_ATTRIBUTE_READONLY) std::cout << " - Только для чтения\n";
    if (attributes & FILE_ATTRIBUTE_HIDDEN) std::cout << " - Скрытый\n";
    if (attributes & FILE_ATTRIBUTE_SYSTEM) std::cout << " - Системный\n";
    if (attributes & FILE_ATTRIBUTE_DIRECTORY) std::cout << " - Это папка\n";
    if (attributes & FILE_ATTRIBUTE_ARCHIVE) std::cout << " - Архивный\n";
    }
}

void SetAttributesF(const char* filePath){
    std::cout << "\nВыберите атрибуты, введя соответствующие цифры (например, 14 для скрытого и архивного):\n";
    std::cout << "1 - Только для чтения (READONLY)\n";
    std::cout << "2 - Скрытый (HIDDEN)\n";
    std::cout << "3 - Системный (SYSTEM)\n";
    std::cout << "4 - Архивный (ARCHIVE)\n";
    std::cout << "5 - Обычный файл (NORMAL) (Сбросит все другие атрибуты)\n";
    std::cout << "Введите комбинацию цифр: ";

    std::string input;
    std::cin >> input;

    DWORD attributes = 0;

    for (char c : input) {
        switch (c) {
            case '1': attributes |= FILE_ATTRIBUTE_READONLY; break; // битовое или
            case '2': attributes |= FILE_ATTRIBUTE_HIDDEN; break;
            case '3': attributes |= FILE_ATTRIBUTE_SYSTEM; break;
            case '4': attributes |= FILE_ATTRIBUTE_ARCHIVE; break;
            case '5': attributes = FILE_ATTRIBUTE_NORMAL; break; // Сбрасывает все флаги
            default: std::cout << "Некорректный ввод: " << c << std::endl;
        }
    }

    // Устанавливаем атрибуты
    if (SetFileAttributesA(filePath, attributes)) {
        std::cout << "Атрибуты файла успешно изменены!\n";
    } else {
        std::cerr << "Ошибка при изменении атрибутов файла. Код ошибки: " << GetLastError() << std::endl;
    }
}

void GetInformationF(const char* filePath){
    // Открываем файл, чтобы получить дескриптор
    HANDLE hFile = CreateFileA(
        filePath,            // Путь к файлу
        GENERIC_READ,        // Доступ только на чтение
        FILE_SHARE_READ,     // Разрешаем другим процессам читать файл
        NULL,                // Без атрибутов безопасности
        OPEN_EXISTING,       // Файл должен существовать
        FILE_ATTRIBUTE_NORMAL, // Обычный файл
        NULL                 // Нет шаблона
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка при открытии файла. Код: " << GetLastError() << std::endl;
        return;
    }

    // Структура для информации о файле
    BY_HANDLE_FILE_INFORMATION fileInfo;
    
    // Получаем информацию о файле
    if (GetFileInformationByHandle(hFile, &fileInfo)) { // дескриптор, указатель на струкутру
        std::cout << "Атрибуты файла: " << fileInfo.dwFileAttributes << std::endl; // битовая маску атрибутов
        std::cout << "Размер файла: " << ((static_cast<ULONGLONG>(fileInfo.nFileSizeHigh) << 32) | fileInfo.nFileSizeLow) << " байт" << std::endl; // две 32-битные переменные (ULONGLONG)
        // сдвигаем старшие 32 влево и на из место младшие, Если файл меньше 4 ГБ, nFileSizeHigh будет 0, всё в nFileSizeLow 
        std::cout << "Количество жёстких ссылок: " << fileInfo.nNumberOfLinks << std::endl; //  разные имена указывают на один и тот же файл (пока есть хоть одна ссылка - не удалится)
        std::cout << "Серийный номер тома: " << fileInfo.dwVolumeSerialNumber << std::endl; // раздел жёсткого диска, на котором хранится файл
    } else {
        std::cerr << "Ошибка при получении информации о файле. Код: " << GetLastError() << std::endl;
    }

    // Закрываем дескриптор файла
    CloseHandle(hFile);
}

void PrintFileTime(const FILETIME& ft) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);  // Преобразуем FILETIME в SYSTEMTIME
    
    std::cout << std::setw(2) << std::setfill('0') << st.wDay << "." //std::setw(2) — задаёт ширину поля в 2 символа.
              << std::setw(2) << std::setfill('0') << st.wMonth << "." //std::setfill('0') — заполняет недостающие символы нулями.
              << st.wYear << " "
              << std::setw(2) << std::setfill('0') << st.wHour << ":"
              << std::setw(2) << std::setfill('0') << st.wMinute << ":"
              << std::setw(2) << std::setfill('0') << st.wSecond << std::endl;
}

void GetTimeF(const char* filePath){
      // Открываем файл, чтобы получить дескриптор
      HANDLE hFile = CreateFileA(
        filePath,            // Путь к файлу
        GENERIC_READ,        // Доступ только на чтение
        FILE_SHARE_READ,     // Разрешаем другим процессам читать файл
        NULL,                // Без атрибутов безопасности
        OPEN_EXISTING,       // Файл должен существовать
        FILE_ATTRIBUTE_NORMAL, // Обычный файл
        NULL                 // Нет шаблона
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка открытия файла. Код: " << GetLastError() << std::endl;
        return;
    }

    FILETIME creationTime, accessTime, writeTime; // 100-нс интервалы
    
    if (GetFileTime(hFile, &creationTime, &accessTime, &writeTime)) {
        std::cout << "Дата создания: ";
        PrintFileTime(creationTime);

        std::cout << "Дата последнего доступа: ";
        PrintFileTime(accessTime);

        std::cout << "Дата последнего изменения: ";
        PrintFileTime(writeTime);
    } else {
        std::cerr << "Ошибка при получении временных меток. Код: " << GetLastError() << std::endl;
    }

    CloseHandle(hFile);
}

// Функция для ввода даты и времени
void InputDateTime(SYSTEMTIME &st) {
    std::cout << "Введите дату и время (ДД ММ ГГГГ ЧЧ ММ CC): ";
    std::cin >> st.wDay >> st.wMonth >> st.wYear >> st.wHour >> st.wMinute >> st.wSecond;
}

void SetTimeF(const char* filePath) {
    // Открываем файл для получения дескриптора
    HANDLE hFile = CreateFileA(
        filePath,             // Путь к файлу
        GENERIC_WRITE,        // Доступ на запись
        0,                    // Файл не разделяется с другими процессами
        NULL,                 // Без атрибутов безопасности
        OPEN_EXISTING,        // Файл должен существовать
        FILE_ATTRIBUTE_NORMAL, // Обычный файл
        NULL                  // Нет шаблона
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка открытия файла. Код: " << GetLastError() << std::endl;
        return;
    }

    // Получаем текущее время файла, чтобы не потерять невыбранные метки
    FILETIME ftCreation, ftAccess, ftWrite;
    if (!GetFileTime(hFile, &ftCreation, &ftAccess, &ftWrite)) {
        std::cerr << "Ошибка получения текущего времени файла. Код: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return;
    }

    SYSTEMTIME stCreation, stAccess, stWrite;
    bool changeCreation = false, changeAccess = false, changeWrite = false;

    std::cout << "Выберите временные метки для изменения:\n";
    std::cout << "1 - Дата создания\n";
    std::cout << "2 - Дата последнего доступа\n";
    std::cout << "3 - Дата последнего изменения\n";
    std::cout << "Введите номера (например, 1 3): ";

    std::string choices;
    std::cin >> choices;

    for (char choice : choices) {
        switch (choice) {
            case '1':
                std::cout << "\nВведите новую дату создания:\n";
                InputDateTime(stCreation);
                SystemTimeToFileTime(&stCreation, &ftCreation);
                changeCreation = true;
                break;
            case '2':
                std::cout << "\nВведите новую дату последнего доступа:\n";
                InputDateTime(stAccess);
                SystemTimeToFileTime(&stAccess, &ftAccess);
                changeAccess = true;
                break;
            case '3':
                std::cout << "\nВведите новую дату последнего изменения:\n";
                InputDateTime(stWrite);
                SystemTimeToFileTime(&stWrite, &ftWrite);
                changeWrite = true;
                break;
        }
    }

    if (SetFileTime(
        hFile, 
        changeCreation ? &ftCreation : NULL, 
        changeAccess ? &ftAccess : NULL, 
        changeWrite ? &ftWrite : NULL
    )) {
        std::cout << "Временные метки файла успешно изменены!\n";
    } else {
        std::cerr << "Ошибка изменения времени файла. Код: " << GetLastError() << std::endl;
    }

    CloseHandle(hFile);
}