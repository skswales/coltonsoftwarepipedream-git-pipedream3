/****************************************************************************
 * This source file was written by Acorn Computers Limited. It is part of   *
 * the RISCOS library for rendering RISCOS Draw files from applications     *
 * in C. It may be used freely in the creation of programs for Archimedes.  *
 * It should be used with Acorn's C Compiler Release 3 or later.            *
 *                                                                          *
 ***************************************************************************/

/*
 * Title:    drawtypes.h
 * Purpose:  Defines types used by the object level interface for draw files
 *
 */


/*
 * The types defined here are used for detailed access to objects.
 * This will not normally be #included by a client of  the DrawFile modules
 * - it gets pulled in by h.drawfobj.
 */

#ifndef __drawftypes_h
#define __drawftypes_h

#ifndef __os_h
#include "os.h"
#endif
#ifndef __sprite_h
#include "sprite.h"
#endif
#ifndef __drawfdiag_h
#include "drawfdiag.h"
#endif

typedef int draw_sizetyp;
typedef int draw_coltyp;
typedef int draw_pathwidth;   /* 1 word */
typedef draw_box draw_bboxtyp;


/* Types of join */

typedef enum
{ join_mitred   = 0,
  join_round    = 1,
  join_bevelled = 2
} draw_jointyp;


/* Types of cap specification */

typedef enum
{ cap_butt     = 0,
  cap_round    = 1,
  cap_square   = 2,
  cap_triangle = 3
} draw_captyp;


/* Types of winding rule */

typedef enum
{ wind_nonzero = 0,
  wind_evenodd = 1
} draw_windtyp;


/* Dash types */

typedef enum
{ dash_absent  = 0,
  dash_present = 1
} draw_dashtyp;


/* Values used for pack/unpack of draw data */

#define packmask_join     0x03
#define packmask_endcap   0x0C
#define packmask_startcap 0x30
#define packmask_windrule 0x40
#define packmask_dashed   0x80
#define packshft_join        0
#define packshft_endcap      2
#define packshft_startcap    4
#define packshft_windrule    6
#define packshft_dashed      7


/* A Path style */

typedef struct
{ unsigned char joincapwind;       /* 1 byte  */ /* bit 0..1 join         */
                                                 /* bit 2..3 end cap      */
                                                 /* bit 4..5 start cap    */
                                                 /* bit 6    winding rule */
                                                 /* bit 7    dashed       */
  unsigned char reserved8;         /* 1 byte  */
  unsigned char tricapwid;         /* 1 byte  */ /* 1/16th of line width */
  unsigned char tricaphei;         /* 1 byte  */ /* 1/16th of line width */
} draw_pathstyle;


typedef char draw_fontref;    /* 1 byte */


/* Text style */

typedef struct
{ draw_fontref fontref;             /* 1 byte  */
  char         reserved8;           /* 1 byte  */
  short        reserved16;          /* 2 bytes */
} draw_textstyle;   /* 1 word */


typedef unsigned int draw_fontsize;  /* 4 bytes, unsigned */


typedef struct
{ int typeface;     /* index into fontname table */
  int typesizex;
  int typesizey;
  draw_coltyp textcolour;    /* text colour RGB */
  draw_coltyp background;    /* hint for anti-aliased printing RGB */
} fontrec;


typedef enum
{ draw_OBJFONTLIST = 0,
  draw_OBJTEXT     = 1,
  draw_OBJPATH     = 2,
  draw_OBJSPRITE  = 5,
  draw_OBJGROUP   = 6,
  draw_OBJTEXTAREA = 9,
  draw_OBJTEXTCOL  = 10
} draw_tagtyp;

typedef struct { int x,y; } draw_objcoord;

/* -------------------------------------------------------------------------  *
 *
 * File header
 *
 *
 */                                                               

typedef struct
{ char title[4];
  int  majorstamp;
  int  minorstamp;
  char progident[12];
  draw_bboxtyp   bbox;      /* 4 words */
} draw_fileheader;


/* -------------------------------------------------------------------------  *
 * General header for graphic objects
 *
 */   

typedef struct
{ draw_tagtyp    tag;       /* 1 word  */
  draw_sizetyp   size;      /* 1 word  */
  draw_bboxtyp   bbox;      /* 4 words */
} draw_objhdr;


/* -------------------------------------------------------------------------
 *
 * A font list 
 *
 *
 */

typedef struct
{ draw_tagtyp    tag;       /* 1 word  */
  draw_sizetyp   size;      /* 1 word  */
} draw_fontliststrhdr;

typedef struct
{ draw_tagtyp    tag;       /* 1 word  */
  draw_sizetyp   size;      /* 1 word  */

  draw_fontref   fontref;       /*  check size        */
  char           fontname[1];   /* String, null terminated */
} draw_fontliststr;


/* ------------------------------------------------------------------------- 
 *
 *
 * A line of text                                                             *
 *
 */

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  draw_coltyp    textcolour; /* 1 word  */
  draw_coltyp    background; /* 1 word  */
  draw_textstyle textstyle;  /* 1 word  */
  draw_fontsize  fsizex;     /* 1 word, unsigned */
  draw_fontsize  fsizey;     /* 1 word, unsigned */
  draw_objcoord  coord;      /* 2 words */
} draw_textstrhdr;

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  draw_coltyp    textcolour; /* 1 word  */
  draw_coltyp    background; /* 1 word  */
  draw_textstyle textstyle;  /* 1 word  */
  draw_fontsize  fsizex;     /* 1 word, unsigned */
  draw_fontsize  fsizey;     /* 1 word, unsigned */
  draw_objcoord  coord;      /* 2 words */

  char           text[1];   /* String, null terminated */
} draw_textstr;


