#include <iostream>

extern "C"
{

void PlatformInit();

}

extern "C" __declspec(dllexport) void nativetest()
{
  std::cout << "Hello World" << std::endl;
  PlatformInit();
}

extern "C" __declspec(dllexport) void nativearray(unsigned char *data)
{
  data[0] = 99;
}