#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Ballistics.h"

static int panelHandle;
double angle,speed,rangle;
double x=0.0,y=0.0;
double dt=0.0,g=9.81;
double vx,vy;
int select,load,flag=0,flag2=0;
char graphsData[500],line[100];
FILE *fp; 

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Ballistics.uir", PANEL)) < 0)
		return -1;
	RecallPanelState (panelHandle, "panelData", 0); //Recall last panel state
	DisplayPanel (panelHandle);
	MessagePopup ("Created By Berz.", "Welcome to a Ballistics simulator\n\n\nCreated by Berry Ziskind - 308183037\n\nFor more information and features click the Bullet about!");
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK Exitq (int panel, int event, void *callbackData,
					   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			SavePanelState (panelHandle, "panelData", 0);
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Fire (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_VAL, &flag); //Fire button state
			
			GetCtrlVal (panelHandle, PANEL_INTERVAL, &dt);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, dt);
			GetCtrlVal (panelHandle, PANEL_ANGLE, &angle);
			rangle = DegToRad(angle);//degree to radian
			GetCtrlVal (panelHandle, PANEL_SPEED, &speed);
			vx=speed*cos(rangle);//initial speed on x axis
			vy=speed*sin(rangle);//initial speed on y axis 
			
			
			if(flag){ //only if the fire (togglebutton) is initialy off it will ask the user to select file - *prevents crashes*
				MessagePopup ("Information", "Please choose/create file to continue");
				select = FileSelectPopup ("", ".csv", "", "Select a file", VAL_SAVE_BUTTON, 0, 0, 1, 1,graphsData);
			}
			
			if(select!=0){ //saves the data
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
				fp = fopen (graphsData, "w");
				flag2 = 1;//checks if file was chosen and data started to be saved - *prevents crashes* 
			}
			else
			{
				SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_VAL, 0);//if not selected file will not continue
			}
			break;
	}
	return 0;
}

int CVICALLBACK Time (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			if(flag2 == 1)
				fprintf(fp,"%lf,%lf\n",x,y);
			PlotPoint (panelHandle, PANEL_GRAPH, x, y, VAL_SOLID_CIRCLE, VAL_RED);
			
			//Physics Calculation
			x=x+vx*dt;
			y=y+vy*dt-g*(pow(dt,2)/2.0);
			vy = vy- g*dt;
	
			//Stop condition
			if(y<=0.001 ||  flag==0)
			{
				if(flag2 == 1)
					fclose(fp);
				
				SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_VAL, 0);
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			}

			break;
	}
	return 0;
}
//Reset all
int CVICALLBACK resetall (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			x=0;
			y=0;
			vx=speed*cos(rangle);
			vy=speed*sin(rangle);
			flag=0;
			flag2=0;
			
			break;
	}
	return 0;
}

int CVICALLBACK Cursor (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	double xcurs,ycurs;
	switch (event)
	{
		case EVENT_MOUSE_POINTER_MOVE:
			
			 GetGraphCursor (panelHandle, PANEL_GRAPH, 1, &xcurs, &ycurs);
			
			 SetCtrlVal (panelHandle, PANEL_XAXIS, xcurs);
			 SetCtrlVal(panelHandle, PANEL_YAXIS , ycurs);

			break;
	}
	return 0;
}

int CVICALLBACK Load (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	int color;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COLORNUM, &color);
			load = FileSelectPopup ("", ".csv", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 0,graphsData );
			if(load!=0)
			{
				fp = fopen(graphsData, "r");
				while (fgets(line,99,fp)!=0)
				{
					sscanf(line,"%lf,%lf",&x,&y);
					PlotPoint (panelHandle, PANEL_GRAPH, x, y, VAL_SOLID_DIAMOND, color);

				}
				fclose(fp); 
			break;
		}
	}
	return 0;
	
	
}

int CVICALLBACK About (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{   switch (event)
	{
		case EVENT_LEFT_CLICK:
			
			MessagePopup ("About", "Features:\n- Time interval selection\n- Reset All button will clear the graph\n- Zooming option for graph (CTRL+Mouse)\n- Can stop and continue the firing without crashes\n- Will not fire if no file selected fo saving data\n- Load files with selected colors\n- About button\n\n\nCreated by Berry Ziskind - 308183037 ");
			
			break;
	}
	return 0;
}
