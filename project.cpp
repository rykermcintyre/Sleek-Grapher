// Final project
// Ryker McIntyre
// December 2017

#include "gfx.h"
#include <string>
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

#define pi 3.1415926535897932384626433832795
#define e  2.7182818284590452353602874713527
   
// Functions for which type of calculator to use
void buttons(void);
void input(string);

// Calculator button cell shape
void cell(int, int, int);

// Check if equation is valid
bool check(string);

// Function-string interpreter
double evaluate(string, double);

// Main function (all three lines!)
int main(int argc, char *argv[]) {
	if (argc == 1) buttons(); // If argc = 1, run a graphing calculator with buttons
	if (argc == 2) {string file = argv[1]; input(file);} // If argc = 2, use argv[1] as input text file
	return 0;
}

// Graphing calculator with buttons
void buttons(void) {
	char c;
	int x_pos;
	int y_pos;
	string eq = "";
	vector<double> old_x_vect = {99999999999999};
	vector<double> old_y_vect = {99999999999999};
	
	// Open window, set color
	int wd = 1200, ht = 750;
	gfx_open(wd, ht, "Graphing Calculator");
	int gray = 140;
	gfx_color(gray, gray, gray);
	
	// Set axes window/steps
	int x_window = 400;
	int y_window = 300;
	int x_mid = wd/2 + 100;
	int y_mid = ht/2;
	gfx_line(x_mid-x_window, y_mid, x_mid+x_window, y_mid);
	gfx_line(x_mid, y_mid-y_window, x_mid, y_mid+y_window);
	gfx_line(x_mid-10, y_mid-y_window, x_mid+10, y_mid-y_window);
	gfx_line(x_mid-10, y_mid+y_window, x_mid+10, y_mid+y_window);
	gfx_line(x_mid-x_window, y_mid-10, x_mid-x_window, y_mid+10);
	gfx_line(x_mid+x_window, y_mid-10, x_mid+x_window, y_mid+10);
	
	double x_max = 10;
	double y_max = 10;
	double x_step = x_max/x_window;
	double y_step = y_max/y_window;
	double x_scale = 1 / x_step;
	double y_scale = 1 / y_step;
	
	// Label axes
	gfx_text(x_mid+x_window+5, y_mid+5, "X");
	gfx_text(x_mid-2, y_mid-y_window-5, "Y");
	string x_max_char = to_string((int)x_max);
	gfx_text(x_mid+x_window, y_mid+24, x_max_char.c_str());
	string y_max_char = to_string((int)y_max);
	gfx_text(x_mid+15, y_mid-y_window, y_max_char.c_str());
	
	// Create calculator buttons
	cell(25, y_mid + 200, 1);	gfx_text(42, y_mid + 180, "ABS");
	cell(75, y_mid + 200, 1);	gfx_text(98, y_mid + 180, "0");
	cell(125, y_mid + 200, 1);	gfx_text(148, y_mid + 180, ".");
	cell(175, y_mid + 200, 2);	gfx_text(210, y_mid + 180, "GRAPH!");
	cell(25, y_mid + 150, 1);	gfx_text(42, y_mid + 130, "POW");
	cell(75, y_mid + 150, 1);	gfx_text(98, y_mid + 130, "1");
	cell(125, y_mid + 150, 1);	gfx_text(148, y_mid + 130, "2");
	cell(175, y_mid + 150, 1);	gfx_text(198, y_mid + 130, "3");
	cell(225, y_mid + 150, 1);	gfx_text(248, y_mid + 130, "+");
	cell(25, y_mid + 100, 1);	gfx_text(42, y_mid + 80, "TAN");
	cell(75, y_mid + 100, 1);	gfx_text(98, y_mid + 80, "4");
	cell(125, y_mid + 100, 1);	gfx_text(148, y_mid + 80, "5");
	cell(175, y_mid + 100, 1);	gfx_text(198, y_mid + 80, "6");
	cell(225, y_mid + 100, 1);	gfx_text(248, y_mid + 80, "-");
	cell(25, y_mid + 50, 1);	gfx_text(42, y_mid + 30, "COS");
	cell(75, y_mid + 50, 1);	gfx_text(98, y_mid + 30, "7");
	cell(125, y_mid + 50, 1);	gfx_text(148, y_mid + 30, "8");
	cell(175, y_mid + 50, 1);	gfx_text(198, y_mid + 30, "9");
	cell(225, y_mid + 50, 1);	gfx_text(248, y_mid + 30, "*");
	cell(25, y_mid, 1);		gfx_text(42, y_mid - 20, "SIN");
	cell(75, y_mid, 1);		gfx_text(98, y_mid - 20, "(");
	cell(125, y_mid, 1);		gfx_text(148, y_mid - 20, ")");
	cell(175, y_mid, 1);		gfx_text(198, y_mid - 20, ",");
	cell(225, y_mid, 1);		gfx_text(248, y_mid - 20, "/");
	cell(25, y_mid - 50, 1);	gfx_text(48, y_mid - 70, "x");
	cell(75, y_mid - 50, 1);	gfx_text(98, y_mid - 70, "e");
	cell(125, y_mid - 50, 1);	gfx_text(146, y_mid - 70, "pi");
	cell(175, y_mid - 50, 1);	gfx_text(195, y_mid - 70, "<-");
	cell(225, y_mid - 50, 1);	gfx_text(246, y_mid - 70, "AC");
	cell(25, y_mid - 110, 3);	gfx_text(42, y_mid - 130, "y =");
	
	while (true) {
		
		// Wait for input, quit if q
		c = gfx_wait();
		x_pos = gfx_xpos();
		y_pos = gfx_ypos();
		if (c == 'q') break;
		
		// Handle input from buttons/keyboard, store in string "eq"
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid + 150 && y_pos < y_mid + 200)) || c == 'a') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "abs";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid + 150 && y_pos < y_mid + 200)) || c == '0') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "0";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid + 150 && y_pos < y_mid + 200)) || c == '.') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += ".";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid + 100 && y_pos < y_mid + 150)) || c == 'p') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "pow";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid + 100 && y_pos < y_mid + 150)) || c == '1') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "1";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid + 100 && y_pos < y_mid + 150)) || c == '2') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "2";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 225) && (y_pos >= y_mid + 100 && y_pos < y_mid + 150)) || c == '3') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "3";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 225 && x_pos < 275) && (y_pos >= y_mid + 100 && y_pos < y_mid + 150)) || c == '=') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "+";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid + 50 && y_pos < y_mid + 100)) || c == 't') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "tan";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid + 50 && y_pos < y_mid + 100)) || c == '4') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "4";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid + 50 && y_pos < y_mid + 100)) || c == '5') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "5";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 225) && (y_pos >= y_mid + 50 && y_pos < y_mid + 100)) || c == '6') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "6";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 225 && x_pos < 275) && (y_pos >= y_mid + 50 && y_pos < y_mid + 100)) || c == '-') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "-";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid && y_pos < y_mid + 50)) || c == 'c') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "cos";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid && y_pos < y_mid + 50)) || c == '7') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "7";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid && y_pos < y_mid + 50)) || c == '8') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "8";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 225) && (y_pos >= y_mid && y_pos < y_mid + 50)) || c == '9') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "9";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 225 && x_pos < 275) && (y_pos >= y_mid && y_pos < y_mid + 50)) || c == 'o') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "*";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid - 50 && y_pos < y_mid)) || c == 's') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "sin";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid - 50 && y_pos < y_mid)) || c == '[') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "(";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid - 50 && y_pos < y_mid)) || c == ']') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += ")";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 225) && (y_pos >= y_mid - 50 && y_pos < y_mid)) || c == ',') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += ",";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 225 && x_pos < 275) && (y_pos >= y_mid - 50 && y_pos < y_mid)) || c == '/') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "/";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 25 && x_pos < 75) && (y_pos >= y_mid - 100 && y_pos < y_mid - 50)) || c == 'x') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "x";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 75 && x_pos < 125) && (y_pos >= y_mid - 100 && y_pos < y_mid - 50)) || c == 'e') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "e";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 125 && x_pos < 175) && (y_pos >= y_mid - 100 && y_pos < y_mid - 50)) || c == 'z') {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq += "pi";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 225) && (y_pos >= y_mid - 100 && y_pos < y_mid - 50)) || c == 8) {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			if (eq.size() > 0) eq.pop_back();
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 225 && x_pos < 275) && (y_pos >= y_mid - 100 && y_pos < y_mid - 50)) || c == 27) {
			gfx_color(0, 0, 0);	gfx_text(75, y_mid - 130, eq.c_str());
			eq = "";
			gfx_color(0, 255, 0);	gfx_text(75, y_mid - 130, eq.c_str());
		}
		if ((c == 1 && (x_pos >= 175 && x_pos < 275) && (y_pos >= y_mid + 150 && y_pos < y_mid + 200)) && (check(eq)) || ((c == 13) && check(eq))) {
			
			// Make x vector
			vector<double> x_vect;
			for (double i = -x_max; i <= x_max; i += x_step) {
				x_vect.push_back(i);
			}
			// Make y vector based on equation for x vector
			vector<double> y_vect;
			double x;
			double y;
			for (int i = 0; i < x_vect.size(); i++) {
				x = x_vect[i];
				y = evaluate(eq,x);
				y_vect.push_back(y);
			}
			// Delete last graph
			double x_prev = old_x_vect[0];
			double y_prev = old_y_vect[0];
			double x_prev_pt, y_prev_pt, x_pt, y_pt;
			gfx_color(0, 0, 0);
			for (int i = 1; i < old_x_vect.size(); i++) {
				x = old_x_vect[i];
				y = old_y_vect[i];
				
				x_prev_pt = (x_prev*x_scale+x_mid);
				y_prev_pt = (-y_prev*y_scale+y_mid);
				x_pt = (x*x_scale+x_mid);
				y_pt = (-y*y_scale+y_mid);
				
				if (abs(y) <= y_max && abs(old_y_vect[i-1]) <= y_max) {
					gfx_line(x_prev_pt, y_prev_pt, x_pt, y_pt);
				}
				x_prev = old_x_vect[i];
				y_prev = old_y_vect[i];
			}
			gfx_color(0, 255, 0);
			// Print graph on screen
			x_prev = x_vect[0];
			y_prev = y_vect[0];
			gfx_color(255, 0, 0);
			for (int i = 1; i < x_vect.size(); i++) {
				x = x_vect[i];
				y = y_vect[i];
				
				x_prev_pt = (x_prev*x_scale+x_mid);
				y_prev_pt = (-y_prev*y_scale+y_mid);
				x_pt = (x*x_scale+x_mid);
				y_pt = (-y*y_scale+y_mid);
				
				if (abs(y) <= y_max && abs(y_vect[i-1]) <= y_max) {
					gfx_line(x_prev_pt, y_prev_pt, x_pt, y_pt);
				}
				x_prev = x_vect[i];
				y_prev = y_vect[i];
			}
			gfx_color(0, 255, 0);
			
			// Set the old equation equal to the current
			old_x_vect = x_vect;
			old_y_vect = y_vect;
		}
		
		// Redraw axes
		gfx_color(gray, gray, gray);
		gfx_line(x_mid-x_window, y_mid, x_mid+x_window, y_mid);
		gfx_line(x_mid, y_mid-y_window, x_mid, y_mid+y_window);
		gfx_line(x_mid-10, y_mid-y_window, x_mid+10, y_mid-y_window);
		gfx_line(x_mid-10, y_mid+y_window, x_mid+10, y_mid+y_window);
		gfx_line(x_mid-x_window, y_mid-10, x_mid-x_window, y_mid+10);
		gfx_line(x_mid+x_window, y_mid-10, x_mid+x_window, y_mid+10);
		
		// Relabel axes
		gfx_text(x_mid+x_window+5, y_mid+5, "X");
		gfx_text(x_mid-2, y_mid-y_window-5, "Y");
		gfx_text(x_mid+x_window, y_mid+24, x_max_char.c_str());
		gfx_text(x_mid+15, y_mid-y_window, y_max_char.c_str());
		
	}
}

