// PWClassicSandbox.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <Windows.h>
#include <Wininet.h>

#pragma comment(lib, "wininet.lib")

int main(int argc, char* argv[])
{
// Initialize variables
const std::string apiUrl = "https://playpw.fun";
const std::string apiEndpoint = "/api/launcher/";
const std::string jsonData = "{\"method\": \"getUserByToken\", \"data\": {\"token\": \"9a6513c4b7ea501817e7369e9b026b4f\"}}";

// Open Internet connection
HINTERNET hInternet = InternetOpen(L"HTTP Post Request", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
if (hInternet == NULL) {
    std::cerr << "InternetOpen failed with error: " << GetLastError() << std::endl;
    return 1;
}

// Connect to the server
HINTERNET hConnect = InternetConnect(hInternet, L"playpw.fun", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
if (hConnect == NULL) {
    std::cerr << "InternetConnect failed with error: " << GetLastError() << std::endl;
    InternetCloseHandle(hInternet);
    return 1;
}

// Open the HTTP request
HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", L"/api/launcher/", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
if (hRequest == NULL) {
    std::cerr << "HttpOpenRequest failed with error: " << GetLastError() << std::endl;
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return 1;
}

// Set headers and data for the POST request
const char* headers = "Content-Type: application/json\r\n";
const char* postData = jsonData.c_str();
DWORD postDataLen = jsonData.length();

// Send the HTTP request
BOOL bRequestSent = HttpSendRequestA(hRequest, headers, -1L, (LPVOID)postData, postDataLen);
if (!bRequestSent) {
    std::cerr << "HttpSendRequest failed with error: " << GetLastError() << std::endl;
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return 1;
}

// Read the response
char buffer[4096];
DWORD bytesRead = 0;
std::string responseStream;

while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    responseStream += buffer;
}

// Close handles
InternetCloseHandle(hRequest);
InternetCloseHandle(hConnect);
InternetCloseHandle(hInternet);

// Output the response
std::cout << "Response: " << responseStream.c_str() << std::endl;
std::cin.get();
// Here, you would parse the JSON response, similar to the way it was done in C#
// You can use a JSON library like nlohmann/json for parsing the response in C++
return 0;
}