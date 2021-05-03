#ifndef _UDP_H__
#define _UDP_H__

//int main_control();
int action_cmd(int id, int val=0,int time=0);
void aruco_cmd(int action, int id, int roll=0, int pitch=0, int yaw=0);
bool get_control_mode();
void set_control_mode();
bool get_aruco_ok();
void set_aruco_ok();
#endif

