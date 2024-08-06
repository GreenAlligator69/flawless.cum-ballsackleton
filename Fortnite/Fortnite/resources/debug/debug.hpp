#pragma once 
#include "termcolor.hpp"

namespace debug {
    inline std::string getCurrentDateTime( ) {
        auto now = std::chrono::system_clock::now( );

        std::time_t now_c = std::chrono::system_clock::to_time_t( now );

        std::tm now_tm = *std::localtime( &now_c );

        std::stringstream ss;
        ss << std::put_time( &now_tm, "%Y-%m-%d %H:%M:%S" );

        return ss.str( );
    }

    inline void print( const char* func_name, int line, const char* str, ... ) {
        std::cout << termcolor::bright_red << hash_str( "[FN_event] " );
        std::cout << termcolor::bright_grey << getCurrentDateTime( ).c_str( );
        std::cout << termcolor::bright_yellow << " " << func_name;
        std::cout << termcolor::bright_yellow << ":" << line;

        char buffer[4096];
        va_list args;
        va_start( args, str );
        int rc = vsnprintf( buffer, sizeof( buffer ), str, args );
        va_end( args );

        std::cout << " " << termcolor::white << buffer;
    }

    inline void print_info( const char* func_name, int line, const char* str, ... ) {
        std::cout << termcolor::bright_red << hash_str( "[FN_event] " );
        std::cout << termcolor::bright_grey << getCurrentDateTime( ).c_str( );
        std::cout << termcolor::bright_yellow << " " << func_name;
        std::cout << termcolor::bright_yellow << ":" << line;

        char buffer[4096];
        va_list args;
        va_start( args, str );
        int rc = vsnprintf( buffer, sizeof( buffer ), str, args );
        va_end( args );

        std::cout << " " << termcolor::bright_cyan << buffer;
    }
    inline void print_error( bool bold, const char* func_name, int line, const char* str, ... ) {
        std::cout << termcolor::bright_red << hash_str( "[FN_event] " );
        std::cout << termcolor::bright_grey << getCurrentDateTime( ).c_str( );
        std::cout << termcolor::bright_yellow << " " << func_name;
        std::cout << termcolor::bright_yellow << ":" << line;

        char buffer[4096];
        va_list args;
        va_start( args, str );
        int rc = vsnprintf( buffer, sizeof( buffer ), str, args );
        va_end( args );

        if ( bold ) {
            std::cout << " " << termcolor::on_bright_red << termcolor::grey << buffer;
        }
        else
        {
            std::cout << " " << termcolor::bright_red << buffer;
        }
    }

}

#define print(a, ...) debug::print(__FILE__, __LINE__, a, ##__VA_ARGS__);
#define print_info(a, ...) debug::print_info(__FILE__, __LINE__, a, ##__VA_ARGS__);
#define print_error(a, b, ...) debug::print_error(b, __FILE__, __LINE__, a, ##__VA_ARGS__);