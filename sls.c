#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

const int r_mid = 23;
const int r_length = 185;
const int r_tail = 0;
const int r_shake = 5;
const double r_a = 0.2;
const int fps = 100;
char *rocket[];
char *blank;

const int num_exhausts = 1000;
const char *exhaust_chars = "*";
const int num_exhaust_chars = 1;
const int exhaust_speed = 4;

struct exhaust {
	int x, y, xv;
	char c;
};

void display(int pos, int offset, int h, struct exhaust *exhausts) {
	int i;
	for(i = 0; i < h && i + pos < r_length; i++) {
		mvprintw(i, 0, blank);
		mvprintw(i, offset, "%s", rocket[i + pos]);
	}
	for(; i < h; i++) {
		mvprintw(i, 0, blank);
	}
	if(pos + h > r_length) {
		for(i = 0; i < num_exhausts; i++) {
			mvprintw(r_length - pos + exhausts[i].y,
				offset + exhausts[i].x + r_mid, "%c",
				exhausts[i].c);
		}
	}
	refresh();
}

void update_exhausts(struct exhaust *exhausts, int h, int v) {
	int i;
	for(i = 0; i < num_exhausts; i++) {
		exhausts[i].y += exhaust_speed + v;
		exhausts[i].x += exhausts[i].xv;
		if(exhausts[i].y > h * 2 || exhausts[i].c == '\0' || (rand() % 5 == 0)) {
			exhausts[i].y = rand() % 20;
			exhausts[i].x = rand() % 26 - 13;
			exhausts[i].xv = rand() % 3 - 1;
			exhausts[i].c = exhaust_chars[rand() % num_exhaust_chars];
		}
	}
}

void rocket_launch(int w, int h) {
	int offset = w / 2 - r_mid;
	int t = 0;
	const int sleep = 1000000 / fps;

	struct exhaust exhausts[num_exhausts];
	memset(exhausts, 0x00, sizeof(exhausts));

	const int wait_time = fps;
	while(t < wait_time) {
		display(0, offset + rand() % r_shake - (r_shake/2), h, exhausts);
		t++;
		usleep(sleep);
	}
	const double a = r_a / fps;
	double pos = 0;
	double v = 0;

	while((int)pos < r_length + r_tail + h) {
		update_exhausts(exhausts, h, (int) v);
		display((int)pos, offset + rand() % r_shake - (r_shake/2), h, exhausts);
		v += a;
		pos += v;
		usleep(sleep);
	}
}

void handler(int dummy) {
}

int main() {
	/* init sig handler */
	signal(SIGINT, handler);

	/* init rand */
	srand(time(NULL));

	/* init ncurses */
	int width, height;
	initscr();
	getmaxyx(stdscr, height, width);
	curs_set(0);

	/* init blank line */
	blank = malloc(width + 1);
	memset(blank, ' ', width);

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