// Graphing calculator using input file
void input(string file) {
	char c;
	string equation;
	string eq_print;
	string x_max_str;
	string y_max_str;
	
	ifstream ifs;
	ifs.open(file);
	if (!ifs) return;
	getline(ifs,equation,'\n');
	getline(ifs, x_max_str,'\n');
	getline(ifs, y_max_str,'\n');
	ifs.close();
	
	if (check(equation) == 0) return;
	
	double x_max = stod(x_max_str);
	double y_max = stod(y_max_str);
	
	while (true) {
		
		// Open window, set color
		int wd = 1200, ht = 750;
		gfx_open(wd, ht, "Graphing Calculator");
		int gray = 140;
		gfx_color(gray, gray, gray);
		
		// Set axes window/steps
		int x_window = 500;
		int y_window = 300;
		int x_mid = wd/2;
		int y_mid = ht/2;
		gfx_line(x_mid-x_window, y_mid, x_mid+x_window, y_mid);
		gfx_line(x_mid, y_mid-y_window, x_mid, y_mid+y_window);
		gfx_line(x_mid-10, y_mid-y_window, x_mid+10, y_mid-y_window);
		gfx_line(x_mid-10, y_mid+y_window, x_mid+10, y_mid+y_window);
		gfx_line(x_mid-x_window, y_mid-10, x_mid-x_window, y_mid+10);
		gfx_line(x_mid+x_window, y_mid-10, x_mid+x_window, y_mid+10);
		
		double x_step = x_max/x_window;
		double y_step = y_max/y_window;
		double x_scale = 1 / x_step;
		double y_scale = 1 / y_step;
		
		// Label axes
		gfx_text(x_mid+x_window+5, y_mid+5, "X");
		gfx_text(x_mid-2, y_mid-y_window-5, "Y");
		string x_max_char = to_string((int)x_max);
		gfx_text(x_mid+x_window, y_mid+24, x_max_char.c_str());
		string y_max_char = to_string((int)y_max);
		gfx_text(x_mid+15, y_mid-y_window, y_max_char.c_str());
		
		gfx_flush();
		
		// Make x vector
		vector<double> x_vect;
		for (double i = -x_max; i <= x_max; i += x_step) {
			x_vect.push_back(i);
		}
		// Make y vector based on equation for x vector
		vector<double> y_vect;
		double x;
		double y;
		for (int i = 0; i < x_vect.size(); i++) {
			x = x_vect[i];
			y = evaluate(equation,x);
			y_vect.push_back(y);
		}
		// Print graph on screen
		double x_prev = x_vect[0];
		double y_prev = y_vect[0];
		double x_prev_pt, y_prev_pt, x_pt, y_pt;
		gfx_color(255, 0, 0);
		for (int i = 1; i < x_vect.size(); i++) {
			x = x_vect[i];
			y = y_vect[i];
			
			x_prev_pt = (x_prev*x_scale+x_mid);
			y_prev_pt = (-y_prev*y_scale+y_mid);
			x_pt = (x*x_scale+x_mid);
			y_pt = (-y*y_scale+y_mid);
			
			if (abs(y) <= y_max && abs(y_vect[i-1]) <= y_max) {
				gfx_line(x_prev_pt, y_prev_pt, x_pt, y_pt);
			}
			x_prev = x_vect[i];
			y_prev = y_vect[i];
			gfx_flush();
		}
		gfx_color(gray, gray, gray);
		
		// Print equation to window
		eq_print = "y = " + equation;
		gfx_color(255, 255, 255);
		gfx_text(100, 50, eq_print.c_str());
		gfx_color(gray, gray, gray);
		
		// Wait for input
		c = gfx_wait();
		if (c == 'q') break;
	}
}

