/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once

#include <cstdint>
#define FN_USE_DOUBLES
#include "fastnoise.h"

/**
 * Bits and bobs that need to be available everywhere. 
 * 
*/
#ifdef _WIN32
#include "resource.h"
#endif



#ifndef GLuint
typedef unsigned int GLuint;
#endif

#ifndef GLRef
typedef unsigned int GLRef;
#endif

#ifndef GLenum
	typedef unsigned int GLenum;
#endif

#include "sl_maths.h"

#define argb(a,r,g,b) ( ((uint32)(a)<<24) |		\
			((((uint32)r)<<24)>>8) |	\
			((((uint32)g)<<24)>>16) |	\
			((((uint32)b)<<24)>>24))

#define rgb(r,g,b) argb(255,(r),(g),(b))
#define argb_f(a,r,g,b) argb((uint8)((a)*255.0f),(uint8)((r)*255.0f),(uint8)((g)*255.0f),(uint8)((b)*255.0f))
#define rgb_f(r,g,b) argb_f(1.0f,(r),(g),(b))
#define geta(p) ((uint32)((p))>>24)
#define getr(p) (((uint32)((p))<<8)>>24)
#define getg(p) (((uint32)((p))<<16)>>24)
#define getb(p) (((uint32)((p))<<24)>>24)

#define geta_nf(p) (geta(p)/255.0f)
#define getr_nf(p) (getr(p)/255.0f)
#define getg_nf(p) (getg(p)/255.0f)
#define getb_nf(p) (getb(p)/255.0f)



enum class BlendMode {
	blend_multiply, blend_add, blend_alpha, blend_darken,
	blend_lighten, blend_screen, blend_difference, blend_negation,
	blend_exclusion, blend_overlay, blend_hardlight, blend_softlight,
	blend_colourdodge, blend_inverse_colourdodge, blend_softdodge,
	blend_colourburn, blend_inverse_colourburn, blend_softburn,
	blend_quadratic_reflect, blend_quadratic_glow, blend_quadratic_freeze,
	blend_quadratic_heat, blend_interpolate, blend_rgb_r, blend_rgb_g, blend_rgb_b,
	blend_hue, blend_saturation, blend_colour, blend_luminosity
};