/* -------------------------------------------------------------------------  *
 *
 * Elements within a path                                                     *
 *
 */

typedef enum
 { draw_PathTERM  = 0,     /* end of path                                   */
   draw_PathMOVE  = 2,     /* move to (x,y), starts new subpath             */
   draw_PathLINE  = 8,     /* line to (x,y)                                 */
   draw_PathCURVE = 6,     /* bezier curve to (x3,y3) with 2 control points */
   draw_PathCLOSE = 5      /* close current subpath with a line             */
} draw_path_tagtype;

typedef struct { draw_path_tagtype tag; int x,y; } Path_movestr;

typedef struct { draw_path_tagtype tag; int x,y; } Path_linestr;

typedef struct { draw_path_tagtype tag; int x1,y1;
                                        int x2,y2; int x3,y3; } Path_curvestr;

typedef struct { draw_path_tagtype tag; } Path_closestr;

typedef struct { draw_path_tagtype tag; } Path_termstr;

typedef union           /* Use ONLY for space checking purposes */
{ Path_movestr a;Path_linestr b;Path_curvestr c;Path_closestr d;Path_termstr e;
} Largest_path_str;


typedef union
{ Path_movestr  *move;
  Path_linestr  *line;
  Path_curvestr *curve;
  Path_closestr *close;
  Path_termstr  *term;

  char *bytep;
  int  *wordp;
} Path_eleptr;


/* -------------------------------------------------------------------------  *
 *
 * Optional dashpattern                                                       *
 *
 */


typedef struct
{ int dashstart;       /* 1 word */           /* distance into pattern */
  int dashcount;       /* 1 word */           /* number of elements    */
} draw_dashstrhdr;

typedef struct
{ int dashstart;       /* 1 word */           /* distance into pattern */
  int dashcount;       /* 1 word */           /* number of elements    */
  int dashelements[6]; /* dashcount words */  /* elements of pattern   */
} draw_dashstr;


/* -------------------------------------------------------------------------  *
 *
 * Unpacked joint,start cap,end cap structure - as fed to drawmod_stroke etc  *
 *
 */

typedef struct
{ char join;
  char endcap;
  char startcap;
  char reserved;  /* must be zero */
  int  mitrelimit;
  short endtricapwid;
  short endtricaphei;
  short starttricapwid;
  short starttricaphei;
} draw_jointspec;


/* -------------------------------------------------------------------------  *
 *
 * A path
 *
 */                                                                    

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  draw_coltyp    fillcolour; /* 1 word  */
  draw_coltyp    pathcolour; /* 1 word  */
  draw_pathwidth pathwidth;  /* 1 word  */
  draw_pathstyle pathstyle;  /* 1 word  */
} draw_pathstrhdr;

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  draw_coltyp    fillcolour; /* 1 word  */
  draw_coltyp    pathcolour; /* 1 word  */
  draw_pathwidth pathwidth;  /* 1 word  */
  draw_pathstyle pathstyle;  /* 1 word  */

  draw_dashstr data;      /* optional dash pattern, then path elements */
 int PATH;
} draw_pathstr;


/* -------------------------------------------------------------------------
 *
 *
 * A sprite
 *
 */                                                                  

typedef struct
{ draw_tagtyp    tag;       /* 1 word  */  
  draw_sizetyp   size;      /* 1 word  */   
  draw_bboxtyp   bbox;      /* 4 words */ 
} draw_spristrhdr;

typedef struct
{ draw_tagtyp    tag;       /* 1 word  */
  draw_sizetyp   size;      /* 1 word  */
  draw_bboxtyp   bbox;      /* 4 words */
  sprite_header  sprite;
  int            palette[1]; /* depends on sprite.mode (or not present) */
} draw_spristr;


/* -------------------------------------------------------------------------  *
 *
 * A grouping                                                                 *
 */

typedef struct { char ch[12]; } draw_groupnametyp;  /* 12 bytes */

typedef struct
{ draw_tagtyp       tag;   /* 1 word   */
  draw_sizetyp      size;  /* 1 word   */
  draw_bboxtyp      bbox;  /* 4 words  */
  draw_groupnametyp name;  /* 12 bytes */
} draw_groustr;                             


/* -------------------------------------------------------------------------  *
 *
 * A text column                                                              * These only appear nested within a text area.
 *
 */

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
} draw_textcolhdr;


/* -------------------------------------------------------------------------  *
 *
 * A text area object
 *
 *
 */

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  draw_textcolhdr column;    /* Hook for pointing to text columns */
} draw_textareastrhdr;

typedef struct
{ draw_tagtyp    tag;        /* 1 word  */
  draw_sizetyp   size;       /* 1 word  */
  draw_bboxtyp   bbox;       /* 4 words */
  /* Text columns go in here */
} draw_textareahdr;

/* End structure - follows all the column */
typedef struct               /* Structure for getting size */
{
  int            endmark;    /* 1 word, always 0 */
  int            blank1;     /* 1 word, reserved for future expansion */
  int            blank2;     /* 1 word, reserved for future expansion */
  draw_coltyp    textcolour; /* 1 word */
  draw_coltyp    backcolour; /* 1 word */
  /* String goes in here */
} draw_textareastrend;

typedef struct
{
  int            endmark;    /* 1 word, always 0 */
  int            blank1;     /* 1 word, reserved for future expansion */
  int            blank2;     /* 1 word, reserved for future expansion */
  draw_coltyp    textcolour; /* 1 word */
  draw_coltyp    backcolour; /* 1 word */
  char           text[1];    /* String, null terminated */
} draw_textareaend;

#endif

/* end of drawtypes.h */

