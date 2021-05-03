#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <string.h>
//#include <arpa/inet.h>
//#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <iostream>
#include <pthread.h>
#include "crc.h"
#include "cJSON.h"
#include "ftp_client.h"
#include "tcp_client.h"
#include <ws2tcpip.h>
#include "proto.h"
#include "udp.h"
#include<iostream>
#include<cstring>

#define 校准 CMD_ACC 
#define 起飞 CMD_TAKEOFF 
#define 降落 CMD_LAND 
#define 上升 CMD_UP 
#define 向左 CMD_LEFT 
#define 下降 CMD_DOWN 
#define 向右 CMD_RIGHT 
#define 前进 CMD_FORWARD 
#define 向后 CMD_BACK 
#define 拍照 CMD_TAKE_PHOTO 
#define 定高 CMD_TOF_ALT 
#define 射击 CMD_SHOOT 
#define 起飞高度 CMD_TAKEOFF_ALTH
#define 向左旋转 CMD_LEFT_YAW
#define 向右旋转 CMD_RIGHT_YAW
#define 等待(t) Sleep(t)
#define 要求(c) action_cmd(c);
#define 要求高度(up,height) action_cmd(up,height);
#define 要求动作(action,power,length) action_cmd(action,power,length);
#define 起飞许可() TAKEOFF()
#define 九十度 1300
#define 四十五度 650
#define 如果不 else
#define 如果 if
#define 真 true
#define 存在 ==
#define 报告(text) printf(text);
#define 向左旋转 TURNLEFT()
#define 向右旋转 TURNRIGHT()


static bool TAKEOFF()
{
	action_cmd(CMD_TAKEOFF);
	if (get_control_mode() == true && batt_get_cap() > 20) {
		set_control_mode();
		return true;
	}
	return false;
}

inline static bool TURNRIGHT()
{
	action_cmd(CMD_RIGHT_TURN, 60, 0);
	return true;
}
inline static bool TURNLEFT()
{
	action_cmd(CMD_LEFT_TURN, 60, 0);
	return true;
}
/*******************************************************
action_cmd(cmd,val,time)

 cmd:控制命令如下：
	CMD_ACC,                 //校准
	CMD_TAKEOFF,             //起飞
	CMD_LAND,                //降落
	CMD_FORWARD_TURN,        //前翻
	CMD_BACK_TURN,           //后翻
	CMD_LEFT_TURN,           //左翻
	CMD_RIGHT_TURN,          //右翻
	CMD_UP,                  //上升
	CMD_DOWN,                //下降
	CMD_LEFT,                //向左
	CMD_RIGHT,               //向右
	CMD_FORWARD,             //向前
	CMD_BACK,                //向后
	CMD_LEFT_YAW,            //左旋
	CMD_RIGHT_YAW,           //右旋
	CMD_TAKE_PHOTO,          //拍照
	CMD_TOF_ALT,             //定高
	CMD_TAKEOFF_ALTH,        //起飞高度
	CMD_MODE_CHANGE,         //模式切换
	CMD_SHOOT,               //射击

 val:动力值或者高度值，例如定高和起飞高度命令需要高度值(厘米),前后左右命令为动力值（0-100）

 time:每个动作执行时间(ms)

注意：
前后左右每条指令都要加延时，飞机需要时间自稳,时间越长，效果越好
动力越小，指令执行时间要越大
*******************************************************************/

void action_start()
{
	if (TAKEOFF() == true) {            //起飞
		printf("起飞成功\n");
		Sleep(2000);


		/*****

	注意：
	无人机实地飞行示例，实际环境及每个飞机可能需要微调。
	每次飞行后加延时，需要时间自稳, 时间越长，效果越好
		向前后上下左右，旋转。中间的数字参数代表速度0-100.   100代表最快
	*******************************************************************/


		action_cmd(CMD_TAKEOFF);        //起飞
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_FORWARD, 100, 150);  //向前
		Sleep(3000);
		action_cmd(CMD_LEFT, 100, 320);    //向左
		Sleep(3000);

		action_cmd(CMD_SHOOT);          //射击
		Sleep(3000);

		action_cmd(CMD_RIGHT, 100, 0);    //向右
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_SHOOT);          //射击
		Sleep(3000);

		action_cmd(CMD_RIGHT, 100, 100);    //向右
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_FORWARD, 100, 700);  //向前
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_LEFT_YAW, 100, 1300);    //向左转90度
		Sleep(3000);

		action_cmd(CMD_LEFT_YAW, 100, 1300);    //向左转90度
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_BACK, 100, 100);    //向后
		Sleep(3000);

		action_cmd(CMD_SHOOT);          //射击
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_RIGHT, 100, 800);    //向右
		Sleep(3000);
		action_cmd(CMD_SHOOT);          //射击
		Sleep(3000);
		action_cmd(CMD_RIGHT, 100, 100);    //向右
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_FORWARD, 100, 700);  //向前
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //定高150厘米

		action_cmd(CMD_LEFT, 100, 700);    //向左
		Sleep(3000);

		action_cmd(CMD_BACK, 100, 200);    //向后
		Sleep(3000);
		action_cmd(CMD_RIGHT_YAW, 100, 1350);    //向右转90度
		Sleep(3000);

		action_cmd(CMD_TAKE_PHOTO);     //拍照
		Sleep(3000);

		action_cmd(CMD_LEFT, 100, 400);    //向左
		Sleep(3000);

		action_cmd(CMD_FORWARD, 100, 250);    //向前
		Sleep(3000);

		action_cmd(CMD_LAND);           //降落


	//	action_cmd(CMD_SHOOT);          //射击
	//	action_cmd(CMD_TAKE_PHOTO);     //拍照
	//  Sleep(1000);                    //延时1s
	//	action_cmd(CMD_TOF_ALT,150);    //定高150厘米
	//	action_cmd(CMD_LEFT,50,1000);     //向左
	//	Sleep(2000);
	//	action_cmd(CMD_FORWARD,20,1000);  //向前
	//	Sleep(2000);
	//	action_cmd(CMD_BACK,50,2000);     //向后
	//	Sleep(2000);
	//	action_cmd(CMD_UP,50,2000);       //向上
	//	Sleep(2000);
	//	action_cmd(CMD_DOWN,20,1000);     //向下
	//	Sleep(2000);
	//	action_cmd(CMD_RIGHT,20,1000);    //向右
	//	action_cmd(CMD_LEFT_YAW,50,1000);   //左转
	//	action_cmd(CMD_RIGHT_YAW,50, 1000);  //右转
	//	Sleep(3000);
	//	action_cmd(CMD_LAND);           //降落
	}
	else {
		printf("起飞失败\n");
	}
}

void defa()
{
	如果 (起飞许可() 存在 真)
	{
		报告("起飞成功\n");
		等待(2000);
		要求高度(定高, 150);
		等待(3000);
		要求动作(前进, 30, 100); //前进100厘米,30%动力
		等待(3000);
		要求(射击);
		要求动作(向左旋转, 30, 九十度);
		向左旋转;
		拍照;
		要求(降落);
	}
	如果不
	{
		报告("发生了异常");
	}
}
