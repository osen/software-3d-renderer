#include <iostream>

extern "C" __declspec(dllexport) void nativetest()
{
  std::cout << "Hello" << std::endl;
}
