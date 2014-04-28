// Copyright 2013 Max Malmgren

// This file is part of DolphiiMote.

// DolphiiMote is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// DolphiiMote is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with DolphiiMote.  If not, see <http://www.gnu.org/licenses/>.

#include "../../Dolphiimote/Core/dolphiimote.h"
#include <stdio.h>
#include <Windows.h>

int state = 0;

void on_data_received(uint8_t wiimote_number, struct dolphiimote_wiimote_data *data, void *userdata)
{
  printf("wiimote %i: ", wiimote_number);

  if(data->button_state & dolphiimote_BUTTON_A)
  {
    printf("A ");

    if(state == 0)
    {
      state = 1;
      dolphiimote_enable_capabilities(wiimote_number, dolphiimote_CAPABILITIES_MOTION_PLUS);
    }

    dolphiimote_brief_rumble(wiimote_number);
  }

  if(data->button_state & dolphiimote_BUTTON_B)
  {
    printf("B ");
    if(state == 1)
    {
      state = 0;
      dolphiimote_enable_capabilities(wiimote_number, dolphiimote_CAPABILITIES_EXTENSION);
    }
  }

  if(data -> button_state & dolphiimote_BUTTON_DPAD_DOWN)
    printf("Down ");
  if(data -> button_state & dolphiimote_BUTTON_DPAD_RIGHT)
    printf("Right ");
  if(data -> button_state & dolphiimote_BUTTON_DPAD_LEFT)
    printf("Left ");
  if(data -> button_state & dolphiimote_BUTTON_DPAD_UP)
    printf("Up ");
  if(data -> button_state & dolphiimote_BUTTON_MINUS)
    printf("Minus ");
  if(data -> button_state & dolphiimote_BUTTON_PLUS)
    printf("Plus ");
  if(data -> button_state & dolphiimote_BUTTON_HOME)
    printf("Home ");
  if(data -> button_state & dolphiimote_BUTTON_ONE)
    printf("One ");
  if(data -> button_state & dolphiimote_BUTTON_TWO)
    printf("Two ");

  if(data->valid_data_flags & dolphiimote_ACCELERATION_VALID)
    printf("Acc: %02d %02d %02d\t", data->acceleration.x, data->acceleration.y, data->acceleration.z);

  if(data->valid_data_flags & dolphiimote_MOTIONPLUS_VALID)
    printf("Motion Plus: %04X%04X%04X\t", data->motionplus.yaw_down_speed, data->motionplus.pitch_left_speed, data->motionplus.roll_left_speed);

  if(data->valid_data_flags & dolphiimote_NUNCHUCK_VALID)
  {
    int c = data->nunchuck.buttons & dolphiimote_NUNCHUCK_BUTTON_C;
    int z = data->nunchuck.buttons & dolphiimote_NUNCHUCK_BUTTON_Z;
    printf("Nunchuck: C: %i, Z: %i, Acc: %02X%02X%02X Stick X: %i, Y: %i\t", c, z, data->nunchuck.x, data->nunchuck.y, data->nunchuck.z, data->nunchuck.stick_x, data->nunchuck.stick_y);
  }

  if(data->valid_data_flags & dolphiimote_CLASSIC_CONTROLLER_VALID)
  {

    int lx = data->classic_controller.left_stick_x;
    int ly = data->classic_controller.left_stick_y;
    int rx = data->classic_controller.right_stick_x;
    int ry = data->classic_controller.right_stick_y;
    int lt = data->classic_controller.left_trigger;
    int rt = data->classic_controller.right_trigger;

    printf("Classic: L:%02d,%02d R:%02d,%02d T:%02d,%02d\t",lx,ly,rx,ry,lt,rt);

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_A)
      printf("A");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_B)
      printf("B");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_X)
      printf("X");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_Y)
      printf("Y");

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_DPAD_LEFT)
      printf("DL");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_DPAD_RIGHT)
      printf("DR");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_DPAD_DOWN)
      printf("DD");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_DPAD_UP)
      printf("DU");

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_TRIGGER_LEFT)
      printf("LT");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_TRIGGER_RIGHT)
      printf("RT");

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_Z_LEFT)
      printf("LZ");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_Z_RIGHT)
      printf("RZ");

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_PLUS)
      printf("+");
    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_MINUS)
      printf("-");

    if(data->classic_controller.buttons & dolphiimote_CLASSIC_CONTROLLER_BUTTON_HOME)
      printf("H");
  }

  printf("\n");
}

void on_capabilities_changed(uint8_t wiimote, dolphiimote_capability_status *status, void *userdata)
{
  printf("wiimote %i capabilities:\n", wiimote);
  printf("Extension: ");

  switch(status->extension_type)
  {
    case dolphiimote_EXTENSION_NONE:
      printf("None");
      break;
    case dolphiimote_EXTENSION_NUNCHUCK:
      printf("Nunchuck");
      break;
    case dolphiimote_EXTENSION_CLASSIC_CONTROLLER:
      printf("Classic Controller");
      break;
    case dolphiimote_EXTENSION_CLASSIC_CONTROLLER_PRO:
      printf("Classic Controller Pro");
      break;
    case dolphiimote_EXTENSION_GUITAR_HERO_GUITAR:
      printf("Guitar");
      break;
    case dolphiimote_EXTENSION_GUITAR_HERO_WORLD_TOUR_DRUMS:
      printf("Drums");
      break;
  }

  printf("\n");

  printf("Available:");

  if(status->available_capabilities & dolphiimote_CAPABILITIES_MOTION_PLUS)
    printf(" MotionPlus");

  if(status->available_capabilities & dolphiimote_CAPABILITIES_EXTENSION)
    printf(" Extension");

  if(status->available_capabilities & dolphiimote_CAPABILITIES_IR)
    printf(" IR");

  printf("\n");

  printf("Enabled:");

  if(status->enabled_capabilities & dolphiimote_CAPABILITIES_MOTION_PLUS)
    printf(" MotionPlus");

  if(status->enabled_capabilities & dolphiimote_CAPABILITIES_EXTENSION)
    printf(" Extension");

  if(status->enabled_capabilities & dolphiimote_CAPABILITIES_IR)
    printf(" IR");
  
  printf("\n");

  Sleep(500);
  dolphiimote_set_reporting_mode(wiimote, 0x35);  
}

void on_log_received(const char* str, uint32_t size)
{
  printf_s(str);
}

void init_dolphiimote(dolphiimote_callbacks callbacks)
{
  int wiimote_flags;
  int i;
  wiimote_flags = dolphiimote_init(callbacks);  

  for(i = 0; i < dolphiimote_MAX_WIIMOTES; i++, wiimote_flags >>= 1)
  {
    if(wiimote_flags & 0x01)
      dolphiimote_determine_capabilities(i);
  }
}

int main()
{
  dolphiimote_callbacks callbacks = { 0 };  
  int loop = 0;

  callbacks.data_received = on_data_received;
  callbacks.capabilities_changed = on_capabilities_changed;
  callbacks.log_received = on_log_received;

  dolphiimote_log_level(dolphiimote_LOG_LEVEL_DEBUG);

  init_dolphiimote(callbacks);

  while(1)
  {
    dolphiimote_update();
    Sleep(10);
  }
  //dolphiimote_shutdown();
}