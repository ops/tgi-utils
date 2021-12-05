/*
 * import.c
 *
 * Import MINIGRAFIK image as TGI image.
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


static void ImportImage (void)
{
  static const unsigned char Palette[2] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };

  tgi_setpalette (Palette);
  tgi_setcolor (COLOR_FORE);
  tgi_clear ();

  mg_import ("image.mg");

  cgetc ();
}


int main (void)
{
  /* Install the driver */
  tgi_install (tgi_static_stddrv);
  CheckError ("tgi_install");

  tgi_init ();
  CheckError ("tgi_init");

  /* Set the border color */
  bordercolor (COLOR_BLACK);

  /* Do graphics stuff */
  ImportImage ();

  /* Uninstall the driver */
  tgi_uninstall ();

  return EXIT_SUCCESS;
}
