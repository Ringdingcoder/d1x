//prototypes opengl functions - Added 9/15/99 Matthew Mueller
#ifndef _OGL_INIT_H_ 
#define _OGL_INIT_H_

#ifdef __WINDOWS__
#include "winhdr.h"
#include <stddef.h>
#endif

//#ifdef __WINDOWS__
//#define OGL_RUNTIME_LOAD
//#endif

#ifdef OGL_RUNTIME_LOAD
#include "loadgl.h"
int ogl_init_load_library(void);
#else
#include <GL/gl.h>
#endif

#ifndef GL_VERSION_1_1
#ifdef GL_EXT_texture
#define GL_INTENSITY4 GL_INTENSITY4_EXT
#define GL_INTENSITY8 GL_INTENSITY8_EXT
#endif
#endif


#include "gr.h"
#include "palette.h"
#include "types.h"


#define OGL_TEXTURE_LIST_SIZE 2000

typedef struct _ogl_texture {
	int handle;
	GLint internalformat;
	GLenum format;
	int w,h,tw,th,lw;
	int bytesu;
	int bytes;
	GLfloat u,v;
	GLfloat prio;
	int wrapstate[2];
	fix lastrend;
	ulong numrend;
	char wantmip;
} ogl_texture;

extern ogl_texture ogl_texture_list[OGL_TEXTURE_LIST_SIZE];

extern int ogl_mem_target;
ogl_texture* ogl_get_free_texture(void);
void ogl_init_texture(ogl_texture* t);
void ogl_init_texture_list_internal(void);
void ogl_smash_texture_list_internal(void);
void ogl_vivify_texture_list_internal(void);

extern int ogl_brightness_ok;
extern int ogl_brightness_r, ogl_brightness_g, ogl_brightness_b;
int ogl_setbrightness_internal(void);
extern int ogl_fullscreen;
void ogl_do_fullscreen_internal(void);

extern int ogl_voodoohack;

extern int ogl_alttexmerge;//merge textures by just printing the seperate textures?
extern int ogl_rgba_format;
extern int ogl_setgammaramp_ok;
extern int ogl_intensity4_ok;
extern int ogl_luminance4_alpha4_ok;
extern int ogl_rgba2_ok;
extern int ogl_readpixels_ok;
extern int ogl_gettexlevelparam_ok;
#ifdef GL_ARB_multitexture
extern int ogl_arb_multitexture_ok;
#else
#define ogl_arb_multitexture_ok 0
#endif
#ifdef GL_SGIS_multitexture
extern int ogl_sgis_multitexture_ok;
#else
#define ogl_sgis_multitexture_ok 0
#endif

#ifndef EXT_texture_env_combine
#define EXT_texture_env_combine 1
#define GL_COMBINE_RGB_EXT                0x8571
#define GL_COMBINE_ALPHA_EXT              0x8572
#define GL_PRIMARY_COLOR_EXT              0x8577
#define GL_PREVIOUS_EXT                   0x8578
#define GL_SOURCE0_RGB_EXT                0x8580
#define GL_SOURCE1_RGB_EXT                0x8581
#define GL_SOURCE2_RGB_EXT                0x8582
#define GL_SOURCE0_ALPHA_EXT              0x8588
#define GL_SOURCE1_ALPHA_EXT              0x8589
#define GL_SOURCE2_ALPHA_EXT              0x858A
#define GL_OPERAND0_RGB_EXT               0x8590
#define GL_OPERAND1_RGB_EXT               0x8591
#define GL_OPERAND2_RGB_EXT               0x8592
#define GL_OPERAND0_ALPHA_EXT             0x8598
#define GL_OPERAND1_ALPHA_EXT             0x8599
#define GL_OPERAND2_ALPHA_EXT             0x859A
#endif

#ifndef GL_NV_texture_env_combine4
#define GL_NV_texture_env_combine4 1
#define GL_COMBINE4_NV                    0x8503
#define GL_SOURCE3_RGB_NV                 0x8583
#define GL_SOURCE3_ALPHA_NV               0x858B
#define GL_OPERAND3_RGB_NV                0x8593
#define GL_OPERAND3_ALPHA_NV              0x859B
#endif
extern int ogl_nv_texture_env_combine4_ok;

#ifndef GL_EXT_texture_filter_anisotropic
#define GL_EXT_texture_filter_anisotropic 1
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif
extern int ogl_ext_texture_filter_anisotropic_ok;

extern int gl_initialized;
extern int GL_texmagfilt,GL_texminfilt,GL_needmipmaps;
extern float GL_texanisofilt;
extern int gl_reticle;

extern int active_texture_unit;
void ogl_setActiveTexture(int t);
extern int GL_TEXTURE_2D_enabled;
//extern int GL_texclamp_enabled;
//extern int GL_TEXTURE_ENV_MODE_state,GL_TEXTURE_MAG_FILTER_state,GL_TEXTURE_MIN_FILTER_state;
#define OGL_ENABLE2(a,f) {if (a ## _enabled!=1) {f;a ## _enabled=1;}}
#define OGL_DISABLE2(a,f) {if (a ## _enabled!=0) {f;a ## _enabled=0;}}

