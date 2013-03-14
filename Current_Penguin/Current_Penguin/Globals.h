#pragma once

// Display Constants
const int WIDTH = 1280;
const int HEIGHT = 700;
const int FPS = 60;
const float PI = 3.14;

// Sound Constants
const int NUM_SAMPLES = 2;

// Enumerations
enum KEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ENTER };
enum STATE { TITLE, PLAYING, HELP, ENDGAME };

// Game Constants
const int NUM_ENEMIES = 5;
const int NUM_OBSTACLES = 10;
const int NUM_BULLETS = 15;
const int HEALTH_OBSTACLE = 3;