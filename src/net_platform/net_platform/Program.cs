using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

class Program : Form
{
  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void nativetest();

  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void nativearray(byte[] data);

  byte[] buffer;

  Program()
  {
    buffer = new byte[128];
    nativetest();
    nativearray(buffer);
  }

  static void Main(string[] args)
  {
    Program program = new Program();
    Application.Run(program);
  }
}
