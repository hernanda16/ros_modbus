/**
 * @author Hernanda, Indra Mahendra, Isabelle;
 * @brief this Program will only work with libmodbus library;
 * Datasheets:
 * - 
 * Documentation  
 * - https://github.com/hernanda16/libmodbus
 * 
 * April-2-2023
 **/

#include "ros/ros.h"
#include <iostream>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "comm_stm");
    ros::NodeHandle NH;
    ros::MultiThreadedSpinner spinner(0);

    spinner.spin();
}