// Cell on calculator
void cell(int x, int y, int type) {
	gfx_color(0, 255, 0);
	if (type == 1) {
		gfx_line(x, y, x + 50, y);
		gfx_line(x, y, x, y - 50);
		gfx_line(x + 50, y, x + 50, y - 50);
		gfx_line(x, y - 50, x + 50, y - 50);
	}
	if (type == 2) {	
		gfx_line(x, y, x + 100, y);
		gfx_line(x, y, x, y - 50);
		gfx_line(x + 100, y, x + 100, y - 50);
		gfx_line(x, y - 50, x + 100, y - 50);
	}
	if (type == 3) {
		gfx_line(x, y, x + 250, y);
		gfx_line(x, y, x, y - 50);
		gfx_line(x + 250, y, x + 250, y - 50);
		gfx_line(x, y - 50, x + 250, y - 50);
	}
}

// Check equation for validity
bool check(string eq) {
	char let;
	char last_let;
	char next_let;
	// Get rid of spaces in string
	string holder;
	for (int i = 0; i < eq.size(); i++) {
		let = eq[i];
		if (let != ' ') {
			holder.push_back(let);
		}
	}
	eq = holder;
	if (eq.size() == 0) return 0;
	if ((eq.size() == 1) && ((eq[0] >= 48 && eq[0] <= 57) || (eq[0] == 'x') || (eq[0] == 'e'))) return 1;
	if (eq[0] != '0' && eq[0] != '1' && eq[0] != '2' && eq[0] != '3' && eq[0] != '4' && eq[0] != '5' && eq[0] != '6' && eq[0] != '7' && eq[0] != '8' && eq[0] != '9' && eq[0] != '.' && eq[0] != 'x' && eq[0] != 'e' && eq[0] != 'p' && eq[0] != '(' && eq[0] != '-' && eq[0] != 's' && eq[0] != 'c' && eq[0] != 't' && eq[0] != 'a') {
		return 0;
	}
	char final_let = eq[eq.size() - 1];
	if (final_let != '0' && final_let != '1' && final_let != '2' && final_let != '3' && final_let != '4' && final_let != '5' && final_let != '6' && final_let != '7' && final_let != '8' && final_let != '9' && final_let != 'x' && final_let != 'e' && final_let != 'i' && final_let != ')' && final_let != '.') {
		return 0;
	} 
	int p_count = 0;
	for (int i = 0; i < eq.size(); i++) {
		if (eq[i] == '(') p_count++;
		if (eq[i] == ')') p_count--;
	}
	for (int i = 0; i < eq.size() - 2; i++) {
		if (eq[i] == 's' && eq[i+1] == 'i' && eq[i+2] != 'n') return 0;
	}
	if (eq[eq.size() - 1] == 'i' && eq[eq.size() - 2] != 'p') return 0;
	if (p_count != 0) return 0;
	for (int i = 1; i < eq.size(); i++) {
		let = eq[i];
		last_let = eq[i-1];
		if (let == 'x') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == 'e') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == 'p') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == 's') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(' && last_let != 'b' && last_let != 'o') {
				return 0;
			}
		}
		if (let == 'c') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == 't') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == 'a') {
			if (last_let != '-' && last_let != '+' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(' && last_let != 't') {
				return 0;
			}
		}
		if (let == '(') {
			if (last_let != 'n' && last_let != 's' && last_let != 'w' && last_let != '+' && last_let != '-' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
		if (let == ')') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x') {
				return 0;
			}
		}
		if (let == ',') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x') {
				return 0;
			}
		}
		if (let == '/') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x') {
				return 0;
			}
		}
		if (let == '*') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x') {
				return 0;
			}
		}
		if (let == '+') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x') {
				return 0;
			}
		}
		if (let == '-') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != ')' && last_let != 'i' && last_let != 'e' && last_let != 'x' && last_let != '(' && last_let != ',' && last_let != '/' && last_let != '*' && last_let != '+') {
				return 0;
			}
		}
		if (let == '0' || let == '1' || let == '2' || let == '3' || let == '4' || let == '5' || let == '6' || let == '7' || let == '8' || let == '9') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != '(' && last_let != ',' && last_let != '/' && last_let != '*' && last_let != '+' && last_let != '-' && last_let != '.') {
				return 0;
			}
		} 
		if (let == '.') {
			if (last_let != '0' && last_let != '1' && last_let != '2' && last_let != '3' && last_let != '4' && last_let != '5' && last_let != '6' && last_let != '7' && last_let != '8' && last_let != '9' && last_let != '+' && last_let != '-' && last_let != '*' && last_let != '/' && last_let != ',' && last_let != '(') {
				return 0;
			}
		}
	}
	return 1;
}

