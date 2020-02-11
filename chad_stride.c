#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h> // usleep
#include <string.h> // strlen
#include <signal.h>

#define CHAD_FRAMES 7
#define CHAD_ROWS   24

int STAY = 0, LOOP = 0, SIZE = 1, NOFUCKS = 0;

/* Chad frames */

const char* chad_frames[CHAD_FRAMES][CHAD_ROWS] = {
    {
      "                          %",
      "                     .(....",
      "                  %......(",
      "              ,*........&",
      "           .#,.,,,,. .(",
      "         *.,.*,,,,&@/,%",
      "        /,,,,,,,,,,,,,,*",
      "        &,,((%.,,,,,,.#(*",
      "        &.,@.%,,,,,.(.*",
      "        .,..,.#*,,,,./.",
      "       /,,.@@/* ..,,,,/",
      "      @@@**@@@@@",
      "     @@@*@@...@@@",
      "   @@.@@***@@@......@@@",
      " @@...@@*********@@@...@@",
      " @@...@@@********@@ @@@",
      "@....@@@***@@@**@",
      " @@@@ @@******@@@",
      "     @******@@***@@",
      "     @...@@@  @@....@@*@@",
      " @@@@...@       @..@***@@",
      "@**@@@           @@***@",
      "@**@@              @@@",
      "@****@",
    },
    {
      "                         & /",
      "                     & ...%",
      "                 % ......%",
      "              (.........%",
      "           @.,,,,.%@@&",
      "         @,,,@.,,@(/@.&",
      "        /,,,..,,,,,,,,,.@",
      "        &,,*..*.,,,,.((.",
      "        &*, ,&,,,,,*@%@",
      "       ..,..,,./,,,,,.@",
      "       %,,,..*%@&#.,.*,",
      "      @@*****@@@",
      "     @********@@@",
      "     @*******@...@@",
      "   @@@********@@...@",
      "   @@.@@@*******@...@@",
      "     @@@*@@@@@**@.....@@",
      "     @********@@   @@@",
      "@@@  @@@***@@*@@@",
      "@@*@@.@@@@@@@@..@",
      "@@***@...@@@@...@",
      "@@*@@ @@@  @@.@@",
      "@@@      @@*****@",
      "         @@,,,,,,@@"
    },
    {
      "                       %...",
      "                   #...../",
      "               /........@",
      "            /,%######&%@",
      "          .,#,,,...(@%",
      "        %,,,,,,,,..,,,.",
      "        ,,,&./,,,,,,.#,,&",
      "        *,#*%%,,,,,,.#&",
      "       ...*../,,,,,.%@",
      "       %,,@,,,,,,,,,,,..",
      "     @@.,,,,,,,@ @&%",
      "  @*************@...@@",
      "  @@@@**********@@@.@@",
      "  @...@@******@@",
      "  @...@@******@@",
      "  @...@@******@@",
      "@@...@*****@@*@@",
      "@@...@**@****@@@",
      "  @@@@@@******@@",
      "   @@....@@@@@",
      "  @**@..@@@",
      "   @@***@",
      "   @@****@@",
      "     @*****@@"
    },
    {
      "                         (../",
      "                     /.....@",
      "                 %........(",
      "              //%#####%&/(",
      "           ,.,/,,,,..#%&",
      "          &,,,,.,,.,..,,,",
      "          .,.(,.,,,,,,.#.,#",
      "          .,@/*@,,,,,,,#(",
      "         #.,&,(,,,,,,,#@",
      "         .,,%,,,,,,,,,,,,",
      "      @@@,,,,,,,.@@ %,",
      "   @@.@@*********@@.@@",
      " @@.....@********@@.@@",
      "@.....@@@********@@...@",
      " @@...@@********@  @...@@",
      " @@.....@*******@  @...@@",
      "   @@....@@***@@",
      "     @@@@***@@@@",
      "      @@****@@@@",
      "     @..@@@@.....@@@***@@",
      "     @...@@@@@...@@***@",
      "   @@...@       @**@",
      " @@**@@@         @@",
      "   @@****@@"
    },
    {
      "                           /*%",
      "                       &....*",
      "                   (.......",
      "                %.........",
      "             /(.,,,,.../",
      "           ,,,@,,,.%@#@#",
      "          ,,,,,,,,,,,,,,.#",
      "          ,,(@(,.,,,,,%(/%",
      "          #,%#..,,,,,%.*&",
      "         %,,&,,*&,,,,,./",
      "        %.,,*@#/....,,,.#",
      "   @@.@@*@@@@@@@@",
      " @@.....@********@@",
      "@.....@@*********@@@",
      "@....@**********@...@@",
      " @@...@@********@@@.@@",
      " @@.....@@@***@@ @@.@@",
      "   @@@@@***@@@@@@...@@",
      "     @*****@**@@ @@@",
      "     @@@***@@@",
      "   @@.@@@@@.@@",
      " @@...@@ @@...@@",
      "@**@@@     @....@@@@",
      "@****@      @@*****@"
    },
    {
      "                       %..&",
      "                   %.....(",
      "               ,,........",
      "            #..**,/*, .",
      "         *.,,,,,%#/(,",
      "        *,,, .,,&@#.,,*",
      "       #,,.%#,,,,,,,,/,(",
      "       @,..%.&,,,,,,..",
      "       (@,%,#,,,,,/,.@",
      "      ,,,,.,,,.,,,,,,.#",
      "     @@,,,,,,.,  &,#*",
      "    @..@**@@@@@",
      "  @@...@*******@",
      "@@.....@*******@",
      "  @@....@@@****@",
      "     @@....@@@@@",
      "     @@@@@@****@",
      "     @@******@@.@@",
      "     @@***@@@@@.@@",
      "    @**@@@...@@@",
      "     @@@...@@",
      "       @...@@",
      "       @*****@@",
      "        @@@@@"
    },
    {
      "                     &..&",
      "                 (...../",
      "             /.........",
      "          (.*(((##/,.",
      "       ( ,,,,,&**(",
      "      ,,,, .,,#&/.,,(",
      "     #,, @&,,,,,,,,#,/",
      "     @,..&.%,,,,,,.*",
      "     /&,&,#,,,,,*..&",
      "    ,,,,.,,,.,,,,,,.%",
      "    &,,,,,,.,  &/&.",
      "  @@@*@@...@@*@@...@",
      "  @**@.....@@@.....@",
      "  @***@@........@@@",
      "@@.@@****@@@@@",
      "  @@@********@",
      "  @********@@",
      "  @**********@",
      "  @***@@***@@@",
      "  @...@@@....@",
      "  @...@@*@@@@",
      "@@...@  @****@",
      "@@@@@@  @****@",
      "@@******@"
  }
};

