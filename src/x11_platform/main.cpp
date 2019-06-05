#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <vector>

#define WIDTH 800
#define HEIGHT 600

extern "C"
{
  void PlatformInit();
  void PlatformTick();
  void PlatformKeyDown(char key);
  void PlatformKeyUp(char key);
  void PlatformDisplay(int width, int height, unsigned char *buffer);
}

std::vector<unsigned char> buffer;

int main()
{
  int width = WIDTH;
  int height = HEIGHT;

  Display *display = XOpenDisplay(NULL);
  if(!display) abort();

  int screen = DefaultScreen(display);

  Window window = XCreateWindow(display,
    RootWindow(display, screen),
    0, 0, width, height, 0, 0,
    CopyFromParent, CopyFromParent,
    0, NULL);

  GC gc = DefaultGC(display, screen);

  XSelectInput(display, window,
    ExposureMask | KeyPressMask | KeyReleaseMask |
    ButtonPressMask | ButtonReleaseMask |
    StructureNotifyMask);

  Atom deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &deleteMessage, 1);
  XMapWindow(display, window);

  PlatformInit();

  char *data = (char *)malloc(width * height * 4);
  XImage *img = XCreateImage(display, DefaultVisual(display, screen),
    24, ZPixmap,
    0, data, width, height, 32, 0);

  XEvent e = {0};
  bool running = true;

  while(running)
  {
    while(XPending(display))
    {
      XNextEvent(display, &e);

      if(e.type == ConfigureNotify)
      {
        width = e.xconfigure.width;
        height = e.xconfigure.height;
        XDestroyImage(img);
        // free(data); // Not needed, XDestroyImage deletes data store
        data = (char *)malloc(width * height * 4);
        img = XCreateImage(display, DefaultVisual(display, screen),
          24, ZPixmap,
          0, data, width, height, 32, 0);
      }
      else if(e.type == ClientMessage)
      {
        if(e.xclient.data.l[0] == deleteMessage)
        {
          running = false;
        }
      }
      else if(e.type == KeyPress)
      {
        PlatformKeyDown(XLookupKeysym(&e.xkey, 0));
      }
      else if(e.type == KeyRelease)
      {
        PlatformKeyUp(XLookupKeysym(&e.xkey, 0));
      }
    }

    PlatformTick();

    if(buffer.size() < width * height * 3)
    {
      buffer.resize(width * height * 3);
    }

    PlatformDisplay(width, height, &buffer.at(0));
    unsigned char *p = &buffer.at(0);
    char *d = data;

    for(int i = 0; i < width * height; i++)
    {
      *(d + 0) = *(p + 2);
      *(d + 1) = *(p + 1);
      *(d + 2) = *(p + 0);
      *(d + 3) = (char)255;

      p += 3;
      d += 4;
    }

    XPutImage(display, window, gc, img, 0, 0, 0, 0, width, height);
  }

  return 0;
}