// Function-string interpreter
double evaluate(string f, double in) {
	
	// Variables
	double out; //output
	int size = f.size();
	char current_let;
	char last_let = '\0';
	string expr;
	string expr1;
	string expr2;
	int i;
	
	// + - * / cos sin tan pow abs
	
	// Get rid of spaces in string
	string holder;
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let != ' ') {
			holder.push_back(current_let);
		}
	}
	f = holder;
	size = f.size();
	// Change minus signs to ~s to differentiate from negative signs
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '-') {
			if (last_let >= 48 && last_let <= 57) {
				f[i] = '~';
			}
			if (last_let == 'x' || last_let == 'e' || last_let == 'i' || last_let == ')' || last_let == ']') {
				f[i] = '~';
			}
		}
		last_let = current_let;
	}
	last_let = '\0';
//	cout << "-2~ " << f << endl;
	// Change parenthesis that AREN'T function parenthesis to brackets
	int p_count = 0;
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '(') {
			if (last_let != 's' && last_let != 'n' && last_let != 'w') {
				f[i] = '[';
				for (int j = i + 1; j < size; j++) {
					current_let = f[j];
					if (current_let == '(') p_count++;
					if (current_let == ')' && p_count == 0) {
						f[j] = ']';
						break;
					}
					if (current_let == ')' && p_count > 0) {
						p_count--;
					}
				}
			} 
		}
		last_let = f[i];
	}
	size = f.size();
	p_count = 0;
