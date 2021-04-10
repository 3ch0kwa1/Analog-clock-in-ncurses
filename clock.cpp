//made by 3ch0kwa1


#include <ncurses.h>
#include <bits/stdc++.h>
#include <cmath>
#include <time.h>

using namespace std;

int main(){
    initscr();
    noecho();
    start_color();
    
    int maxlines = LINES-1, maxcols = COLS-1;  //getting window parameters
    
    double pi = 3.141592653;
    
    int xcenter = maxlines/2, ycenter = maxcols/2;   //setting the center of the window
    
    int slength = min(maxcols,maxlines)/2-3;			//setting the length of each arm
    int mlength = slength*5/7;
    int hlength = slength/2;
    int sticklength = slength/4;
    
    int minute = 0, hour = 0, secundum = 0, month = 0, day = 0;
    int fmonth, smonth, fday, sday;
    
    double mangle = 0.0, hangle = 0.0, sangle = 0.0;		//these are the angels of the arms (0 is up and pi is down)
    
    double numberangle = 0.0;
    double numberangles[12] = {{0.0}};						//the numbers' positions
    for(int i=0;i<12;i++){
		numberangle += pi/6.0;
		numberangles[i] += numberangle;
	}
	
	string numbers = "123456789";
	
	init_pair(1,COLOR_YELLOW,COLOR_BLACK);
	
	for(double fi=0.0;fi<2*pi;fi+=0.01){											
		wmove(stdscr, xcenter-((slength+2)*cos(fi)), ycenter+2*((slength+2)*sin(fi)));		//the big circle
		waddch(stdscr,'o');	
	}
		
	bool sticks[10][7] = {{1,1,0,1,1,1,1},{0,1,0,0,1,0,0,},{1,1,1,0,0,1,1},{1,1,1,0,1,1,0},{0,1,1,1,1,0,0},				//7-segment display
						  {1,0,1,1,1,1,0},{1,0,1,1,1,1,1},{1,1,0,0,1,0,0,},{1,1,1,1,1,1,1},{1,1,1,1,1,1,0}};
    
    while(true){
		
		wmove(stdscr,xcenter,ycenter);								//the center square
		waddch(stdscr,'#');
		wmove(stdscr,xcenter+1,ycenter);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter+1,ycenter+1);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter+1,ycenter-1);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter-1,ycenter);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter-1,ycenter+1);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter-1,ycenter-1);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter,ycenter-1);
		waddch(stdscr,'o');
		wmove(stdscr,xcenter,ycenter+1);
		waddch(stdscr,'o');
		
		for(double i=2.0;i<slength;i+=0.3){									//removing the arms from the last tick
			wmove(stdscr, xcenter-(i*cos(sangle)), ycenter+2*(i*sin(sangle)));
			waddch(stdscr,' ');
		}
		
		for(double i=2.0;i<mlength;i+=0.3){
			wmove(stdscr, xcenter-(i*cos(mangle)), ycenter+2*(i*sin(mangle)));
			waddch(stdscr,' ');
		}
		
		for(double i=2.0;i<hlength;i+=0.3){
			wmove(stdscr, xcenter-(i*cos(hangle)), ycenter+2*(i*sin(hangle)));
			waddch(stdscr,' ');
		}
																				//printing the numbers
		for(int i=0;i<9;i++){
			wmove(stdscr, xcenter-((slength-1)*cos(numberangles[i])), ycenter+2*((slength-1)*sin(numberangles[i])));
			waddch(stdscr, numbers[i]);
		}
		
		wmove(stdscr, xcenter-((slength-1)*cos(numberangles[9])), ycenter+2*((slength-1)*sin(numberangles[9])));
		wprintw(stdscr, "10");
		
		wmove(stdscr, xcenter-((slength-1)*cos(numberangles[10])), ycenter+2*((slength-1)*sin(numberangles[10])));
		wprintw(stdscr, "11");
		
		wmove(stdscr, xcenter-((slength-1)*cos(numberangles[11])), ycenter+2*((slength-1)*sin(numberangles[11])));
		wprintw(stdscr, "12");
		
		time_t now = time(0);								//getting time data
		tm *ltm = localtime(&now);
		
		secundum = ltm->tm_sec;								//setting the angles of the arms
		sangle = pi/30*secundum;
		
		minute = ltm->tm_min;
		mangle = pi/30*minute;
		
		hour = ltm->tm_hour;
		hangle = (2*pi/12)*(hour%12);
		
		month = ltm->tm_mon;
		day = ltm->tm_mday;
		
		fmonth = month/10;
		smonth = month%10;
		fday = day/10;
		sday = day%10;
		
		for(double i=2.0;i<slength;i+=0.3){										//printing the arms
			wmove(stdscr, xcenter-(i*cos(sangle)), ycenter+2*(i*sin(sangle)));
			waddch(stdscr,'s');
		}
		
		//attron(COLOR_PAIR(3));
		
		for(double i=2.0;i<mlength;i+=0.3){
			wmove(stdscr, xcenter-(i*cos(mangle)), ycenter+2*(i*sin(mangle)));
			waddch(stdscr,'m');
		}
		
		//attron(COLOR_PAIR(4));
		
		for(double i=2.0;i<hlength;i+=0.3){
			wmove(stdscr, xcenter-(i*cos(hangle)), ycenter+2*(i*sin(hangle)));
			waddch(stdscr,'h');
		}
		
		attron(COLOR_PAIR(1));										//changing the color to yellow
		
		for(int i=0;i<sticklength;i++){											//printing the date
			wmove(stdscr, xcenter+(3), ycenter-6-sticklength-i);
			if(sticks[fmonth][0]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter-6-sticklength);
			if(sticks[fmonth][1]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength)/2, ycenter-6-sticklength-i);
			if(sticks[fmonth][2]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter-6-2*sticklength);
			if(sticks[fmonth][3]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter-6-sticklength);
			if(sticks[fmonth][4]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(2*sticklength)/2, ycenter-6-sticklength-i);
			if(sticks[fmonth][5]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter-6-2*sticklength);
			if(sticks[fmonth][6]) waddch(stdscr,'<');
			else waddch(stdscr,' ');
		}
		
		for(int i=0;i<sticklength;i++){
			wmove(stdscr, xcenter+3, ycenter-3-i);
			if(sticks[smonth][0]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter-3);
			if(sticks[smonth][1]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength)/2, ycenter-3-i);
			if(sticks[smonth][2]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter-3-sticklength);
			if(sticks[smonth][3]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter-3);
			if(sticks[smonth][4]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(2*sticklength)/2, ycenter-3-i);
			if(sticks[smonth][5]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter-3-sticklength);
			if(sticks[smonth][6]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
		}
		
		for(int i=0;i<sticklength;i++){
			wmove(stdscr, xcenter+3, ycenter+3+i);
			if(sticks[fday][0]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter+3+sticklength);
			if(sticks[fday][1]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength)/2, ycenter+3+i);
			if(sticks[fday][2]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter+3);
			if(sticks[fday][3]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter+3+sticklength);
			if(sticks[fday][4]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(2*sticklength)/2, ycenter+3+i);
			if(sticks[fday][5]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter+3);
			if(sticks[fday][6]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
		}
		
		for(int i=0;i<sticklength;i++){
			wmove(stdscr, xcenter+(3), ycenter+6+sticklength+i);
			if(sticks[sday][0]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter+6+2*sticklength);
			if(sticks[sday][1]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength)/2, ycenter+6+sticklength+i);
			if(sticks[sday][2]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+i/2, ycenter+6+sticklength);
			if(sticks[sday][3]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter+6+2*sticklength);
			if(sticks[sday][4]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(2*sticklength)/2, ycenter+6+sticklength+i);
			if(sticks[sday][5]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
			
			wmove(stdscr, xcenter+3+(sticklength+i)/2, ycenter+6+sticklength);
			if(sticks[sday][6]) waddch(stdscr,'#');
			else waddch(stdscr,' ');
		}
		
		wmove(stdscr, xcenter+3+(2*sticklength)/2, ycenter);								//the point between month and day
		waddch(stdscr, '#');
		
		attroff(COLOR_PAIR(1));																//reset the color to white for the next tick
		
		
		refresh();														//adjust changes
		
		
	}
    
    getch();										//these commands are obligatory, but in this case, they have no meaning
    endwin();

    return 0;
}
