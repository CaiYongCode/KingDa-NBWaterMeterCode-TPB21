/*********************************************************************************
�ļ�������
*********************************************************************************/
#include "Debug.h"
/*********************************************************************************
����������
*********************************************************************************/
/*********************************************************************************
��������������
*********************************************************************************/
/*********************************************************************************
�ⲿ����������
*********************************************************************************/
/*********************************************************************************
˽�б���������
*********************************************************************************/ 
struct Debug_EN Debug;
/*********************************************************************************
���Ա���������
*********************************************************************************/
/*********************************************************************************
�ڲ�����������
*********************************************************************************/
/*********************************************************************************
���ܴ��붨����
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Process(void)
{
  unsigned char cmd = 0;

  if( (BC95.Start_Process == BC95_POWER_DOWN)
        &&(Debug.Status == 1)
         &&(Debug.SendData == 0) )
  {
    Debug.SendData = 1;
    Send_Debug_Data();
  }
  
  if(Uart3.Receive_Pend == TRUE)//�ж�������
  { 
    Uart3_Receive(Uart3.R_Buffer);
    
    if( (Uart3.R_Buffer[0] == 0xAB)&&(Uart3.R_Buffer[1] == 0xAB) )
    {
      cmd = Uart3.R_Buffer[2];
      switch(cmd)
      {
        case 0x01:
          {
            Debug.Status = 1;
            Debug_ACK_OK(cmd);
          }
          break;
        case 0x02:      //��ȡ����
          {
            if(BC95.Start_Process != BC95_POWER_DOWN)
            {
              Debug_ACK_Busy(cmd);
            }
            else
            {
              Send_Debug_Data();
            }
          }
          break;
        case 0x03:      //У��
          {
            Cal.Water_Data.flow8[0] = Uart3.R_Buffer[4];
            Cal.Water_Data.flow8[1] = Uart3.R_Buffer[5];
            Cal.Water_Data.flow8[2] = Uart3.R_Buffer[6];
            Cal.Water_Data.flow8[3] = Uart3.R_Buffer[7];
            Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);
            
            Debug_ACK_OK(cmd);
          }
          break;
        case 0x04:      //���Խ���
          {
            Debug.Status = 0;
            Create_Timer(ONCE,2,MCU_DeInit,0,PROCESS); 
            Debug_ACK_OK(cmd);
          }
          break;
        default:
          break;
      }
      
    }
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ACK_Busy(unsigned char cmd)
{
  unsigned char data[4] = {0};

  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = cmd;
  data[3] = 0x00;
  
  Uart3_Send(data,4);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ACK_OK(unsigned char cmd)
{
  unsigned char data[4] = {0};

  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = cmd;
  data[3] = 0x01;
  
  Uart3_Send(data,4);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Send_Debug_Data(void)
{
  unsigned char data[24] = {0};
   
  //��ȡʱ��   
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);

  //��ȡ�ϴ�����������Ϣ
  Read_BC95_ErrorRecord();
  
  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = 0x02;
  data[3] = 0x01;
  
  //��ǰ�ۻ�����
  data[4] = Cal.Water_Data.flow8[0];
  data[5] = Cal.Water_Data.flow8[1];
  data[6] = Cal.Water_Data.flow8[2];
  data[7] = Cal.Water_Data.flow8[3];
  //��ص�ѹ
  data[8] = MeterParameter.Voltage/0x100;
  data[9] = MeterParameter.Voltage%0x100;
  //�¶� 
  data[10] = (u8)MeterParameter.Temp;
  //��
  data[11] = (RTC_DateStr.RTC_Year+2000)/0x100;
  data[12] = (RTC_DateStr.RTC_Year+2000)%0x100;
  //��
  data[13] = RTC_DateStr.RTC_Month;
  //��
  data[14] = RTC_DateStr.RTC_Date;
  //ʱ
  data[15] = RTC_TimeStr.RTC_Hours;
  //��
  data[16] = RTC_TimeStr.RTC_Minutes;
  //��
  data[17] = RTC_TimeStr.RTC_Seconds;
  //����״̬
  data[18] = Cal.Error;
   //�ź�ǿ��
  data[19] = BC95.Rssi;
  //�ϴ�����������Ϣ
  data[20] = BC95.ErrorRecord;
  
  Uart3_Send(data,21);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