//	cout << "[ ] " << f << endl;
	
	// Parse string
	// Find []
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '[') {
			int first = i + 1;
			int last = i + 1;
			for (int j = i + 1; j < size; j++) {
				current_let = f[j];
				if (current_let == '[') {p_count++;}
				if (current_let == ']' && p_count == 0) {
					last = j - 1;
					break;
				}
				if (current_let == ']' && p_count > 0) {p_count--;}
			}
			int length = last - first + 1;
			expr = f.substr(first, length);
			string sub = to_string(evaluate(expr, in));
			f.replace(first - 1, length + 2, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "[f] " << f << endl;
	// Find pow
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'p' && f[i+1] == 'o' && f[i+2] == 'w') {
			int first = i + 4; // p ow( 'first'
			int precomma = i + 4;
			int postcomma = i + 4;
			int last = i + 4;
			int j;
			for (j = i + 4; j < size; j++) {
				current_let = f[j];
				if (current_let == '(') {p_count++;}
				if (current_let == ')') {p_count--;}
				if (current_let == ',' && p_count == 0) {
					precomma = j - 1;
					postcomma = j + 1;
					break;
				}
			}
			p_count = 0;
			for (int k = postcomma; k < size; k++) {
				current_let = f[k];
				if (current_let == '(') {p_count++;}
				if (current_let == ')' && p_count == 0) {
					last = k - 1;
					break;
				}
				if (current_let == ')' && p_count > 0) {p_count--;}
			}
			int length1 = precomma - first + 1;
			int length2 = last - postcomma + 1;
			expr1 = f.substr(first, length1);
			expr2 = f.substr(postcomma, length2);
			string sub = to_string(pow(evaluate(expr1, in), evaluate(expr2, in)));
			f.replace(first - 4, (length1+length2) + 6, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "pow " << f << endl;
	// Find abs
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'a' && f[i+1] == 'b' && f[i+2] == 's') {
			int first = i + 4; // a bs( 'first'
			int last = i + 4;
			int j;
			for (j = i + 4; j < size; j++) {
				current_let = f[j];
				if (current_let == '(') {p_count++;}
				if (current_let == ')' && p_count == 0) {
					last = j - 1;
					break;
				}
				if (current_let == ')' && p_count > 0) {p_count--;}
			}
			int length = last - first + 1;
			expr = f.substr(first, length);
			string sub = to_string(abs(evaluate(expr, in)));
			f.replace(first - 4, (length) + 5, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "abs " << f << endl;
	// Find sin
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 's' && f[i+1] == 'i' && f[i+2] == 'n') {
			int first = i + 4; // s in( 'first'
			int last = i + 4;
			int j;
			for (j = i + 4; j < size; j++) {
				current_let = f[j];
				if (current_let == '(') {p_count++;}
				if (current_let == ')' && p_count == 0) {
					last = j - 1;
					break;
				}
				if (current_let == ')' && p_count > 0) {p_count--;}
			}
			int length = last - first + 1;
			expr = f.substr(first, length);
			string sub = to_string(sin(evaluate(expr, in)));
			f.replace(first - 4, (length) + 5, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "sin " << f << endl;
	// Find cos
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'c' && f[i+1] == 'o' && f[i+2] == 's') {
			int first = i + 4; // s in( 'first'
			int last = i + 4;
			int j;
			for (j = i + 4; j < size; j++) {
				current_let = f[j];
				if (current_let == '(') {p_count++;}
				if (current_let == ')' && p_count == 0) {
					last = j - 1;
					break;
				}
				if (current_let == ')' && p_count > 0) {p_count--;}
			}
			int length = last - first + 1;
			expr = f.substr(first, length);
			string sub = to_string(cos(evaluate(expr, in)));
			f.replace(first - 4, (length) + 5, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "cos " << f << endl;
	// Find tan
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 't' && f[i+1] == 'a' && f[i+2] == 'n') {
			int first = i + 4; // s in( 'first'
			int last = i + 4;
			int j;
			for (j = i + 4; j < size; j++) {
				current_let = f[j];
				if (current_let == '(') {p_count++;}
				if (current_let == ')' && p_count == 0) {
					last = j - 1;
					break;
				}
				if (current_let == ')' && p_count > 0) {p_count--;}
			}
			int length = last - first + 1;
			expr = f.substr(first, length);
			string sub = to_string(tan(evaluate(expr, in)));
			f.replace(first - 4, (length) + 5, sub);
			i = 0;
			size = f.size();
		}
	}
	p_count = 0;
	size = f.size();
//	cout << "tan " << f << endl;
	// Use - (~)
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '~') {
			int length1 = i;
			int length2 = size - i - 1;
			expr1 = f.substr(0, length1);
			expr2 = f.substr(i+1, length2);
			string sub = to_string(evaluate(expr1, in) - evaluate(expr2,in));
			f = sub;
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "--- " << f << endl;
	// Use +
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '+') {
			int length1 = i;
			int length2 = size - i - 1;
			expr1 = f.substr(0, length1);
			expr2 = f.substr(i+1, length2);
			string sub = to_string(evaluate(expr1, in) + evaluate(expr2,in));
			f = sub;
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "+++ " << f << endl;
	// Use /
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '/') {
			int length1 = i;
			int length2 = size - i - 1;
			expr1 = f.substr(0, length1);
			expr2 = f.substr(i+1, length2);
			string sub = to_string(evaluate(expr1, in) / evaluate(expr2,in));
			f = sub;
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "/// " << f << endl;
	// Use *
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == '*') {
			int length1 = i;
			int length2 = size - i - 1;
			expr1 = f.substr(0, length1);
			expr2 = f.substr(i+1, length2);
			string sub = to_string(evaluate(expr1, in) * evaluate(expr2,in));
			f = sub;
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "*** " << f << endl;
	// Change all x's to the value of the input
	string in_str = to_string(in);
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'x') {
			f.replace(i, 1, in_str);
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "x   " << f << endl;
	// Change all e's to e
	string e_str = to_string(e);
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'e') {
			f.replace(i, 1, e_str);
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "e   " << f << endl;
	// Change all pi's to pi
	string pi_str = to_string(pi);
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if (current_let == 'p' && f[i+1] == 'i') {
			f.replace(i, 2, pi_str);
			i = 0;
			size = f.size();
		}
	}
	size = f.size();
//	cout << "pi  " << f << endl;
	// Get rid of "--" (since that's just + )
	holder = "";
	for (i = 0; i < size; i++) {
		current_let = f[i];
		if ((current_let == '-' && last_let == '-') || (current_let == '-' && f[i+1] == '-')) {}
		else {holder.push_back(current_let);}
		last_let = current_let;
	}
	f = holder;
	size = f.size();
	last_let = '\0';
//	cout << "--  " << f << endl;
	
	//cout << f << " ";
	out = stod(f);
	return out;
}








































