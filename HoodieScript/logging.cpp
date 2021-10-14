#include "pch.h"
#include "logging.h"

namespace hoodie_script {
    FILE* logging::_stdoutHandle;
    FILE* logging::_stderrHandle;
    FILE* logging::_stdinHandle;
    std::ofstream logging::_fileHandle;

    void logging::init() {
        allocate_console();
        open_log_file();
    }

    void logging::deinit() {
        free_console();
        close_log_file();
    }

    void logging::write_line(std::string message) {
        std::ostringstream logEntry;
        logEntry << banner() << message << std::endl;
        log(logEntry.str());
    }

    void logging::write_line(const char* format, ...) {
        std::ostringstream logEntry;
        char messageBuffer[1000]{};

        va_list args;
        va_start(args, format);
        vsprintf_s(&messageBuffer[0], 1000, format, args);
        va_end(args);

        logEntry << banner() << std::string(messageBuffer) << std::endl;
        log(logEntry.str());
    }

    void logging::allocate_console() {
        AllocConsole();
        SetConsoleTitleA(LOG_CONSOLE_NAME);
        freopen_s(&_stdoutHandle, "CONOUT$", "w", stdout);
        freopen_s(&_stderrHandle, "CONOUT$", "w", stderr);
        freopen_s(&_stdinHandle, "CONIN$", "r", stdin);
    }

    void logging::free_console() {
        std::cout.clear();
        fclose(_stdoutHandle);
        fclose(_stderrHandle);
        fclose(_stdinHandle);
        FreeConsole();
    }

    void logging::open_log_file() {
        _fileHandle.open(LOG_FILE_NAME);
        if (!_fileHandle.is_open()) {
            write_to_console("Could not open file handle");
        }
    }

    void logging::close_log_file() {
        if (_fileHandle.is_open()) {
            _fileHandle.close();
        }
    }

    std::string logging::banner()
    {
        std::ostringstream banner;
        banner << "[" << get_time() << " " << LOG_BANNER << "] ";
        return banner.str();
    }

    std::string logging::get_time() {
        time_t rawtime;
        struct tm timeinfo;
        char _buffer[80];

        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);

        strftime(_buffer, sizeof(_buffer), "%H:%M:%S", &timeinfo);
        return { _buffer };
    }

    void logging::write_to_console(std::string message) {
        std::cout << message;
    }

    void logging::write_to_file(std::string message) {
        if (_fileHandle.is_open()) {
            _fileHandle << message;
            _fileHandle.flush();
        }
        else {
            write_to_console("could not write to file handle!");
        }
    }

    void logging::log(std::string entry) {
        write_to_console(entry);
        write_to_file(entry);
    }
}