void usage(const int exit_code) {
  printf("./cchad -[flags]\n"
"-s: Chad stays still and doesn't move forever\n"
"-l: Chad walks infinitely\n"
"-b: Big Chad (each b increases chad)\n"
"-f: Chad gives no fucks (ignores signals)\n"
"-h: This message\n");
  exit(exit_code);
}

void arg_parse(char* arg) {
  arg ++;
  while (*arg != '\0') {
    switch (*arg++) {
      case 's':
        STAY = 1;
        break;
      case 'l':
        LOOP = 1;
        break;
      case 'b':
        SIZE += 1;
        break;
      case 'f':
        NOFUCKS = 1;
        break;
      case 'h':
        usage(0);
      default:
        usage(1);
    }
  }
}

short get_color(char c, int pair){
    switch (c){
        case 'b':
            return 2;
        case 'y':
            return 6;
        case 'r':
            return 3;
        case 'c':
            return 5;
        case 'g':
            return 4;
        default:
            return pair;
    }
}

int main(int argc, char *argv[]) {

    /* Handle Arguments */
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-')
            arg_parse(argv[i]);
    }

    if (NOFUCKS) {
        signal(SIGHUP , SIG_IGN);
        signal(SIGINT , SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
    }

    /* ncurses stuff */
    int col, row;
    int x_pos = 0, i = 0;
    initscr();
    start_color();
    getmaxyx(stdscr, row, col); // stdscr is default screen
    noecho();
    curs_set(0);
    nodelay(stdscr, 1);
    leaveok(stdscr, 1);
    scrollok(stdscr, 0);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);

    int pair = 1;

    short old_color = COLOR_WHITE;
    /* loop until done */
    while(x_pos < col || LOOP) {
        attron(COLOR_PAIR(pair));

        // check for wrap on loop
        if (x_pos >= col) x_pos = 0;

        for (int j = 0; j < CHAD_ROWS; j++) {
            // find position of furthest character to the right
            int right_pos = x_pos + strlen(chad_frames[i % CHAD_FRAMES][j]);
            // draw row, checking it doesn't go off screen if not looping
            mvaddnstr(j * SIZE, x_pos, chad_frames[i % CHAD_FRAMES][j],
                      (right_pos > col && !LOOP) ? col - x_pos : right_pos);
        }

        i++; // increment animation counter
        if (!STAY) x_pos++; // move across screen

        /* Ncurses stuff */
        refresh();
        char c = getch();
        pair = get_color(c, pair);
        clear();

        /* animation wait */
        usleep(150000);
    }

    /* Clean up */
    delwin(stdscr);
    endwin();
    refresh();

    return 0;
}
