#include <iostream>

extern "C"
{

void PlatformInit();

}

extern "C" __declspec(dllexport) void nativetest()
{
  std::cout << "Hello" << std::endl;
  PlatformInit();
}