namespace x11colours {
	static constexpr pixel32 antiquewhite = rgb(0xfa, 0xeb, 0xd7);
	static constexpr pixel32 darkslategrey = rgb(0x2f, 0x4f, 0x4f);
	static constexpr pixel32 black = rgb(0, 0, 0);
	static constexpr pixel32 orange = rgb(255, 127, 0);
	static constexpr pixel32 magenta = rgb(255, 0, 255);
	static constexpr pixel32 grey = rgb(150, 150, 150);
	static constexpr pixel32 brightred = rgb(255, 128, 128);
	static constexpr pixel32 brightgreen = rgb(128, 255, 128);
	static constexpr pixel32 brightblue = rgb(128, 128, 255);
	static constexpr pixel32 darkgrey = rgb(64, 64, 64);
	static constexpr pixel32 mediumgrey = rgb(128, 128, 128);
	static constexpr pixel32 brightgrey = rgb(192, 192, 192);
	static constexpr pixel32 navy = rgb(0, 0, 128);
	static constexpr pixel32 royalblue = rgb(65, 105, 225);
	static constexpr pixel32 tomato = rgb(255, 99, 71);
	static constexpr pixel32 navyblue = rgb(0, 0, 0x80);
	static constexpr pixel32 maroon = rgb(0xb0,0x30,0x60);
	static constexpr pixel32 silver = rgb(192, 192, 192);
	static constexpr pixel32 green = rgb(0, 255, 0);
	static constexpr pixel32 white = rgb(255, 255, 255);
	static constexpr pixel32 red = rgb(255, 0, 0);
	static constexpr pixel32 blue = rgb(0, 0, 255);
	static constexpr pixel32 yellow = rgb(255, 255, 0);
	static constexpr pixel32 cyan = rgb(0, 255, 255);
	static constexpr pixel32 darkkhaki = rgb(189, 183, 107);
	static constexpr pixel32 khaki = rgb(240, 230, 140);
	static constexpr pixel32 palegoldenrod = rgb(238, 232, 170);
	static constexpr pixel32 peachpuff = rgb(255, 218, 185);
	static constexpr pixel32 moccasin = rgb(255, 228, 181);
	static constexpr pixel32 papayawhip = rgb(255, 239, 213);
	static constexpr pixel32 lightgoldenrodyellow = rgb(250, 250, 210);
	static constexpr pixel32 lemonchiffon = rgb(255, 250, 205);
	static constexpr pixel32 lightyellow = rgb(255, 255, 224);
	static constexpr pixel32 gold = rgb(255, 215, 0);
	static constexpr pixel32 darkorange = rgb(255, 140, 0);
	static constexpr pixel32 orangered = rgb(255, 69, 0);
	static constexpr pixel32 coral = rgb(255, 127, 80);
	static constexpr pixel32 lightsalmon = rgb(255, 160, 122);
	static constexpr pixel32 palevioletred = rgb(219, 112, 147);
	static constexpr pixel32 mediumvioletred = rgb(199, 21, 133);
	static constexpr pixel32 deeppink = rgb(255, 20, 147);
	static constexpr pixel32 hotpink = rgb(255, 105, 180);
	static constexpr pixel32 lightpink = rgb(255, 182, 193);
	static constexpr pixel32 pink = rgb(255, 192, 203);
	static constexpr pixel32 darkred = rgb(139, 0, 0);
	static constexpr pixel32 firebrick = rgb(178, 34, 34);
	static constexpr pixel32 crimson = rgb(220, 20, 60);
	static constexpr pixel32 lightcoral = rgb(240, 128, 128);
	static constexpr pixel32 indianred = rgb(205, 92, 92);
	static constexpr pixel32 thistle = rgb(219, 191, 216);
	static constexpr pixel32 plum = rgb(221, 160, 221);
	static constexpr pixel32 violet = rgb(238, 130, 238);
	static constexpr pixel32 orchid = rgb(218, 112, 214);
	static constexpr pixel32 fuchsia = rgb(255, 0, 255);
	static constexpr pixel32 mediumorchid = rgb(186, 85, 211);
	static constexpr pixel32 blueviolet = rgb(138, 43, 226);
	static constexpr pixel32 darkviolet = rgb(148, 0, 211);
	static constexpr pixel32 darkorchid = rgb(153, 50, 204);
	static constexpr pixel32 darkmagenta = rgb(139, 0, 139);
	static constexpr pixel32 purple = rgb(128, 0, 128);
	static constexpr pixel32 indigo = rgb(75, 0, 130);
	static constexpr pixel32 slateblue = rgb(106, 90, 205);
	static constexpr pixel32 darkslateblue = rgb(72, 61, 139);
	static constexpr pixel32 mediumslateblue = rgb(123, 104, 238);
	static constexpr pixel32 slategrey = rgb(112, 128, 144);
	static constexpr pixel32 lightslategrey = rgb(119, 136, 153);
	static constexpr pixel32 dimgrey = rgb(105, 105, 05);
	static constexpr pixel32 lightgrey = rgb(211, 211, 211);
	static constexpr pixel32 gainsboro = rgb(220, 220, 220);
	static constexpr pixel32 mistyrose = rgb(255, 228, 225);
	static constexpr pixel32 lavenderbush = rgb(255, 240, 245);
	static constexpr pixel32 linen = rgb(250, 240, 230);
	static constexpr pixel32 ivory = rgb(255, 255, 240);
	static constexpr pixel32 floralwhite = rgb(255, 250, 240);
	static constexpr pixel32 oldlace = rgb(253, 245, 230);
	static constexpr pixel32 beige = rgb(245, 245, 220);
	static constexpr pixel32 seashell = rgb(255, 245, 238);
	static constexpr pixel32 whitesmoke = rgb(245, 245, 245);
	static constexpr pixel32 aliceblue = rgb(240, 248, 255);
	static constexpr pixel32 azure = rgb(240, 255, 255);
	static constexpr pixel32 mintcream = rgb(245, 255, 250);
	static constexpr pixel32 honeydew = rgb(240, 255, 250);
	static constexpr pixel32 snow = rgb(255, 250, 250);
	static constexpr pixel32 brown = rgb(265, 42, 42);
	static constexpr pixel32 sienna = rgb(160, 82, 45);
	static constexpr pixel32 saddlebrown = rgb(139, 69, 19);
	static constexpr pixel32 chocolate = rgb(210, 105, 30);
	static constexpr pixel32 peru = rgb(205, 133, 63);
	static constexpr pixel32 darkgoldenrod = rgb(184, 134, 11);
	static constexpr pixel32 goldenrod = rgb(218, 165, 32);
	static constexpr pixel32 sandybrown = rgb(244, 164, 96);
	static constexpr pixel32 rosybrown = rgb(188, 143, 143);
	static constexpr pixel32 tan = rgb(210, 180, 140);
	static constexpr pixel32 burlywood = rgb(222, 184, 135);
	static constexpr pixel32 wheat = rgb(245, 222, 179);
	static constexpr pixel32 navajowhite = rgb(255, 222, 173);
	static constexpr pixel32 bisque = rgb(255, 228, 196);
	static constexpr pixel32 blanchedalmond = rgb(255, 235, 205);
	static constexpr pixel32 cornsilk = rgb(255, 248, 220);
	static constexpr pixel32 greenyellow = rgb(173, 255, 47);
	static constexpr pixel32 chartreuse = rgb(127, 255, 0);
	static constexpr pixel32 lawngreen = rgb(124, 252, 0);
	static constexpr pixel32 limegreen = rgb(50, 205, 50);
	static constexpr pixel32 palegreen = rgb(152, 251, 152);
	static constexpr pixel32 lightgreen = rgb(144, 238, 144);
	static constexpr pixel32 mediumspringgreen = rgb(0, 250, 154);
	static constexpr pixel32 springgreen = rgb(0, 255, 127);
	static constexpr pixel32 mediumseagreen = rgb(60, 179, 113);
	static constexpr pixel32 seagreen = rgb(46, 139, 87);
	static constexpr pixel32 forestgreen = rgb(34, 139, 24);
	static constexpr pixel32 darkgreen = rgb(0, 100, 0);
	static constexpr pixel32 yellowgreen = rgb(154, 205, 50);
	static constexpr pixel32 olivedrab = rgb(107, 142, 35);
	static constexpr pixel32 darkolivegreen = rgb(85, 107, 47);
	static constexpr pixel32 mediumaquamarine = rgb(102, 205, 170);
	static constexpr pixel32 darkseagreen = rgb(143, 188, 143);
	static constexpr pixel32 lightseagreen = rgb(32, 178, 170);
	static constexpr pixel32 darkcyan = rgb(0, 139, 139);
	static constexpr pixel32 lightcyan = rgb(224, 255, 255);
	static constexpr pixel32 paleturquoise = rgb(175, 238, 238);
	static constexpr pixel32 aquamarine = rgb(127, 255, 212);
	static constexpr pixel32 turquoise = rgb(64, 224, 208);
	static constexpr pixel32 mediumturquoise = rgb(72, 209, 204);
	static constexpr pixel32 darkturquoise = rgb(0, 206, 209);
	static constexpr pixel32 cadetblue = rgb(95, 158, 160);
	static constexpr pixel32 steelblue = rgb(70, 130, 180);
	static constexpr pixel32 lightsteelblue = rgb(176, 196, 222);
	static constexpr pixel32 powderblue = rgb(176, 224, 230);
	static constexpr pixel32 lightblue = rgb(173, 216, 230);
	static constexpr pixel32 skyblue = rgb(135, 206, 235);
	static constexpr pixel32 lightskyblue = rgb(135, 206, 250);
	static constexpr pixel32 deepskyblue = rgb(0, 191, 255);
	static constexpr pixel32 dodgerblue = rgb(30, 144, 255);
	static constexpr pixel32 cornflowerblue = rgb(100, 149, 237);
	static constexpr pixel32 mediumblue = rgb(0, 0, 205);
	static constexpr pixel32 darkblue = rgb(0, 0, 139);
	static constexpr pixel32 midnightblue = rgb(25, 25, 112);
	static constexpr pixel32 teal = rgb(0, 128, 128);
}

