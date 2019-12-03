#include "tasks.h"

MOTOR_t SCA[3];

/* Variable defines --------------------------------------------------------------*/
SCA_Handler_t *pSCA_ID1 = NULL; //读写指针，可用于获取执行器参数或调用FAST型函数
SCA_Handler_t *pSCA_ID2 = NULL;
SCA_Handler_t *pSCA_ID3 = NULL;

/* CAN端口信息定义，用于绑定SCA句柄，实现多端口控制。移植时根据实际数量定义，默认使用2个 */
CAN_Handler_t CAN_Port1, CAN_Port2;

void init_task(void)
{
    init_task_hardware();
    init_task_controller();
    init_task_innfos();
}

/**
	* @Function:	Initialize the onboard peripherals
	* @Parameter:	none
	* @Return:		none
	* @Attention:	none
*/
void init_task_hardware(void)
{
    HAL_Init(); 
    Stm32_Clock_Init(360,25,2,8);
    delay_init(180);
    uart_init(115200);
    LED_Init();
    LCD_Init();
		CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_8TQ,6,CAN_MODE_LOOPBACK); //CAN³õÊ¼»¯,²¨ÌØÂÊ500Kbps 
}

/**
	* @Function:	Initialize low-level controller structure and configure parameters
	* @Parameter:	none
	* @Return:		none
	* @Attention:	none
*/
void init_task_controller(void)
{
    MOTOR_init(&SCA[0], MOTOR_POSITION_MODE);
    MOTOR_init(&SCA[1], MOTOR_POSITION_MODE);
    MOTOR_init(&SCA[2], MOTOR_POSITION_MODE);

    MOTOR_set_vel_loop_gain(&SCA[0], 1.0f, 0.0f);
    MOTOR_set_vel_loop_limit(&SCA[0], 0.0f, 0.0f);
    MOTOR_set_pos_loop_gain(&SCA[0], 1.0f, 0.0f, 0.0f);
    MOTOR_set_pos_loop_limit(&SCA[0], 0.0f, 0.0f);

    MOTOR_set_vel_loop_gain(&SCA[1], 1.0f, 0.0f);
    MOTOR_set_vel_loop_limit(&SCA[1], 0.0f, 0.0f);
    MOTOR_set_pos_loop_gain(&SCA[1], 1.0f, 0.0f, 0.0f);
    MOTOR_set_pos_loop_limit(&SCA[1], 0.0f, 0.0f);

    MOTOR_set_vel_loop_gain(&SCA[2], 1.0f, 0.0f);
    MOTOR_set_vel_loop_limit(&SCA[2], 0.0f, 0.0f);
    MOTOR_set_pos_loop_gain(&SCA[2], 1.0f, 0.0f, 0.0f);
    MOTOR_set_pos_loop_limit(&SCA[2], 0.0f, 0.0f);
}

/**
	* @Function:	Initialize structures of innfos actuator, then enable the actuator
	* @Parameter:	none
	* @Return:		none
	* @Attention:	none
*/
void init_task_innfos(void)
{
    /* 初始化CAN端口参数 */
    CAN_Port1.CanPort = 1;          //标记端口号
    CAN_Port1.Retry = 2;            //失败重发次数
    CAN_Port1.Send = CAN1_Send_Msg; //CAN1端口发送函数

    /* 装载执行器的ID与所使用的CAN端口号 */
    setupActuators(3, &CAN_Port1); //ID1 绑定CAN1

    /* 获取ID1和2的参数句柄 */
    pSCA_ID3 = getInstance(3);

    /* 启动所有执行器 */
    enableAllActuators();

    /* 设置驱动器工作模式 */
    activateActuatorMode(0x03, SCA_Current_Mode, Block);
}

/**
	* @Function:	Get motor data, calculate PID output, send control data
	* @Parameter:	none
	* @Return:		none
	* @Attention:	Because the communication with the motor usually takes a lot of time,
                    so it is better to add the task scheduling function or real-time system 
                    for the MCU.
*/
void ctrl_task(void)
{
    // getVelocityFast(pSCA_ID1, Block);
    // getPositionFast(pSCA_ID1, Block);
    // getVelocityFast(pSCA_ID2, Block);
    // getPositionFast(pSCA_ID2, Block);
    // getVelocityFast(pSCA_ID3, Block);
    // getPositionFast(pSCA_ID3, Block);

    // MOTOR_set_fbk(&SCA[0], 0.0f, pSCA_ID1->Velocity_Real, pSCA_ID1->Position_Real);
    // MOTOR_set_fbk(&SCA[1], 0.0f, pSCA_ID2->Velocity_Real, pSCA_ID2->Position_Real);
    // MOTOR_set_fbk(&SCA[2], 0.0f, pSCA_ID3->Velocity_Real, pSCA_ID3->Position_Real);

    // MOTOR_calc(&SCA[0]);
    // MOTOR_calc(&SCA[1]);
    // MOTOR_calc(&SCA[2]);

    // setCurrentFast(pSCA_ID1, MOTOR_get_cmd(&SCA[0]));
    // setCurrentFast(pSCA_ID2, MOTOR_get_cmd(&SCA[0]));
    // setCurrentFast(pSCA_ID3, MOTOR_get_cmd(&SCA[0]));

    setCurrentFast(pSCA_ID3, 1.0f);
}

/**
	* @Function:	Background tasks
	* @Parameter:	none
	* @Return:		none
	* @Attention:	Background task is the while loop in main.c
*/
void loop_task(void)
{
    //float t;
    //int c;

    while (1)
    {
        ctrl_task();
        /*c++;
        t = Time_s + Time_ms / 1000.0f;
        if (t > 3.0f)
        {
            c = 0;
            t -= 3.0f;
            //printf("tps:%.1f", c / 3.0f);
        }*/
    }
}
