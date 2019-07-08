//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

//******************************************************************************
// File:   005_BNO055.h
// Author: Hans Desmet
// Comments: File handles BNO055 sensor
// Revision history: Version 01.00
// Date 26/12/2018
//******************************************************************************

#include <string.h>
#include <p24fxxxx.h> 
#include "---_Variables.h"
#include "005_BNO055.h"
#include "007_Uart.h"

extern VAR Mobit;
extern NonVolatile NonVolatileDATA;
extern void delay_ms(unsigned long val);

extern uint8_t Uart3_Buffer[64];
extern int16_t Uart3_Use_Len;
uint8_t Uart3_Read_Postion = 0;

uint8_t send_buf[64] = "";

void Uart3_Clear(void)
{
    memset(Uart3_Buffer,0,64);
    Uart3_Use_Len = 0;
    Uart3_Read_Postion = 0;
}
uint8_t Uart3_Getc(void)
{
    uint8_t try_cnt = 20;
    do{
        if((Uart3_Use_Len>0) && (Uart3_Use_Len>Uart3_Read_Postion)){
            //printf("%.2X\r\n", Uart3_Buffer[Uart3_Read_Postion]);
            return Uart3_Buffer[Uart3_Read_Postion++];
        }else{
            delay_ms(50);
        }
    }while(--try_cnt);
    printf("uart3 recv timeout\n");
    return 0;
}

static int16_t bno055_write_byte(uint8_t reg_addr, uint8_t reg_data)
{
	int16_t i = 0;
	uint8_t onebyte = 0;
	Uart3_Clear();
	memset(send_buf, 0, 64);
	
	send_buf[0] = 0xAA;
	send_buf[1] = 0x00;// WR
	send_buf[2] = reg_addr;
	send_buf[3] = 0x01;// LEN
	send_buf[4] = reg_data;
	// send data
	for (i=0; i<5; i++) {
		Uart3_Putc(send_buf[i]);
	}
	
	// wait
	delay_ms(20);
	
	onebyte = Uart3_Getc();
	
	if (0xEE == onebyte) {// NG ack response
        if (reg_addr != BNO055_SYS_TRIGGER) {
            onebyte = Uart3_Getc();
            if (onebyte != 0x01) {// 0x01 - WRITE_SUCCESS
                printf("write failure code: 0x%X\r\n", onebyte);
                return -1;
            }
        }
	} else {// invalid ack
		printf("receive invalid ack header: 0x%X\r\n", onebyte);
		return -1;
	}

	return 0;
}

static int16_t bno055_write_bytes(uint8_t reg_addr, uint8_t *p_in, uint8_t len)
{
	int16_t i = 0;
	uint8_t onebyte = 0;

	if ((!p_in) || (len<=0)) {
		return -1;
	}

	memset(send_buf, 0, 64);
	
	send_buf[0] = 0xAA;
	send_buf[1] = 0x00;// WR
	send_buf[2] = reg_addr;
	send_buf[3] = len;// LEN
	
	for (i=0; i<len; i++) {
		send_buf[4+i] = p_in[i];
	}

	// send data
	for (i=0; i<(len+4); i++) {
		Uart3_Putc(send_buf[i]);
	}
	
	// wait
	delay_ms(100);
	
	onebyte = Uart3_Getc();
	
	if (0xEE == onebyte) {// NG ack response
		onebyte = Uart3_Getc();
		
		if (onebyte != 0x01) {// 0x01 - WRITE_SUCCESS
			printf("write failure code: 0x%X\r\n", onebyte);

			return -1;
		}
	} else {// invalid ack
		printf("receive invalid ack header: 0x%X\r\n", onebyte);

		return -1;
	}
	
	return 0;
}

