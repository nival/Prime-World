// PWClassicSandbox.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <Windows.h>
#include <Wininet.h>

#pragma comment(lib, "wininet.lib")

int main(int argc, char* argv[])
{
// Initialize variables


//const std::string jsonData2 = "{method:\"getUserBuild\",data:{id:\"%s\",hero:\"%d\"}}"

// Open Internet connection






// Output the response
std::cout << "Response: " << responseStream.c_str() << std::endl;
std::cin.get();
// Here, you would parse the JSON response, similar to the way it was done in C#
// You can use a JSON library like nlohmann/json for parsing the response in C++
return 0;
}