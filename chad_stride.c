#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h> // usleep
#include <string.h> // strlen
#include <signal.h>
#include <stdbool.h>

#define CHAD_FRAMES 7
#define CHAD_ROWS   24

#define AVG_CHAD_WIDTH 25

#define DEFAULT_SIZE 1

bool STAY = false, LOOP = false, NOFUCKS = false, COLOR = false;
long SLEEP_TIMER = 150000;
int SIZE = DEFAULT_SIZE, PAIR = 1;

const char* ARG_FLAGS = "slfhb:a:c:";

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
    printf("./chad_stride -[flags]\n"
            "-s: Chad stays still and doesn't move forever\n"
            "-l: Chad walks infinitely\n"
            "-b SIZE: Big Chad (each b increases chad)\n"
            "-f: Chad gives no fucks (ignores signals)\n"
            "-a SLEEP_TIME: Adjust sleep timer for chad\n"
            "-c COLOR: Chad strolls by in the color of your choice (r|g|b|m|c|y)\n"
            "-h: This message\n");
    exit(exit_code);
}

int get_color_pair(char c, int pair){
    switch (c){
        case 'w':
            return 1;
        case 'b':
            return 2;
        case 'r':
            return 3;
        case 'g':
            return 4;
        case 'c':
            return 5;
        case 'y':
            return 6;
        case 'm':
            return 7;
        default:
            return pair;
    }
} 

long arg_to_long(char* arg) {
    char* p_end;
    long modifier = strtol(optarg, &p_end, 10);
    if (p_end == optarg) {
        fprintf(stderr, "Invalid digits for flag -b\n");
        usage(1);
    }
    return modifier;
}

void handle_args(int argc, char *argv[]) {
    char c;
    while ((c = getopt(argc, argv, ARG_FLAGS)) != -1) {
        switch (c) {
            case 's':
                STAY = true;
                break;
            case 'l':
                LOOP = true;
                break;
            case 'b': {
                          long modifier = arg_to_long(optarg);
                          if (modifier < 0) {
                              fprintf(stderr, "Error: invalid argument -b. Must be positive!\n");
                          }
                          SIZE += modifier; 
                          break;
                      }
            case 'f':
                      NOFUCKS = true;
                      break;
            case 'a': {
                          long modifier = arg_to_long(optarg);
                          if (modifier < 0) {
                              fprintf(stderr, "Error: Access flag isn't positive!\n");
                          }
                          SLEEP_TIMER = modifier;
                          break;
                      }
            case 'c':
                      COLOR = true;
                      /* check ascii char val a-z */
                      if ( ((unsigned char) *optarg) > 96 && ((unsigned char) *optarg) < 173) {
                          PAIR = get_color_pair(*optarg, PAIR);
                      } else {
                          fprintf(stderr, "Error: invalid color value. Must be (w|r|g|b|m|c|y)\n\n");
                          usage(1);
                      }
                      break;
            case 'h':
                      usage(0);
            default:
                      usage(1);
        }
    }
}


int main(int argc, char *argv[]) {
    handle_args(argc, argv);

    // set signals
    if (NOFUCKS) {
        signal(SIGHUP , SIG_IGN);
        signal(SIGINT , SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
    }

    /* ncurses stuff */
    int col, row;
    initscr();

    /* start color if term supports it */
    if (COLOR && has_colors()) start_color();

    getmaxyx(stdscr, row, col); // stdscr is default screen
    // center chad if stay is set
    int x_pos = STAY ? (col / 2) - (AVG_CHAD_WIDTH / 2): 0;
    int i = 0;
    noecho();
    curs_set(0);
    nodelay(stdscr, 1);
    leaveok(stdscr, 1);
    scrollok(stdscr, 0);

    /* initialize colors */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

    /* loop until done */
    while(x_pos < col || LOOP) {
        // call this just in case resize of term
        getmaxyx(stdscr, row, col);
        /* set color */
        attron(COLOR_PAIR(PAIR));

        // check for wrap on loop
        if (x_pos >= col) x_pos = 0;

        for (int j = 0; j < CHAD_ROWS; j++) {
            // find position of furthest character to the right
            int right_pos = x_pos + strlen(chad_frames[i % CHAD_FRAMES][j]);
            // draw row, checking it doesn't go off screen if not looping
            mvaddnstr(j * SIZE + row/2 - CHAD_ROWS/2, x_pos, chad_frames[i % CHAD_FRAMES][j],
                    (right_pos > col && !LOOP) ? col - x_pos : right_pos);
        }

        i++; // increment animation counter
        if (!STAY) x_pos++; // move across screen

        /* Ncurses stuff */
        refresh();

        /* Color stuff */
        char c = getch();

        if (COLOR && has_colors()){
            PAIR = get_color_pair(c, PAIR);
        }

        clear();

        /* animation wait */
        usleep(SLEEP_TIMER);
    }

    /* Clean up */
    delwin(stdscr);
    endwin();
    refresh();

    return 0;
}
