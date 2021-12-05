/*
 * tgi_utils.h
 *
 * 2021 ops
 *
 */

#ifndef _TGI_UTILS_H
#define _TGI_UTILS_H

#include <stdint.h>

/* Export VIC-20 TGI picture in MINIGRAFIK format */
int mg_export(const char *name,
              uint8_t foreground,
              uint8_t background,
              uint8_t border);

/* Import VIC-20 MINIGRAFIK picture */
int mg_import(const char *name);

#endif