namespace htmlcolours {
	static constexpr pixel32 aqua = rgb(0x00, 0xff, 0xff);
	static constexpr pixel32 grey = rgb(0x80, 0x80, 0x80);
	static constexpr pixel32 navy = rgb(0x00, 0x00, 0x80);
	static constexpr pixel32 silver = rgb(0xc0, 0xc0, 0xc0);
	static constexpr pixel32 black = rgb(0x00, 0x00, 0x00);
	static constexpr pixel32 green = rgb(0x00, 0x80, 0x00);
	static constexpr pixel32 olive = rgb(0x80, 0x80, 0x00);
	static constexpr pixel32 teal = rgb(0x00, 0x80, 0x80);
	static constexpr pixel32 blue = rgb(0x00, 0x00, 0xff);
	static constexpr pixel32 lime = rgb(0x00, 0xff, 0x00);
	static constexpr pixel32 purple = rgb(0x80, 0x00, 0x80);
	static constexpr pixel32 white = rgb(0xff, 0xff, 0xff);
	static constexpr pixel32 fuchsia = rgb(0xff, 0x00, 0xff);
	static constexpr pixel32 maroon = rgb(0x80, 0x00, 0x00);
	static constexpr pixel32 red = rgb(0xff, 0x00, 0x00);
	static constexpr pixel32 yellow = rgb(0xff, 0xff, 0x00);
}

