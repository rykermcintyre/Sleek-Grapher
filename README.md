# Sleek-Grapher
## Read this in raw text format (written before I knew how to use markdown)
## Must have XQuartz installed to run
*********************************
* README: graph | project.cpp	*
* Ryker McIntyre		*
* December 2017			*
* Super Copywrighted Material	*
* Solo Project			*
*********************************

This program is a graphing calculator.

Type "make" to compile the executable: "graph".

"graph" has two modes: (1) Interactive, (2) Input.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1) Interactive:
Type "graph" to display a blank graph with x and y windows automatically set from -10 to +10.  A calculator will appear on the left-hand side of the screen.  Using the buttons, the user may type any equation they wish into the box.  Syntax MUST be C++ interpretable, as if the string that the user types in were to appear in a C++ script.  The program is set to handle as many invalid cases as the developer (Ryker McIntyre, TM) could think up.  However, a less common invalid prompt may cause the program to crash.  For example, instead of typing 6(sin(4x)), type 6*sin(4*x).  When the desired equation is typed in, hit the "Graph!" button to display the graph.  If incorrect syntax is detected, the program will not display a graph.  In addition, the keyboard can be used to type in the input.  A list of buttons, their keyboard shortcut equivalents, an example of C++ interpretable code for each, and a short description of each button's action is shown below is shown below:

+------------------------------------------------------------+
| Button  | Shortcut   | Example     | Action                |
+------------------------------------------------------------+
| x       | x          | 3*x         | y = f(x)              |
| e       | e          | pow(e,x)    | 2.71828               |
| pi      | z          | sin(pi*x)   | 3.14159               |
| SIN     | s          | sin(pi*x)   | Sine Function         |
| COS     | c          | cos(pi*x)   | Cosine Function       |
| TAN     | t          | tan(pi*x)   | Tangent Function      |
| POW     | p          | pow(x,2)    | Power Function        |
| ABS     | a          | abs(7*x)    | Absolute Value        |
| (       | [          | 4*(3+x)     | Left Parenthesis      |
| )       | ]          | (x-2)/pi    | Right Parenthesis     |
| ,       | ,          | pow(e,x)    | Separates Base/Exp    |
| +       | =          | x+4         | Addition              |
| -       | -          | 6-x 8*(-x)  | Subtraction/Negative  |
| *       | o          | x*7         | Multiplication        |
| /       | /          | 8/x         | Division              |
| .       | .          | 4.7         | Decimal Point         |
| 0 to 9  | 0 to 9     | 6           | Digits                |
| <-      | Backspace  |             | Delete Character      |
| AC      | Escape     |             | Clear All             |
| Graph!  | Return     |             | Display f(x)          |
+------------------------------------------------------------+

To exit the program, type "q" to quit or click the x in the corner.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2) Input
The major advantage of input mode is the ability to set the graph's window.  To use input mode, type the executable "graph" followed by a text file of the following format, with a fun example given on the right:

Format...		|   Example...
Line 1: equation	|   sin(8*pi*x) - 9*sin(x/pi)
Line 2: x-window size	|   10
Line 3: y-window size	|   10

However, once the graph has been created, it cannot be altered like it can in interactive mode.  As seen in the example, spaces are allowed in the syntax of the equation.  As long as the equation would be C++ interpretable, it should be able to be read.  The example text shown above is currently stored in a text file called "eq.txt" for the user's convenience.

The program can only read files of this format, so be sure to use it!

To exit the program, type "q" to quit or click the x in the corner.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Potential bugs:

A) Axes or buttons not appearing: If this happens, simply quit the program by typing "q" to quit or clicking the x in the corner and reload the program by typing the executable.

B) Program crashing: If this happens, it is almost certainly due to strange and invalid syntax.  Be sure to use valid syntax.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Happy graphing!

Yours truly,

	Ryker McIntyre

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