static uint8_t bno055_read_byte(uint8_t reg_addr)
{
	int16_t i = 0;
	uint8_t onebyte = 0;

    Uart3_Clear();
	memset(send_buf, 0, 64);

	send_buf[0] = 0xAA;
	send_buf[1] = 0x01;// RD
	send_buf[2] = reg_addr;
	send_buf[3] = 0x01;// LEN
	// send data
	for (i=0; i<4; i++) {
		Uart3_Putc(send_buf[i]);
	}

	// wait
	delay_ms(20);

	// recv ack till empty or timeout
	onebyte = Uart3_Getc();

	if (0xEE == onebyte) {// NG ack response
		onebyte = Uart3_Getc();
		printf("read failure code: 0x%X\r\n", onebyte);

		return -1;
	} else if (0xBB == onebyte) {// OK ack response
		onebyte = Uart3_Getc();// length
		
		if (onebyte != 0x01) {// length NG
			printf("receive data lenght is ng\r\n");
			return -1;
		}

		return Uart3_Getc();// data
	} else {// invalid ack
		printf("read invalid ack header: 0x%X\r\n", onebyte);

		return -1;
	}
}

static int16_t bno055_read_bytes(uint8_t reg_addr, uint8_t len, uint8_t *p_out)
{
	int16_t i = 0;
	uint8_t onebyte = 0;

	if ((!p_out) || (len<=0)) {
		return -1;
	}
    Uart3_Clear();
	memset(send_buf, 0, 64);
	
	send_buf[0] = 0xAA;
	send_buf[1] = 0x01;// RD
	send_buf[2] = reg_addr;
	send_buf[3] = len;// LEN
	// send data
	for (i=0; i<4; i++) {
		Uart3_Putc(send_buf[i]);
	}

	// wait
	delay_ms(20);

	// recv ack till empty or timeout
	onebyte = Uart3_Getc();

	if (0xEE == onebyte) {// NG ack response
		onebyte = Uart3_Getc();
		printf("read failure code: 0x%X\r\n", onebyte);

		return -1;
	} else if (0xBB == onebyte) {// OK ack response
		onebyte = Uart3_Getc();// length
		
		if (onebyte != len) {// length NG
			printf("receive data length is NG(%d-%d)\r\n", len, onebyte);
			return -1;
		}
		
		for (i=0; i<onebyte; i++) {
			p_out[i] = Uart3_Getc();// length
		}
	} else {// invalid ack
		printf("read invalid ack header: 0x%X\r\n", onebyte);

		return -1;
	}
	
	return 0;
}
static int16_t bno055_loop_read_bytes(uint8_t reg_addr,uint8_t len,uint8_t *p_out)
{
    int16_t i = 3;
    int16_t result = 0;
    while(i--){
        result = bno055_read_bytes(reg_addr,len,p_out);
        if(!result){
            return 0;
        }
    }
    return -1;
}

// to check chip id
int16_t bno055_verify_chip(void)
{
	uint8_t onebyte = 0;
	onebyte = bno055_read_byte(BNO055_CHIP_ID);
	
	if (onebyte != 0xA0) {
		printf("verify BNO055_CHIP_ID failed\r\n");
		
		return -1;
	}
	
	onebyte = bno055_read_byte(BNO055_ACC_ID);
	
	if (onebyte != 0xFB) {
		printf("verify BNO055_ACC_ID failed\r\n");
		
		return -1;
	}
	
	onebyte = bno055_read_byte(BNO055_MAG_ID);
	
	if (onebyte != 0x32) {
		printf("verify BNO055_MAG_ID failed\r\n");
		
		return -1;
	}
	
	onebyte = bno055_read_byte(BNO055_GYRO_ID);
	
	if (onebyte != 0x0F) {
		printf("verify BNO055_GYRO_ID failed\r\n");
		
		return -1;
	}
	
	return 0;
}

// read the X/Y/Z axis of acceleration
int16_t bno055_read_accel(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z accel register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_ACC_DATA_X_LSB, 6, &byteData[0]);  // Read the six raw data registers into data array
    if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];      // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4];
    }
    return result;
}

