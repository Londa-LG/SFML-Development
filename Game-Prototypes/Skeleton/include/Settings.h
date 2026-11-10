#pragma once
#include <string>

struct Settings
{
  int width;
  int height;
  int frame_rate;
  bool full_screen;
  std::string title;
};

void init_settings(Settings &set);
void load_settings(Settings &set);
void save_settings(Settings &set);
