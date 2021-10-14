#pragma once

#include <ctime>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>

#define LOG_BANNER "HOODIESCRIPT"
#define LOG_FILE_NAME "hoodiescript.log"
#define LOG_CONSOLE_NAME "HoodieScriptExtender"

namespace hoodie_script {
    class logging {
    public:
        static void init();
        static void deinit();

        static void write_line(std::string message);
        static void write_line(const char* format, ...);
    private:
        static void allocate_console();
        static void free_console();
        static void open_log_file();
        static void close_log_file();

        static void log(std::string message);
        static void write_to_console(std::string message);
        static void write_to_file(std::string message);

        static std::string banner();
        static std::string get_time();

        static FILE* _stdoutHandle;
        static FILE* _stderrHandle;
        static FILE* _stdinHandle;
        static std::ofstream _fileHandle;
    };
}