// read the X/Y/Z axis of gyroscope
int16_t bno055_read_gyro(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_GYR_DATA_X_LSB, 6, &byteData[0]);  // Read the six raw data registers sequentially into data array
	if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4]; 
    }
    return result;
}

// read the X/Y/Z axis of magnetometer
int16_t bno055_read_mag(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_MAG_DATA_X_LSB, 6, &byteData[0]);  // Read the six raw data registers sequentially into data array
	if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4];
    }
    return result;
}

// read the W/X/Y/Z axis of quaternion
int16_t bno055_read_quat(int16_t *p_out)
{
	uint8_t byteData[8];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_QUA_DATA_W_LSB, 8, &byteData[0]);  // Read the six raw data registers sequentially into data array
	if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4];
        p_out[3] = ((int16_t)byteData[7] << 8) | byteData[6];
    }
    return result;
    
}

// read the heading/roll/pitch of euler
int16_t bno055_read_eul(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_EUL_HEADING_LSB, 6, &byteData[0]);  // Read the six raw data registers sequentially into data array
    if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4];
    }
    return result;
}

// read the X/Y/Z axis of linear acceleration
int16_t bno055_read_lia(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_LIA_DATA_X_LSB, 6, &byteData[0]);  // Read the six raw data registers sequentially into data array
	if(!result){
       p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4]; 
    }
    return result;
}

// read the X/Y/Z axis of gravity vector
int16_t bno055_read_grv(int16_t *p_out)
{
	uint8_t byteData[6];  // x/y/z gyro register data stored here
	int16_t result = bno055_loop_read_bytes(BNO055_GRV_DATA_X_LSB, 6, &byteData[0]);  // Read the six raw data registers sequentially into data array
	if(!result){
        p_out[0] = ((int16_t)byteData[1] << 8) | byteData[0];       // Turn the MSB and LSB into a signed 16-bit value
        p_out[1] = ((int16_t)byteData[3] << 8) | byteData[2];  
        p_out[2] = ((int16_t)byteData[5] << 8) | byteData[4];
    }
    return result;
}

int16_t bno055_read_calibrate_sta(int16_t *calib_sta)
{
	uint8_t temp = 0;

	int16_t result = bno055_loop_read_bytes(BNO055_CALIB_STAT, 1, &temp);
    if(!result){
        printf("calibration sta = 0x%.2X\r\n", temp);
        printf("system calibration %s\r\n", ((3 == (0xC0&temp)>>6))?"done":"not done");
        printf("gyro calibration %s\r\n", ((3 == (0x30&temp)>>4))?"done":"not done");
        printf("accel calibration %s\r\n", ((3 == (0x0C&temp)>>2))?"done":"not done");
        printf("mag calibration %s\r\n", ((3 == (0x03&temp)>>0))?"done":"not done");
        
        *calib_sta = temp;
    }
	return result;
}

// 1 C = 1 LSB
// 2 F = 1 LSB
int8_t bno055_read_temp(void)
{
	uint8_t temp = 0;

	bno055_loop_read_bytes(BNO055_TEMP, 1, &temp);

	return temp;
}

