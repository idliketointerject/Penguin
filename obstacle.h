#ifndef OBSTACLE_H
#define OBSTACLE_H

class obstacle{
public:

	int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);
	int x0;
	int width;
	int height;
	int y0;
	//nothing yet
};
#endif