//#define OGL_ENABLE(a) OGL_ENABLE2(a,glEnable(a))
//#define OGL_DISABLE(a) OGL_DISABLE2(a,glDisable(a))
#define OGL_ENABLE(a) OGL_ENABLE2(GL_ ## a,glEnable(GL_ ## a))
#define OGL_DISABLE(a) OGL_DISABLE2(GL_ ## a,glDisable(GL_ ## a))

//#define OGL_TEXCLAMP() OGL_ENABLE2(GL_texclamp,glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);)
//#define OGL_TEXREPEAT() OGL_DISABLE2(GL_texclamp,glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)

//#define OGL_SETSTATE(a,s,f) {if (a ## _state!=s) {f;a ## _state=s;}}

//#define OGL_TEXENV(p,m) OGL_SETSTATE(p,m,glTexEnvi(GL_TEXTURE_ENV, p,m));
//#define OGL_TEXPARAM(p,m) OGL_SETSTATE(p,m,glTexParameteri(GL_TEXTURE_2D,p,m));

extern int last_width,last_height;
#define OGL_VIEWPORT(x,y,w,h){if (w!=last_width || h!=last_height){glViewport(x,grd_curscreen->sc_canvas.cv_bitmap.bm_h-y-h,w,h);last_width=w;last_height=h;}}

//platform specific funcs
//MSVC seems to have problems with inline funcs not being found during linking
#ifndef _MSC_VER
inline 
#endif
void ogl_swap_buffers_internal(void);
int ogl_init_window(int x, int y);//create a window/switch modes/etc
void ogl_destroy_window(void);//destroy window/etc
void ogl_init(void);//one time initialization
void ogl_close(void);//one time shutdown

//generic funcs
//#define OGLTEXBUFSIZE (1024*1024*4)
#define OGLTEXBUFSIZE (2048*2048*4)
extern GLubyte texbuf[OGLTEXBUFSIZE];
//void ogl_filltexbuf(unsigned char *data,GLubyte *texp,int width,int height,int twidth,int theight);
void ogl_filltexbuf(unsigned char *data,GLubyte *texp,int truewidth,int width,int height,int dxo,int dyo,int twidth,int theight,int type);
void ogl_loadbmtexture_m(grs_bitmap *bm,int domipmap);
void ogl_loadbmtexture(grs_bitmap *bm);
//void ogl_loadtexture(unsigned char * data, int width, int height,int dxo,int dyo, int *texid,float *u,float *v,char domipmap,float prio);
void ogl_loadtexture(unsigned char * data, int dxo,int dyo, ogl_texture *tex);
void ogl_freetexture(ogl_texture *gltexture);
void ogl_freebmtexture(grs_bitmap *bm);
void ogl_do_palfx(void);
void ogl_start_offscreen_render(int x, int y, int w, int h);
void ogl_end_offscreen_render(void);
void ogl_start_frame(void);
void ogl_end_frame(void);
void ogl_swap_buffers(void);
void ogl_set_screen_mode(void);
void ogl_cache_level_textures(void);

void ogl_urect(int left,int top,int right,int bot);
bool ogl_ubitmapm_c(int x, int y,grs_bitmap *bm,int c);
bool ogl_ubitmapm(int x, int y,grs_bitmap *bm);
bool ogl_ubitblt_i(int dw,int dh,int dx,int dy, int sw, int sh, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);
bool ogl_ubitblt(int w,int h,int dx,int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);
bool ogl_ubitblt_tolinear(int w,int h,int dx,int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);
bool ogl_ubitblt_copy(int w,int h,int dx,int dy, int sx, int sy, grs_bitmap * src, grs_bitmap * dest);
void ogl_upixelc(int x, int y, int c);
void ogl_ulinec(int left,int top,int right,int bot,int c);

extern unsigned char *ogl_pal;

#include "3d.h"
bool g3_draw_tmap_2(int nv,g3s_point **pointlist,g3s_uvl *uvl_list,grs_bitmap *bmbot,grs_bitmap *bm,int orient);

void ogl_draw_reticle(int cross,int primary,int secondary);

//whee
//#define PAL2Tr(c) ((gr_palette[c*3]+gr_palette_gamma)/63.0)
//#define PAL2Tg(c) ((gr_palette[c*3+1]+gr_palette_gamma)/63.0)
//#define PAL2Tb(c) ((gr_palette[c*3+2]+gr_palette_gamma)/63.0)
//#define PAL2Tr(c) ((gr_palette[c*3])/63.0)
//#define PAL2Tg(c) ((gr_palette[c*3+1])/63.0)
//#define PAL2Tb(c) ((gr_palette[c*3+2])/63.0)
#define CPAL2Tr(c) ((gr_current_pal[c*3])/63.0)
#define CPAL2Tg(c) ((gr_current_pal[c*3+1])/63.0)
#define CPAL2Tb(c) ((gr_current_pal[c*3+2])/63.0)
#define PAL2Tr(c) ((ogl_pal[c*3])/63.0)
#define PAL2Tg(c) ((ogl_pal[c*3+1])/63.0)
#define PAL2Tb(c) ((ogl_pal[c*3+2])/63.0)
//inline GLfloat PAL2Tr(int c);
//inline GLfloat PAL2Tg(int c);
//inline GLfloat PAL2Tb(int c);

#endif
