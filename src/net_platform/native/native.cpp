#include <iostream>

extern "C"
{

void PlatformInit();
void PlatformTick();
void PlatformDisplay(int width, int height, int type, unsigned char *buffer);
void PlatformKeyDown(char key);
void PlatformKeyUp(char key);

}

extern "C" __declspec(dllexport) void native_platform_init()
{
  PlatformInit();
}

extern "C" __declspec(dllexport) void native_platform_tick()
{
  PlatformTick();
}

extern "C" __declspec(dllexport) void native_platform_display(int width, int height, int format, unsigned char *buffer)
{
  PlatformDisplay(width, height, format, buffer);
}

extern "C" __declspec(dllexport) void native_platform_keydown(char key)
{
  PlatformKeyDown(key);
}

extern "C" __declspec(dllexport) void native_platform_keyup(char key)
{
  PlatformKeyUp(key);
}