// read system status & self test result & system error
void bno055_read_status(uint8_t *sys_stat, uint8_t *st_ret, uint8_t * sys_err)
{
	uint8_t temp = 0;

	if (!sys_stat || !st_ret || !sys_err) {
		return;
	}

	// Select page 0 to read sensors
	// bno055_write_byte(BNO055_PAGE_ID, 0x00);

	/* system status
	 0 = idel
	 1 = system error
	 2 = initializing peripherals
	 3 = system initialization
     4 = executing self-test
	 5 = sensor fusio algorithm running
	 6 = system running without fusion algorithms
	*/
	bno055_loop_read_bytes(BNO055_SYS_STATUS, 1, &temp);
	*sys_stat = temp;

	/* self test result
	 0 = fail
	 1 = pass
	 BIT0: accelerometer self test
	 BIT1: magnetometer self test
	 BIT2: gyroscope self test
	 BIT3: mcu self test
	*/
	bno055_loop_read_bytes(BNO055_ST_RESULT, 1, &temp);
	*st_ret = temp;
	
	/*
	 0 = no error
	 1 = peripheral initialization error
	 2 = system initialization error
	 3 = self test result failed
	 4 = register map value out of range
	 5 = register map address out of range
	 6 = register map write error
	 7 = BNO low power mode not available for selected operation mode
	 8 = accelerometer power mode not available
	 9 = fusion algorithm configuration error
	 A = sensor configuration error
	*/
	bno055_loop_read_bytes(BNO055_SYS_ERR, 1, &temp);
	*sys_err = temp;
}

// change the chip's axis remap
int8_t bno055_set_axis_remap(uint8_t mode)
{
	// Select BNO055 config mode
	int16_t result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	result = bno055_write_byte(BNO055_AXIS_MAP_CONFIG, mode);
    if(result){
        return -1;
    }
	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	return 0;
}

// change the chip's axis sign
int8_t bno055_set_axis_sign(uint8_t mode)
{
    int16_t result = 0;
	// Select BNO055 config mode
	result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	result = bno055_write_byte(BNO055_AXIS_MAP_SIGN, mode);
    if(result){
        return -1;
    }
	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	return 0;
}

int8_t bno055_enter_suspend_mode(void)
{
    int16_t result = 0;
	// Select BNO055 config mode
	result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	delay_ms(25);

	result = bno055_write_byte(BNO055_PWR_MODE, 0x02);
    if(result){
        return -1;
    }
	delay_ms(25);

	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	delay_ms(25);

	return 0;
}

int8_t bno055_enter_normal_mode(void)
{
    int16_t result = 0;
	// Select BNO055 config mode
	result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	delay_ms(25);

	result = bno055_write_byte(BNO055_PWR_MODE, 0x00);
    if(result){
        return -1;
    }
	delay_ms(25);

	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	delay_ms(25);

	return 0;
}

