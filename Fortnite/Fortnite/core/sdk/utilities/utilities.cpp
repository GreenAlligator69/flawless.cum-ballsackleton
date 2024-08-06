#pragma once 
#include "..\..\inc.hpp"

auto utilities::c_utilities::get_process_id(
	const std::wstring_view process_name ) -> const std::uint32_t
{
	HANDLE handle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	DWORD procID = NULL;

	if ( handle == INVALID_HANDLE_VALUE )
		return procID;

	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof( PROCESSENTRY32W );

	if ( Process32FirstW( handle, &entry ) ) {
		if ( !_wcsicmp( process_name.data( ), entry.szExeFile ) )
		{
			procID = entry.th32ProcessID;
		}
		else while ( Process32NextW( handle, &entry ) ) {
			if ( !_wcsicmp( process_name.data( ), entry.szExeFile ) ) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle( handle );
	return procID;
}

auto utilities::c_utilities::get_gamebar_sid(
	std::uint32_t process_id ) -> const std::wstring {

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, process_id );
	if ( hProcess == NULL ) {
		return L"";
	}

	HANDLE hToken;
	if ( !OpenProcessToken( hProcess, TOKEN_QUERY, &hToken ) ) {
		CloseHandle( hProcess );
		return L"";
	}

	DWORD tokenInfoLength = 0;
	if ( !GetTokenInformation( hToken, TokenAppContainerSid, NULL, 0, &tokenInfoLength ) && GetLastError( ) != ERROR_INSUFFICIENT_BUFFER ) {
		CloseHandle( hToken );
		CloseHandle( hProcess );
		return L"";
	}

	PTOKEN_APPCONTAINER_INFORMATION pAppContainerInfo = reinterpret_cast< PTOKEN_APPCONTAINER_INFORMATION >(new BYTE [ tokenInfoLength ]);
	if ( !GetTokenInformation( hToken, TokenAppContainerSid, pAppContainerInfo, tokenInfoLength, &tokenInfoLength ) ) {
		delete[ ] reinterpret_cast< BYTE* >(pAppContainerInfo);
		CloseHandle( hToken );
		CloseHandle( hProcess );
		return L"";
	}

	LPWSTR pSidString;
	if ( !ConvertSidToStringSidW( pAppContainerInfo->TokenAppContainer, &pSidString ) ) {
		delete[ ] reinterpret_cast< BYTE* >(pAppContainerInfo);
		CloseHandle( hToken );
		CloseHandle( hProcess );
		return L"";
	}

	std::wstring appSID( pSidString );
	LocalFree( pSidString );

	delete[ ] reinterpret_cast< BYTE* >(pAppContainerInfo);
	CloseHandle( hToken );
	CloseHandle( hProcess );
	return appSID;
}

auto utilities::c_utilities::attach_console( ) -> bool
{
	//auto result =  AllocConsole( );
	//if ( !result ) {
	//	return  false ;
	//}

	//freopen_s( &this->m_console, "CON", "w", stdout );
	//freopen_s( &this->m_console, "CON", "w", stderr );

	auto console_handle = GetConsoleWindow( );
	RECT r;
	GetWindowRect( console_handle, &r ); //stores the console's current dimensions
	MoveWindow( console_handle, r.left, r.top, 1150, 550, TRUE ); // 800 width, 100 height

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof( cfi );
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 16;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy( cfi.FaceName, ( L"Cascadia Code" ) ); 
	// 	std::wcscpy( cfi.FaceName, ( L"Geist" ) ); 
	SetCurrentConsoleFontEx( GetStdHandle( STD_OUTPUT_HANDLE ), FALSE, &cfi );
	//::SetWindowPos( console_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
	::ShowWindow( console_handle, SW_NORMAL );
	::SetConsoleTitleA( hash_str( "FN [fortnite]" ) );

	return true;
}

auto utilities::c_utilities::detach_console( ) -> void
{
	fclose( this->m_console );
	FreeConsole( );
}


auto utilities::c_utilities::timer_start(
	) -> std::chrono::steady_clock::time_point {

	this->m_time = std::chrono::high_resolution_clock::now( );
	return this->m_time;
}

auto utilities::c_utilities::timer_end( ) -> void
{
	auto time_span = std::chrono::duration_cast< std::chrono::microseconds >(
		std::chrono::high_resolution_clock::now( ) - this->m_time
	);

	std::printf( "\n [time(microseconds)] -> %d", time_span.count( ) );

}