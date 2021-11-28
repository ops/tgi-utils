/*
 * Adapted from:
 *
 * https://github.com/cc65/cc65/blob/master/samples/tgidemo.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <cc65.h>
#include <conio.h>
#include <tgi.h>

#include <tgi_utils.h>

#define COLOR_BACK      TGI_COLOR_BLACK
#define COLOR_FORE      TGI_COLOR_WHITE


/*****************************************************************************/
/*                                   Data                                    */
/*****************************************************************************/

/* Driver stuff */
static unsigned MaxX;
static unsigned MaxY;


/*****************************************************************************/
/*                                   Code                                    */
/*****************************************************************************/


static void CheckError (const char* S)
{
  unsigned char Error = tgi_geterror ();

  if (Error != TGI_ERR_OK) {
    printf ("%s: %u\n", S, Error);
    if (doesclrscrafterexit ()) {
      cgetc ();
    }
    exit (EXIT_FAILURE);
  }
}


static void DoDiagram (void)
{
  static const unsigned char Palette[2] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };
  int XOrigin, YOrigin;
  int Amp;
  int X, Y;
  unsigned I;

  tgi_setpalette (Palette);
  tgi_setcolor (COLOR_FORE);
  tgi_clear ();

  /* Determine zero and amplitude */
  YOrigin = MaxY / 2;
  XOrigin = 10;
  Amp     = (MaxY - 19) / 2;

  /* Y axis */
  tgi_line (XOrigin, 10, XOrigin, MaxY-10);
  tgi_line (XOrigin-2, 12, XOrigin, 10);
  tgi_lineto (XOrigin+2, 12);

  /* X axis */
  tgi_line (XOrigin, YOrigin, MaxX-10, YOrigin);
  tgi_line (MaxX-12, YOrigin-2, MaxX-10, YOrigin);
  tgi_lineto (MaxX-12, YOrigin+2);

  /* Sine */
  tgi_gotoxy (XOrigin, YOrigin);
  for (I = 0; I <= 360; I += 5) {

    /* Calculate the next points */
    X = (int) (((long) (MaxX - 19) * I) / 360);
    Y = (int) (((long) Amp * -_sin (I)) / 256);

    /* Draw the line */
    tgi_lineto (XOrigin + X, YOrigin + Y);
  }

  mg_export ("image.mg",
             COLOR_BLUE,   /* foreground */
             COLOR_WHITE,  /* background */
             COLOR_CYAN);  /* border */

  cgetc ();
}


int main (void)
{
  /* Install the driver */
  tgi_install (tgi_static_stddrv);
  CheckError ("tgi_install");

  tgi_init ();
  CheckError ("tgi_init");

  /* Get stuff from the driver */
  MaxX = tgi_getmaxx ();
  MaxY = tgi_getmaxy ();

  /* Set the palette, set the border color */
  bordercolor (COLOR_BLACK);

  /* Do graphics stuff */
  DoDiagram ();

  /* Uninstall the driver */
  tgi_uninstall ();

  return EXIT_SUCCESS;
}
