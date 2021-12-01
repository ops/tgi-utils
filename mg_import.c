/*
 *  mg_import.c
 *
 *  November 2021 ops
 */

#include "tgi_utils.h"

#include <stdio.h>

int mg_import(const char *name)
{
  FILE *f;

  f = fopen(name, "rb");
  if(f == 0)
    return -1;

  /* Skip BASIC stub and color settings*/
  fread((void *)0x1100, 1, 17, f);

  /* Read MG image bitmap data */
  fread((void *)0x1100, 1, 3840, f);

  fclose(f);

  return 0;
}
