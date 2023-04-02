/**
 * @file comm_motor.h
 * @author Hernanda @hernanda16, Indra, Isabelle
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ros/ros.h"
#include "modbus.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>

#define NUM_REGISTER 2
//---> Global variables
ros::Timer timer_40Hz;

//---> Motor variables
char key;
modbus_t *ctx;
uint16_t address = 0x0A02;

uint16_t registers[NUM_REGISTER];
int rc;
int speed = 100;

//--------------------------------------------------

//---> Prototypes
void CllbckTimer40Hz(const ros::TimerEvent &event);

int CommMotorInit();
int CommMotorRoutine();

//---> Motor Prototypes
int write(int rc, modbus_t *ctx, uint8_t slave_id, int speed);
int read(int rc, modbus_t *ctx, uint8_t slave_id, uint16_t address, int num_registers, uint16_t *registers);
void inkey();
uint8_t kbhit();
