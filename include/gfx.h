#ifndef __GFX_H__
#define __GFX_H__

// ------------------------------------------------------------------------
// extra gfx functions.
// ------------------------------------------------------------------------
void gfx_draw_line(int x1, int y1, int x2, int y2, unsigned short int color);
void gfx_draw_circle(unsigned short int x, unsigned short int y, unsigned short int r, unsigned short int color);

// ------------------------------------------------------------------------
// preset color values
// ------------------------------------------------------------------------
/*
#define gfx_color_white   gfx_color_make(0xFF, 0xFF, 0xFF)
#define gfx_color_silver  gfx_color_make(0xC0, 0xC0, 0xC0)
#define gfx_color_gray    gfx_color_make(0x80, 0x80, 0x80)
#define gfx_color_black   gfx_color_make(0x00, 0x00, 0x00)
#define gfx_color_red     gfx_color_make(0xFF, 0x00, 0x00)
#define gfx_color_maroon  gfx_color_make(0x80, 0x00, 0x00)
#define gfx_color_yellow  gfx_color_make(0xFF, 0xFF, 0x00)
#define gfx_color_olive   gfx_color_make(0x80, 0x80, 0x00)
#define gfx_color_lime    gfx_color_make(0x00, 0xFF, 0x00)
#define gfx_color_green   gfx_color_make(0x00, 0x80, 0x00)
#define gfx_color_cyan    gfx_color_make(0x00, 0xFF, 0xFF)
#define gfx_color_aqua    gfx_color_cyan
#define gfx_color_teal    gfx_color_make(0x00, 0x80, 0x80)
#define gfx_color_blue    gfx_color_make(0x00, 0x00, 0xFF)
#define gfx_color_navy    gfx_color_make(0x00, 0x00, 0x80)
#define gfx_color_magenta gfx_color_make(0xFF, 0x00, 0xFF)
#define gfx_color_purple  gfx_color_make(0x80, 0x00, 0x80)
#define gfx_color_orange  gfx_color_make(0xFF, 0xA5, 0x00)

#define gfx_color_transp  gfx_color_make(0xFB, 0xE6, 0x1D) // pixels with this color will not be drawn
*/

#endif