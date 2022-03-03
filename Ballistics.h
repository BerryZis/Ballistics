/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: Exitq */
#define  PANEL_GRAPH                      2       /* control type: graph, callback function: Cursor */
#define  PANEL_YAXIS                      3       /* control type: numeric, callback function: (none) */
#define  PANEL_XAXIS                      4       /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTMSG                    5       /* control type: textMsg, callback function: (none) */
#define  PANEL_FIRE                       6       /* control type: textButton, callback function: Fire */
#define  PANEL_ANGLE                      7       /* control type: numeric, callback function: (none) */
#define  PANEL_SPEED                      8       /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTMSG_2                  9       /* control type: textMsg, callback function: (none) */
#define  PANEL_INTERVAL                   10      /* control type: numeric, callback function: (none) */
#define  PANEL_RESET                      11      /* control type: command, callback function: resetall */
#define  PANEL_TIMER                      12      /* control type: timer, callback function: Time */
#define  PANEL_TEXTMSG_3                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  14      /* control type: textMsg, callback function: (none) */
#define  PANEL_LOAD                       15      /* control type: command, callback function: Load */
#define  PANEL_COLORNUM                   16      /* control type: color, callback function: (none) */
#define  PANEL_PICTURE_2                  17      /* control type: picture, callback function: (none) */
#define  PANEL_DECORATION                 18      /* control type: deco, callback function: (none) */
#define  PANEL_PICTURE                    19      /* control type: picture, callback function: About */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK About(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cursor(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Exitq(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resetall(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
