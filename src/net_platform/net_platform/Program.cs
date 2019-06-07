using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

class Program
{
  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void nativetest();

  static void Main(string[] args)
  {
    nativetest();
    Form form = new Form();
    Application.Run(form);
  }
}
