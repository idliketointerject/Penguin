#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
 
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *background = NULL;
   ALLEGRO_BITMAP *penguin = NULL;
   ALLEGRO_SAMPLE *bgm=NULL;
   float background_offset = 0;
   float penguin_x = SCREEN_W / 2.0 - 130 / 2.0;
   float penguin_y = SCREEN_H / 2.0 - 100 / 2.0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize al_init_image_addon!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 
      if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   bgm = al_load_sample( "resources/audio/bgm.wav" );
 
   if (!bgm){
      printf( "BGM not loaded!\n" ); 
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   background = al_load_bitmap("resources/images/background.jpg");
   if(!background) {
      fprintf(stderr, "failed to create background bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   penguin = al_load_bitmap("resources/images/penguin.png");
   if(!penguin) {
      fprintf(stderr, "failed to create penguin bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(penguin);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_draw_bitmap(background,0,0,0);

   al_flip_display();
 
   al_start_timer(timer);
 
   /* Loop the sample until the display closes. */
   al_play_sample(bgm, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP] && penguin_y >= 8.0) {
            penguin_y -= 8.0;
         }
 
         if(key[KEY_DOWN] && penguin_y <= SCREEN_H - 100 - 6.0) {
            penguin_y += 8.0;
         }
 
         if(key[KEY_LEFT] && penguin_x >= 8.0) {
            penguin_x -= 6.0;
         }
 
         if(key[KEY_RIGHT] && penguin_x <= SCREEN_W - 130 - 6.0) {
            penguin_x += 6.0;
         }
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		 
		 if(penguin_x < 160){
			background_offset -= 14.0;
		 }
		 else if(penguin_x < 320){
			background_offset -= 16.0;
		 }
		 else if(penguin_x < 480){
			background_offset -= 18.0;
		 }
		 else{
			background_offset -= 20.0;
		 }
		 
		 if(background_offset < -1279){
			 background_offset += 1280;
		 }

		 al_draw_bitmap(background,background_offset,0,0);

         al_draw_bitmap(penguin,penguin_x,penguin_y,0);
 
         al_flip_display();
      }
   }
 
   al_destroy_bitmap(penguin);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}