int16_t bno055_initial(void)
{
    int16_t result = 0;
    uint8_t onebyte = 0;
    uint8_t try_cnt = 5;

	// Select BNO055 config mode
	result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	delay_ms(25);

    // do reset
	result = bno055_write_byte(BNO055_SYS_TRIGGER, 0x20);
    if(result){
        return -1;
    }
	delay_ms(1000);

    while (--try_cnt) {
        onebyte = bno055_read_byte(BNO055_CHIP_ID);

        if (0xA0 == onebyte) {
            break;
        }
        
        delay_ms(25);
    }
    
    // timeout
    if (try_cnt <= 0) {
        return -1;
    }

	result = bno055_write_byte(BNO055_PWR_MODE, Normalpwr);
    if(result){
        return -1;
    }
    delay_ms(25);

	// Select page 0 to read sensors
	result = bno055_write_byte(BNO055_PAGE_ID, 0x00);
	if(result){
        return -1;
    }
    delay_ms(25);

#if 0
	// TEMP_SRC REG:
	// BIT1~0: 00-Accelerometer; 01-Gyroscope
	// Select BNO055 gyro temperature source 
	result = bno055_write_byte(BNO055_TEMP_SOURCE, 0x01);
	if(result){
        return -1;
    }
	// UNIT_SEL REG: default 0
	// BIT7:(Oritention Mode) 0-Windows ; 1-Android
	// BIT4:(Temp Unit) 0-C ; 1-F
	// BIT2:(Euler Unit) 0-Degrees ; 1-Radians
	// BIT1:(Gyro Angular Rate) 0-dps ; 1-rps
	// BIT0:(Acceleration Unit) 0-m/s2 ; 1-mg
	// Select BNO055 sensor units (temperature in degrees C, rate in dps, accel in mg)
	result = bno055_write_byte(BNO055_UNIT_SEL, 0x01 );
	if(result){
        return -1;
    }
#endif

	result = bno055_write_byte(BNO055_SYS_TRIGGER, 0x00);
    if(result){
        return -1;
    }
	delay_ms(25);

	// Select BNO055 NDOF mode
	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	delay_ms(25);

	// Select page 0 to read sensors
	result = bno055_write_byte(BNO055_PAGE_ID, 0x00);
	if(result){
        return -1;
    }
    delay_ms(25);

    return 0;
}
int16_t bno055_calibrate_demo(void)
{
    int16_t result = 0;
    int16_t calib_sta = 0;
    uint8_t byteData[22];

    // TODO: load offset configs from flash/eeprom into register
    // load_offset_from_flash(&byteData[0]);
    if (0) {
        // Select BNO055 config mode
        result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
        if(result){
            return -1;
        }
        delay_ms(25);

        result = bno055_write_bytes(BNO055_ACC_OFFSET_X_LSB, &byteData[0], 22);
        if(result){
            return -1;
        }
        delay_ms(25);

        // Select BNO055 NDOF mode
        result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
        if(result){
            return -1;
        }
        delay_ms(25);
        
        /* Crystal must be configured AFTER loading calibration data into BNO055. */
        result = bno055_set_ext_crystal(true);
        if(result){
            return -1;
        }
    }

    // TODO: if no offset configs saved in flash/eeprom, to do the calibration
    while (1) {
        printf("To Calibrate Accel/Gyro: Put device on a level surface and keep motionless! Wait......\r\n");
        printf("To Calibrate Mag: Wave device in a figure eight until done!\r\n");
    
        bno055_read_calibrate_sta(&calib_sta);
        
        if (0xFF == calib_sta) {
            break;
        }
        
        delay_ms(3000);
    }
    
	result = bno055_loop_read_bytes(BNO055_ACC_OFFSET_X_LSB, 22, &byteData[0]);
    if(result){
        return -1;
    }
    
    // TODO: save the calibrated done offset configs into flash
    // save_offset_into_flash(&byteData[0]);

    return 0;
}

int16_t bno055_set_ext_crystal(bool usextal)
{
    int16_t result = 0;

	// Select BNO055 config mode
	result = bno055_write_byte(BNO055_OPR_MODE, CONFIGMODE);
    if(result){
        return -1;
    }
	delay_ms(25);

	// Select page 0 to read sensors
	result = bno055_write_byte(BNO055_PAGE_ID, 0x00);
	if(result){
        return -1;
    }
    delay_ms(25);
    
    if (usextal) {
        result = bno055_write_byte(BNO055_SYS_TRIGGER, 0x80);
    } else {
        result = bno055_write_byte(BNO055_SYS_TRIGGER, 0x00);
    }
    
    if(result){
        return -1;
    }
	delay_ms(25);
    
	// Select BNO055 NDOF mode
	result = bno055_write_byte(BNO055_OPR_MODE, NDOF);
    if(result){
        return -1;
    }
	delay_ms(25);
    
    return 0;
}

int16_t bno055_setup(void)
{
    int16_t result = 0;
    uint8_t sys_stat, st_ret, sys_err;

	result = bno055_verify_chip();
    if(result){
        return -1;
    }

	result = bno055_initial();
    if(result){
        return -1;
    }

    bno055_read_status(&sys_stat, &st_ret, &sys_err);

    result = bno055_set_ext_crystal(true);
    if(result){
        return -1;
    }
    
    return 0;
}
  
