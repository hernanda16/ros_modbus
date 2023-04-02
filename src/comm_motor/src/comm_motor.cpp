#include "comm_motor/comm_motor.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "comm_motor");

    ros::NodeHandle NH;
    ros::AsyncSpinner AS(0);

    //=====Timer
    timer_40Hz = NH.createTimer(ros::Duration(0.02), CllbckTimer40Hz);

    if (CommMotorInit() == -1)
        ros::shutdown();

    AS.start();
    ros::waitForShutdown();

    timer_40Hz.stop();
}

//---> Timer callback functions
//==============================================================================

void CllbckTimer40Hz(const ros::TimerEvent &event)
{
    if (CommMotorRoutine() == -1)
        ros::shutdown();
}

//---> Node functions
//==============================================================================
int CommMotorInit()
{
    return 1;
}

int CommMotorRoutine()
{
}

int write(int rc, modbus_t *ctx, uint8_t slave_id, int speed)
{
    ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
    if (ctx == NULL)
    {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        return -1;
    }
    modbus_set_slave(ctx, slave_id);

    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Failed to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx); // membebaskan koneksi slave
        return -1;
    }

    rc = modbus_write_register(ctx, 514, speed);
    if (rc == -1)
    {
        fprintf(stderr, "Failed to write register: %s\n", modbus_strerror(errno));
        return -1;
    }
    else
    {
        printf("Slave %d || Value %d written to register\n", slave_id, speed);
        sleep(0.2);
        printf("%d", speed);
    }
    modbus_close(ctx);
    modbus_free(ctx);
    return 1;
}

int read(int rc, modbus_t *ctx, uint8_t slave_id, uint16_t address, int num_registers, uint16_t *registers)
{
    ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
    if (ctx == NULL)
    {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        return -1;
    }
    modbus_set_slave(ctx, slave_id);

    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Failed to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx); // membebaskan koneksi slave
        return -1;
    }

    rc = modbus_read_registers(ctx, address, num_registers, registers);
    if (rc == -1)
    {
        fprintf(stderr, "Failed to read register: %s\n", modbus_strerror(errno));
        return -1;
    }
    else
    {
        for (int i = 0; i < num_registers; i++)
        {
            printf("Slave %d || Register %d = %d\n", slave_id, address + i, registers[i]);
        }
        sleep(0.2);
    }
    modbus_close(ctx);
    modbus_free(ctx);
    return 1;
}

void inkey()
{
    static struct termios oldt;
    static struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);               // disable buffering
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new settings
    key = getchar();                         // read character (non-blocking)
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
}

uint8_t kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized)
    {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}