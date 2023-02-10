#include "esphome.h"

using namespace esphome;

class UARTSensor : public Component, public UARTDevice {
  public:
  UARTSensor(UARTComponent *parent) : UARTDevice(parent) {}
  Sensor* presence_sensor = new Sensor();
  Sensor* motion_sensor = new Sensor();
  Sensor* activity_sensor = new Sensor();
  Sensor* distance_sensor = new Sensor();
  Sensor* angle_x_sensor = new Sensor();
  Sensor* angle_y_sensor = new Sensor();
  Sensor* angle_z_sensor = new Sensor();
  Sensor* heartstate_sensor = new Sensor();
  Sensor* heartrate_sensor = new Sensor();
  Sensor* respstate_sensor = new Sensor();
  Sensor* resprate_sensor = new Sensor();

  void setup() {
  }

  std::vector<int> bytes;

void loop() override
{
    while (available())
    {
        bytes.push_back(read());

        //End of Frame is 0x54 0x43
        if(bytes[bytes.size()-2] == 0x54 && bytes[bytes.size()-1] == 0x43)
        {            
			processPacket();
            bytes.clear();        
        }
    }
}

  void processPacket() {            

    std::string str = "";
	
	// As described in the Seeed Studio protocol tables:

    // Presence information
	if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) && (bytes[3] == 0x01) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		int presence_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Presence Frame", str.c_str());

		presence_sensor->publish_state(presence_sensor_value);
		return;
	}

    // Motion information
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) && (bytes[3] == 0x02) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		if((bytes[6] == 0x02))
		{
		int motion_sensor_value = 1;
		motion_sensor->publish_state(motion_sensor_value);
		}

		if((bytes[6] == 0x01))
		{
		int motion_sensor_value = 0;            

		motion_sensor->publish_state(motion_sensor_value);
		}

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Motion Frame", str.c_str());

		return;
	}

    // Body dynamic parameters
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) && (bytes[3] == 0x03) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		int activity_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Activity Level Frame", str.c_str());

		//str = esphome::to_string(activity_sensor_value);
		//ESP_LOGI("Activity Level", str.c_str());
            
		activity_sensor->publish_state(activity_sensor_value);
		return;
	}

    // Active reporting of human distance
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) && (bytes[3] == 0x04) && (bytes[4] == 0x00) && (bytes[5] == 0x02))
    {        
      
		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]) + ", " + hexStr(bytes[10]);
		//ESP_LOGI("Distance Frame", str.c_str());

		int distance_sensor_value = int(bytes[6]) + int(bytes[7]);
		
		//str = esphome::to_string(distance_sensor_value);
		//ESP_LOGI("Distance", str.c_str());

		distance_sensor->publish_state(distance_sensor_value);
		return;
	}

    // Active reporting of human body orientation
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x80) && (bytes[3] == 0x05) && (bytes[4] == 0x00) && (bytes[5] == 0x06))
    {        
      
		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]) + ", " + hexStr(bytes[10]) + ", " + hexStr(bytes[11]) + ", " + hexStr(bytes[12]) + ", " + hexStr(bytes[13]) + ", " + hexStr(bytes[14]);
		//ESP_LOGI("Angle Frame", str.c_str());

		int angle_x_sensor_value = int(bytes[6]) + int(bytes[7]);
		int angle_y_sensor_value = int(bytes[8]) + int(bytes[9]);
		int angle_z_sensor_value = int(bytes[10]) + int(bytes[11]);
		
		str = "Angle X: " + esphome::to_string(angle_x_sensor_value) + ", Angle Y: " + esphome::to_string(angle_y_sensor_value) + ", Angle Z: " + esphome::to_string(angle_z_sensor_value);
		
		//ESP_LOGI("Angles", str.c_str());

		angle_x_sensor->publish_state(angle_x_sensor_value);
		angle_y_sensor->publish_state(angle_y_sensor_value);
		angle_z_sensor->publish_state(angle_z_sensor_value);

		return;
	}

    // Heart rate information
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x85) && (bytes[3] == 0x01) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		int heartstate_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Heartrate Information Frame", str.c_str());

		//str = esphome::to_string(heartstate_sensor_value);
		//ESP_LOGI("Heartrate Information Frame", str.c_str());
            
		heartstate_sensor->publish_state(heartstate_sensor_value);
		return;
	}

    // Heart rate value
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x85) && (bytes[3] == 0x02) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		int heartrate_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Heartrate Level Frame", str.c_str());

		//str = esphome::to_string(heartrate_sensor_value);
		//ESP_LOGI("Heartrate Level", str.c_str());
            
		heartrate_sensor->publish_state(heartrate_sensor_value);
		return;
	}

    // Respiratory information
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x81) && (bytes[3] == 0x01) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        

		int respstate_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Respiratory Information Frame", str.c_str());

		//str = esphome::to_string(respstate_sensor_value);
		//ESP_LOGI("Respiratory Information", str.c_str());

		respstate_sensor->publish_state(respstate_sensor_value);
		return;
	}

    // Respiratory value
    if((bytes[0] == 0x53) && (bytes[1] == 0x59) && (bytes[2] == 0x81) && (bytes[3] == 0x02) && (bytes[4] == 0x00) && (bytes[5] == 0x01))
    {        
      
		int resprate_sensor_value = int(bytes[6]);

		//str = "Bytes: " + hexStr(bytes[0]) + ", " + hexStr(bytes[1]) + ", " + hexStr(bytes[2]) + ", " + hexStr(bytes[3]) + ", " + hexStr(bytes[4]) + ", " + hexStr(bytes[5]) + ", " + hexStr(bytes[6]) + ", " + hexStr(bytes[7]) + ", " + hexStr(bytes[8]) + ", " + hexStr(bytes[9]);
		//ESP_LOGI("Respiratory Level Frame", str.c_str());

		//str = esphome::to_string(resprate_sensor_value);
		//ESP_LOGI("Respiratory Level", str.c_str());
            
		resprate_sensor->publish_state(resprate_sensor_value);
		return;
	}

  }

	char hexmap[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	std::string hexStr(int data)
	{
		std::string s = "    ";
		s[0] = '0';
		s[1] = 'x';
		s[2] = hexmap[(data & 0xF0) >> 4];
		s[3] = hexmap[data & 0x0F];
	
		//s = "0x" + s;  
		return s;
	}

};