namespace naturalcolours {
	static constexpr pixel32 airforceblue = rgb(0x5d, 0x8a, 0xa8);
	static constexpr pixel32 aliceblue = rgb(0xf0, 0xf8, 0xff);
	static constexpr pixel32 alizarin = rgb(0xe3, 0x26, 0x36);
	static constexpr pixel32 amaranth = rgb(0xe5, 0x2b, 0x50);

	static constexpr pixel32 amaranthpink = rgb(0xf1, 0x9c, 0xbb);
	static constexpr pixel32 amber = rgb(0xff, 0xbf, 0x00);
	static constexpr pixel32 ambersae = rgb(0xff, 0x7e, 0x00);
	static constexpr pixel32 amethyst = rgb(0x99, 0x66, 0xcc);
	static constexpr pixel32 apricot = rgb(0xfb, 0xce, 0xb1);
	static constexpr pixel32 aqua = rgb(0x00f, 0xff, 0xff);
	static constexpr pixel32 aquamarine = rgb(0x7f, 0xff, 0xd4);

	static constexpr pixel32 armygreen = rgb(0x4b, 0x53, 0x20);
	static constexpr pixel32 arsenic = rgb(0x3b, 0x44, 0x4b);
	static constexpr pixel32 asparagus = rgb(0x7b, 0xa0, 0x5b);
	static constexpr pixel32 atomictangerine = rgb(0xff, 0x99, 0x66);
	static constexpr pixel32 auburn = rgb(0x6d, 0x35, 0x1a);
	static constexpr pixel32 azurecwheel = rgb(0x007, 0xff, 0xff);

