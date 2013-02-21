#include "screenprinter.h"

screenprinter::screenprinter(char* name){
	setXPos(WIDTH/2);
	setYPos(HEIGHT/2);
	fontName = name;
}
ALLEGRO_FONT* screenprinter::getFontPointer(){
	fontPointer = al_load_font(fontName,getTextSize(),0);
	return fontPointer;
}
screenprinter::~screenprinter(){
	if( fontPointer )
	{
		al_destroy_font(fontPointer);
	}
}
void screenprinter::printText(char* message){
	al_draw_textf(getFontPointer(),al_map_rgb(255,255,255),getXPos(), getYPos(), 0, "%s", message);
}