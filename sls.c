#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

const int r_mid = 23;
const int r_length = 185;
const int r_tail = 0;
const int r_shake = 5;
char *rocket[];
char *blank;

void display(int pos, int offset, int h) {
	int i;
	for(i = 0; i < h && i + pos < r_length; i++) {
		mvprintw(i, offset - r_shake / 2, blank);
		mvprintw(i, offset, "%s", rocket[i + pos]);
	}
	for(; i < h; i++) {
		mvprintw(i, offset, blank);
	}
	refresh();
}

void rocket_launch(int w, int h) {
	int offset = w / 2 - r_mid;
	int t = 0;
	const int wait_time = 15;
	while(t < wait_time) {
		display(0, offset + rand() % r_shake - (r_shake/2), h);
		t++;
		usleep(50000);
	}
	double pos = 0;
	double v = 0;
	const double a = 0.01;

	while((int)pos < r_length + r_tail + h) {
		display((int)pos, offset + rand() % r_shake - (r_shake/2), h);
		v += a;
		pos += v;
		usleep(50000);
	}
}

int main() {
	/* init rand */
	srand(time(NULL));

	/* init blank line */
	blank = malloc(50 + r_shake * 2 + 1);
	memset(blank, ' ', 50 + r_shake * 2);

	/* init ncurses */
	int width, height;
	initscr();
	getmaxyx(stdscr, height, width);
	curs_set(0);

	/* run launch routine */
	rocket_launch(width, height);

	/* end ncurses */
	endwin();
}