	static constexpr pixel32 azureweb = rgb(0xf0, 0xff, 0xff);
	static constexpr pixel32 babyblue = rgb(0xe0, 0xff, 0xff);
	static constexpr pixel32 beige = rgb(0xf5, 0xf5, 0xdc);
	static constexpr pixel32 bistre = rgb(0x3d, 0x2b, 0x1f);
	static constexpr pixel32 black = rgb(0x00, 0x00, 0x00);
	static constexpr pixel32 blue = rgb(0x00, 0x00, 0xff);
	static constexpr pixel32 bluepigment = rgb(0x33, 0x33, 0x99);
	static constexpr pixel32 blueryb = rgb(0x02, 0x47, 0xfe);

	static constexpr pixel32 bluegreen = rgb(0x00, 0xdd, 0xdd);
	static constexpr pixel32 blueviolet = rgb(0x8a, 0x2b, 0xe2);
	static constexpr pixel32 bole = rgb(0x79, 0x44, 0x3b);
	static constexpr pixel32 bondiblue = rgb(0x00, 0x95, 0xb6);
	static constexpr pixel32 brandeisblue = rgb(0x00, 0x70, 0xff);
	static constexpr pixel32 brass = rgb(0xb5, 0xa6, 0x42);

	static constexpr pixel32 brightgreen = rgb(0x66, 0xff, 0x00);
	static constexpr pixel32 brightpink = rgb(0xff, 0x00, 0x7f);
	static constexpr pixel32 britishracinggreen = rgb(0x00, 0x42, 0x25);
	static constexpr pixel32 bronze = rgb(0xcd, 0x7f, 0x32);
	static constexpr pixel32 brown = rgb(0x96, 0x4b, 0x00);
	static constexpr pixel32 buff = rgb(0xf0, 0xdc, 0x82);

	static constexpr pixel32 burgundy = rgb(0x80, 0x00, 0x20);
	static constexpr pixel32 burntorange = rgb(0xcc, 0x55, 0x00);
	static constexpr pixel32 burntsienna = rgb(0xe9, 0x74, 0x51);
	static constexpr pixel32 burntumber = rgb(0x8a, 0x33, 0x24);
	static constexpr pixel32 byzantium = rgb(0x70, 0x29, 0x63);


	static constexpr pixel32 cambridgeblue = rgb(0x99, 0xcc, 0xcc);
	static constexpr pixel32 camouflagegreen = rgb(0x78, 0x86, 0x6b);
	static constexpr pixel32 caputmortuum = rgb(0x59, 0x27, 0x20);

	static constexpr pixel32 cardinal = rgb(0xc4, 0x1e, 0x3a);
	static constexpr pixel32 carmine = rgb(0x96, 0x00, 0x18);
	static constexpr pixel32 carminepink = rgb(0xeb, 0x4c, 0x42);
}

struct ARGB3 {
	ARGB3(){}
	ARGB3(pixel32 colour0,pixel32 colour1, pixel32 colour2)
	{
		colours[0]=colour0;
		colours[1]=colour1;
		colours[2]=colour2;
	}
	~ARGB3(){}
	pixel32 colours[3]{x11colours::red,x11colours::green,x11colours::blue};
};



struct SLContext;
class SLTexture;
class SLPrimitiveBuffer;
class SLShader;

extern "C" {
void sl_load_gl_extensions();
}

int32 sl_create_context(SLContext **context,const char *titletext,int32 width,int32 height,bool fullscreen);
int32 sl_destroy_context(SLContext **context);
bool sl_want_to_quit(SLContext *context);
void sl_quit(SLContext *context);
void sl_swap(SLContext *context);
void sl_poll_input(SLContext *context);
void sl_process_input(SLContext *context);

int main_audio();
int main_networking();

void render_gui();
void update_gui();
void init_gui(SLContext *context);

int32 string_split_c(const char *txt, char delim, char ***tokens);
char *load_text_file(const char *filename, int32 &num_bytes_read);