int16_t bno055_demo(void)
{
    int delay_time = 100;
	int16_t raw_data[4] = {0};
    int16_t result = 0;

	float ax, ay, az;// for acceleration
	float gx, gy, gz;// for gyroscope
	float mx, my, mz; // for magnetometer
	float qw, qx, qy, qz;// for quaternion

	float pitch, yaw, roll;// for euler
	float lia_x, lia_y, lia_z;// for linear acceleration
	float grv_x, grv_y, grv_z;// for gravity vector

	// 1 mg = 1 LSB
	// 1 m/s^2 = 100 LSB
	result = bno055_read_accel(raw_data);
    if(result){
        return -1;
    }
    ax = (float)raw_data[0] / 100;
    ay = (float)raw_data[1] / 100;
    az = (float)raw_data[2] / 100;

    printf("acceleration data: x=%f, y=%f, z=%f\r\n", (double)ax, (double)ay, (double)az);
	delay_ms(delay_time);

	// 1 dps = 16 LSB
	// 1 rps = 900 LSB
	result = bno055_read_gyro(raw_data);
    if(result){
        return -1;
    }
    gx = (float)raw_data[0] / 16;
    gy = (float)raw_data[1] / 16;
    gz = (float)raw_data[2] / 16;

    printf("gyroscope data: x=%f, y=%f, z=%f\r\n", (double)gx, (double)gy, (double)gz);
    delay_ms(delay_time);
	

	// 1 ut = 16 LSB
	result = bno055_read_mag(raw_data);
    if(result){
        return -1;
    }
    mx = (float)raw_data[0] / 16;
    my = (float)raw_data[1] / 16;
    mz = (float)raw_data[2] / 16;

    printf("magnetometer data: x=%f, y=%f, z=%f\r\n", (double)mx, (double)my, (double)mz);
    
	
    delay_ms(delay_time);
	// 1 quaternion = 2^14 LSB
	result = bno055_read_quat(raw_data);
    if(result){
        return -1;
    }
    qw = (float)raw_data[0] / 16384;
    qx = (float)raw_data[1] / 16384;
    qy = (float)raw_data[2] / 16384;
    qz = (float)raw_data[3] / 16384;

    printf("quaternion data: qw=%f, qx=%f, qy=%f, qz=%f\r\n", (double)qw, (double)qx, (double)qy, (double)qz);
    delay_ms(delay_time);
    
	// 1 degrees = 16 LSB
	// 1 radians = 900 LSB
	result = bno055_read_eul(raw_data);
    if(result){
        return -1;
    }
    yaw = (float)raw_data[0] / 16;
    roll = (float)raw_data[1] / 16;
    pitch = (float)raw_data[2] / 16;

    printf("euler data: yaw=%f, roll=%f, pitch=%f\r\n", (double)yaw, (double)roll, (double)pitch);
    delay_ms(delay_time);
	// 1 mg = 1 LSB
	// 1 m/s^2 = 100 LSB
	result = bno055_read_lia(raw_data);
    if(result){
        return -1;
    }
    lia_x = (float)raw_data[0] / 100;
    lia_y = (float)raw_data[1] / 100;
    lia_z = (float)raw_data[2] / 100;

    printf("linear acceleration data: x=%f, y=%f, z=%f\r\n", (double)lia_x, (double)lia_y, (double)lia_z);
    delay_ms(delay_time);
	// 1 mg = 1 LSB
	// 1 m/s^2 = 100 LSB
	result = bno055_read_grv(raw_data);
    if(result){
        return -1; 
    }
    grv_x = (float)raw_data[0] / 100;
    grv_y = (float)raw_data[1] / 100;
    grv_z = (float)raw_data[2] / 100;

    printf("grv data: x=%f, y=%f,z=%f\r\n", (double)grv_x, (double)grv_y, (double)grv_z);
    delay_ms(delay_time);
    return 0;
}

//******************************************************************************
// Configure BG96
//******************************************************************************
int16_t Configure_BNO055(void)
{
    int16_t result = bno055_setup();
    if(result){
        printf("bno055 init failure\r\n");
    }else{
        printf("bno055 init success");
    }
    return result;
}

//******************************************************************************
//* END OF FILE
//******************************************************************************
