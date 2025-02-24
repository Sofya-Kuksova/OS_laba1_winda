#include <windows.h>
#include <iostream>
#include <limits>
#include "C:\Users\sonya\vscode\winda\include\drive.h"
#include "C:\Users\sonya\vscode\winda\include\directory.h"
#include "C:\Users\sonya\vscode\winda\include\file.h"

void ShowMenu() {
    std::cout << "\n--- Меню ---\n";
    std::cout << "[1] Вывести список дисков\n";
    std::cout << "[2] Вывести информацию о диске\n";
    std::cout << "[3] Создать каталог\n";
    std::cout << "[4] Удалить каталог\n";
    std::cout << "[5] Создать файл\n";
    std::cout << "[6] Копировать файл\n";
    std::cout << "[7] Переместить файл \n";
    std::cout << "[8] Перезаписать файл\n";
    std::cout << "[9] Вывести атрибуты файла\n";
    std::cout << "[10] Установить атрибуты файла\n";
    std::cout << "[11] Вывести информацию о файле\n";
    std::cout << "[12] Вывести время создания, последнего доступа, последнего редактирования файла\n";
    std::cout << "[13] Изменить время последнего доступа, последнего редактирования файла\n";
    std::cout << "[0] Выход\n";
}

bool IsValidDrivePath(const char* path) {
    // Проверяем, что путь не пустой и длиннее 2 символов
    if (path == nullptr || strlen(path) < 3) {
        return false;
    }

    // Проверяем, что первый символ - буква, а второй символ - ':'
    if (!isalpha(path[0]) || path[1] != ':') {
        return false;
    }

    // Проверяем, что третий символ - '\\'
    if (path[2] != '\\') {
        return false;
    }
    return true;
}

int main() {
    int choice;
    
    do {
        ShowMenu();
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        if (std::cin.fail() || std::cin.peek() != '\n') { // перешёл ли поток ввода в режим ошибки (проверяет следующий символ в потоке без удаления его.)
        std::cin.clear();  // сбрасываем поток 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очищает буфер и позволяет ввести новое значение.
        std::cout << "Некорректный ввод. Попробуйте снова.\n";
        continue; // возвращает пользователя к выбору пункта меню
        }

        switch (choice) {
            case 1:
                PrintDriveList();
                break;
            case 2: {
                bool validPath = false;
                char selectedDrive[MAX_PATH];
                // Очистка потока ввода от оставшегося символа новой строки (при вводе числа)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while (!validPath) {
                    std::cout << "\nВведите имя диска для получения информации (например, C:\\\\ ): ";
                    std::cin.getline(selectedDrive, MAX_PATH);
                    // Проверка пути
                    if (IsValidDrivePath(selectedDrive)) {
                    std::cout << "Путь \"" << selectedDrive << "\" является корректным для диска." << std::endl;
                    validPath = true;
                    } else {
                        std::cout << "Путь \"" << selectedDrive << "\" неверен." << std::endl;
                    }
                }
                PrintDriveInfo(selectedDrive);
                break;
            }
            case 3:{
                char selectedDirectory[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nВведите путь католога, который хотите создать: ";
                std::cin.getline(selectedDirectory, MAX_PATH);
                CreateCatalog(selectedDirectory);
                break;
            } 
            case 4:{
                char selectedDirectory[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nКаталог должен быть пуст";
                std::cout << "\nВведите путь католога, который хотите удалить: ";
                std::cin.getline(selectedDirectory, MAX_PATH);
                RemoveCatalog(selectedDirectory);
                break;
            }
            case 5:{
                char selectedfile[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)\nНельзя создать существующий объект";
                std::cout << "\nВведите путь файла, который хотите создать: ";
                std::cin.getline(selectedfile, MAX_PATH);
                CreateF(selectedfile);
                break;
            }
            case 6:{
                char sourcefile[MAX_PATH];
                char copyfile[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)\nЕсли файл по пути назначения не существует → файл будет успешно скопирован";
                std::cout << "\nВведите путь исходного файла:";
                std::cin.getline(sourcefile, MAX_PATH);
                std::cout << "\nВведите путь файла-копии:";
                std::cin.getline(copyfile, MAX_PATH);
                CopyF(sourcefile, copyfile);
                break;
            }
            case 7:{
                char oldpath[MAX_PATH];
                char newpath[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)";
                std::cout <<"\n- Функция работает в пределах одного диска, и между разными дисками\n- Если новый путь указывает на другой каталог → файл переместится\n- Если новый путь указывает на тот же каталог → файл просто переименуется\n- Если в целевой папке уже существует файл с таким же именем, функция не заменит его, а операция завершится ошибкой";
                std::cout << "\nВведите путь исходного файла:";
                std::cin.getline(oldpath, MAX_PATH);
                std::cout << "\nВведите путь файла назначения для перемещения:";
                std::cin.getline(newpath, MAX_PATH);
                MoveF(oldpath,newpath);
                break;
            }
            case 8:{
                char sourcefile[MAX_PATH];
                char copyfile[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)";
                std::cout<<"\n- Если в целевой папке уже есть файл с таким же именем, он заменяется новым\n- Старый файл в исходном месте удаляется\n- Исходное имя файла и имя файла назначения должны совпадать, иначе ошибка";
                std::cout << "\nВведите путь исходного файла:";
                std::cin.getline(sourcefile, MAX_PATH);
                std::cout << "\nВведите путь файла назначения для перезаписи(можно существующий) (Полностью заменяет файл - содержимое, удаляя старый.): ";
                std::cin.getline(copyfile, MAX_PATH);
                MoveAndReplaceF(sourcefile, copyfile);
                break;

            }
            case 9:{
                char selectedfile[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)";
                std::cout << "\nВведите путь файла:";
                std::cin.getline(selectedfile, MAX_PATH);
                GetAttributesF(selectedfile);
                break;
            }
            case 10:{
                char selectedfile[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)";
                std::cout << "\nВведите путь файла:";
                std::cin.getline(selectedfile, MAX_PATH);
                SetAttributesF(selectedfile);
                break;
            }
            case 11:{
                char filepath[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)";
                std::cout << "\nВведите путь файла, о котором хотите получить информацию: ";
                std::cin.getline(filepath, MAX_PATH);
                GetInformationF(filepath);
                break;
            }
            case 12:{
                char filepath[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)\n- Coordinated Universal Time (UTC)";
                std::cout << "\nВведите путь файла, о котором хотите получить информацию: ";
                std::cin.getline(filepath, MAX_PATH);
                GetTimeF(filepath);
                break;
            }
            case 13:{
                char filepath[MAX_PATH];
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Особенности функции:";
                std::cout << "\nC:\\\\file.txt - абсолютный путь, file.txt - относительный путь (относительно текущей рабочей директории)\n- Coordinated Universal Time (UTC)\n- Файл не должен содержать атрибутов `Только для чтения` или `Системный файл`\nЭто может препятствовать изменению временных парамтеров";
                std::cout << "\nВведите путь файла, о котором хотите изменить информацию: ";
                std::cin.getline(filepath, MAX_PATH);
                SetTimeF(filepath);
                break;
            }
            case 0:
                std::cout << "Выход из программы...\n";
                break;
            default:
                std::cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}