char *rocket[] = {
"                       A",
"                       M",
"                       M",
"                       M",
"                       M",
"                       M",
"                       M",
"                       M",
"                      /M\\",
"                     '[V]'",
"                      [A]",
"                     [,-']",
"                     [/\"\\]",
"                     / _ \\",
"                    / / | \\",
"                   / /_O_| \\",
"                  /______|__\\",
"                  |=_==_==_=|",
"                  |  |   |  |",
"                 V|  |.V.|__|V",
"                 A|  |'A'| =|A",
"                  |__|___|= |",
"                  |__|___| =|",
"                  |####|####|",
"                 |    o|     |",
"                 |     |     |",
"                 |     |     |",
"                |      |      |",
"                |      |      |",
"                |      |      |",
"               |       |       |",
"               |       |       |",
"               |-------|-------|",
"              |        |        |",
"              |        |        |",
"              |___.____|____.___|",
"             |                   |",
"             |___________________|",
"            /|HH|      |HH][HHHHHI",
"            [|##|      |##][#####I",
"            [|##|      |#########I",
"            [|##|______|#######m#I",
"            [I|||||||||||||||||||I",
"            [I|||||||||||||||||||I",
"            [|                   |",
"            [|    H  H          H|",
"            [|    H  H          H|",
"            [|    \\hdF          V|",
"            [|     `'            |",
"            [|    d##b          d|",
"            [|    #hn           #|",
"            [|     \"\"#          }|",
"            [|    \\##/          V|",
"            [|                   |",
"            [|     dh           d|",
"            [|    d/\\h          d|",
"            [|    H\"\"H          H|",
"            [|    \"  \"          \"|",
"            [|________.^.________|",
"            [I########[ ]########I",
"            [I###[]###[.]########I",
"            [I###|||||[_]####||||I",
"            [####II####|        n |",
"           /###########|         \" \\",
"           ############|           |",
"          /############|            \\",
"          ######\"######|            |",
"         /             |####### #####\\",
"         |             |#######.######",
"        /              |##############\\",
"        |              |###############",
"       /_______________|###############\\",
"       I|||||||||||||||||||||||||||||||I",
"       I|||||||||||||||||||||||||||||||I",
"       I|||||||||||||||||||||||||||||||I",
"       I|||||||||||||||||||||||||||||||I",
"       |                               |",
"       |-------------------------------|",
"       |                               |",
"       | [                  U          |",
"       | [                  N          |",
"       | !                  I          |",
"       | [                  T          |",
"       | [                  E          |",
"       | }                  D          |",
"       |                               |",
"       |                               |",
"       | {                  S          |",
"       | [                  T          |",
"       | :                  A          |",
"       | [                  T          |",
"       | [                  E          |",
"      /| {  /|              S    |\\    |",
"     | |   | |                   | |   |",
"     | |   | |                   | |   |",
"     | |   | |                   | |   |",
"     |_|___|_|___________________|_|___|",
"     | |   | |                   | |   |\\",
"     | |___| |___________________| |___|]",
"     | |###| |###################| |###|]",
"     | |###| |###################| |###|]",
"     | |###| |\"\"\"\"\"\"\"\"\"\"#########| |\"\"\"|]",
"     | |###| |         |#########| |   |]",
"      \\|####\\|---------|#########|/----|]",
"       |#####|         |#########|     |/",
"       |#####|         |#########|     |",
"      /]##### |        | ######## |    [\\",
"      []##### |        | ######## |    []",
"      []##### |        | ######## |    []",
"      []##### |        | ######## |    []",
"      []##### |        | ######## |    []",
"       |#####|---------|#########|-----|",
"       |#####|         |#########|     |",
"       |#####|         |##H######|     |",
"       |#####|         |##H######|     |",
"       |#####|         |##H######|     |",
"       |#####|_________|##H######|_____|",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |     ####\"\"\"\"\"\"\"  H            |",
"       |     ####\"\"\"\"\"\"\"  H            |",
"       |     \"\"\"\"\"\"\"\"\"\"\"  H            |",
"       |     \"\"\"\"\"\"\"\"\"\"\"  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |                  H            |",
"       |__________________H____________|",
"       |                  H            |",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       I||||||||||||||||||H||||||||||||I",
"       |#####|         |##H######|     |",
"       |#####|         |##H######|     |",
"       |#####|  H   H  |##H######|   H |",
"       |#####|  H   H  |##H######|   H |",
"       |#####|  H   H  |##H######|   H |",
"       |#####|  \\h_dF  |##H######|   Vm|",
"       |#####|   `\"'   |##H######|    \"|",
"       |#####|         |##H######|     |",
"       |#####|  /###\\  |##H######|   /#|",
"       |#####|  #   '  |##H######|   # |",
"       |#####|  \\###\\  |##H######|   \\#|",
"       |#####|  .   #  |##H######|   . |",
"       |#####|  \\###/  |##H######|   \\#|",
"       |#####|         |##H######|     |",
"       |#####|    H    |##H######|     [",
"       |#####|   dAh   |##H######|    H|",
"       |#####|  dF qL  |##H######|   dF|",
"       |#####|  HhmdH  |##H######|   Hm|",
"       |#####|  H   H  [%]H#apx##|   H |",
"       |#####|         |##H######|     |",
"       |#####A         |##H######A     |",
"       |####| |        |##H#####|#|    |",
"       |####| |        |##H#####|#|    |",
"       |###|   |       |##H####|###|   |",
"       |###|   |       |##H####|###|   |",
"       |##|     |      |##H###|#####|  |",
"       |#-|     |      |##H###|#####|-_|",
"    _-\"==|       |     |##H##|#######|==\"-_",
" _-\"=[]==|       |     |##H##|#######|==[]=\"-_",
"|========|_______|_____|##H##|#######|========|",
"!=======|=========|____|##H#|=========|=======!",
"        !=========! /#####\\ !=========!",
"         /#######\\ /#######\\ /#######\\",
"        d#########V#########V#########h",
"        H#########H#########H#########H",
"       |###########H#######H###########|",
"       |###########|\"\"\"\"\"\"\"|###########|",
"        \"\"\"\"\"\"\"\"\"\"\"         \"\"\"\"\"\"\"\"\"\"\"",
};

