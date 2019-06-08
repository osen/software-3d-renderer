using System;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;
using System.IO;

class Program : Form
{
  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void native_platform_init();

  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void native_platform_tick();

  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void native_platform_display(int width, int height, int format, IntPtr buffer);

  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void native_platform_keydown(char key);

  [DllImport("native", CallingConvention = CallingConvention.Cdecl)]
  extern static void native_platform_keyup(char key);

  Timer timer;
  Bitmap bm;

  Program()
  {
    ClientSize = new Size(800, 600);
    bm = new Bitmap(ClientSize.Width, ClientSize.Height, PixelFormat.Format24bppRgb);

    native_platform_init();

    timer = new Timer();
    timer.Interval = 1;
    timer.Tick += new EventHandler(Tick);
    timer.Start();
  }

  private void Tick(object sender, EventArgs e)
  {
    native_platform_tick();
    Invalidate();
  }

  protected override void OnKeyDown(KeyEventArgs e)
  {
    base.OnKeyDown(e);

    string key = "" + (char)e.KeyValue;
    key = key.ToLower();
    char c = key[0];
    native_platform_keydown(c);
  }

  protected override void OnKeyUp(KeyEventArgs e)
  {
    base.OnKeyUp(e);

    string key = "" + (char)e.KeyValue;
    key = key.ToLower();
    char c = key[0];
    native_platform_keyup(c);
  }

  protected override void OnPaintBackground(PaintEventArgs e)
  {
    int Width = ClientSize.Width;
    int Height = ClientSize.Height;

    Width -= Width % 4;

    Graphics g = e.Graphics;
    g.InterpolationMode = InterpolationMode.NearestNeighbor;

    if(bm.Width != Width || bm.Height != Height)
    {
      bm = new Bitmap(Width, Height, PixelFormat.Format24bppRgb);
    }

    BitmapData da = bm.LockBits(new Rectangle(0, 0, bm.Width, bm.Height), ImageLockMode.WriteOnly, bm.PixelFormat);
    native_platform_display(Width, Height, 6, da.Scan0);
    bm.UnlockBits(da);

    Rectangle dest = new Rectangle(0, 0, Width, Height);
    Rectangle src = new Rectangle(0, 0, 320, 240);

    g.DrawImage(bm, dest, src, GraphicsUnit.Pixel);
    //g.DrawImage(bm, 0, 0);
  }

  static void Main(string[] args)
  {
    Program program = new Program();
    Application.Run(program);
  }
}
