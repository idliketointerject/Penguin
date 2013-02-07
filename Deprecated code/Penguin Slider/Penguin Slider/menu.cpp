/*void mainmenu() {
 
        //added: missing 2nd parameter
        //BITMAP* title_screen_bitmap = load_bitmap("title.bmp", NULL); //The title screen bitmap.
        BITMAP *title_screen_bitmap = create_bitmap(SCREEN_W, SCREEN_H);
 
        #define MIN_MENU_SEL 0
        #define MAX_MENU_SEL 2  
 
        int menusel = MIN_MENU_SEL;
        while (gamestate == GAME_STATE_INTRO) {
                // INPUT ROUTINE
                //changed: fixed various syntax errors in the next few lines
                if (keypressed()) {
                        int k = readkey();
                        //changed: now uses KEY_* vars
                        switch (k >> 8) {
                                case KEY_ESC: gamestate = GAME_STATE_INTRO; break; //escape
                                case KEY_UP: menusel--; if (menusel < MIN_MENU_SEL) menusel = MIN_MENU_SEL; break;
                                case KEY_DOWN: menusel++; if (menusel > MAX_MENU_SEL) menusel = MAX_MENU_SEL; break;
                                case KEY_ENTER:
                                switch (menusel) {
                                        case 0: {gamestate = GAME_STATE_MAINGAME; install_int_ex(increment_speed_counter, BPS_TO_TIMER(MAX_FPS));} 
                                        break;
                                        case 1: gamestate = GAME_STATE_ABOUT; 
                                        break;
                                        case 2: gamestate = GAME_STATE_FINISH; 
                                        break;
                                } break;
                        }
                        clear_keybuf();
                }
 
                // DRAWING ROUTINE
                // draw background
                blit(title_screen_bitmap, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
 
                // draw menu
                if (menusel == 0) { // play
                        textprintf_ex(buffer, font, 20,  80, makecol(0,255,255), -1, "Play Game");
                } else {
                        textprintf_ex(buffer, font, 20,  80, makecol(255,255,255), -1, "Play Game");
                }
                if (menusel == 1) { // about
                        textprintf_ex(buffer, font, 20,  90, makecol(0,255,255), -1, "About Game");
                } else {
                        textprintf_ex(buffer, font, 20,  90, makecol(255,255,255), -1, "About Game");
                }
                if (menusel == 2) { // exit
                        textprintf_ex(buffer, font, 20,  100, makecol(0,255,255), -1, "Exit Game");
                } else {
                        textprintf_ex(buffer, font, 20,  100, makecol(255,255,255), -1, "Exit Game");
                } // added
 
                //draw game state (temporary, just till we get some real game action)
                rectfill (buffer, 0, 0, screen->w, 10, 0);
                switch (gamestate)
                {
                        case (GAME_STATE_INTRO): {textprintf_right_ex(buffer, font, screen->w,  0, makecol(255,255,255), -1, "Intro"); break;}
                        //no longer needed cause of the debug coords... :)
                        //case (GAME_STATE_MAINGAME): {textprintf_right_ex(buffer, font, screen->w,  0, makecol(255,255,255), -1, "Main game"); break;}
                        case (GAME_STATE_GAMEOVER): {textprintf_right_ex(buffer, font, screen->w,  0, makecol(255,255,255), -1, "Game Over"); break;}
                        case (GAME_STATE_ABOUT): {textprintf_right_ex(buffer, font, screen->w,  0, makecol(255,255,255), -1, "About");break;}
                }
 
                // draw to screen
                blit(buffer, screen, 0,0, 0,0, SCREEN_WIDTH,SCREEN_HEIGHT);
        }
 
        destroy_bitmap(title_screen_bitmap);
        return;
}
*/