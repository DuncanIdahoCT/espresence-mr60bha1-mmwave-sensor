#include "mr60bha1_component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mr60bha1 {

static const char *const TAG = "mr60bha1";

void UARTSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MR60BHA1 UART Reader...");
}

void UARTSensor::loop() {
  while (available()) {
    uint8_t byte;
    if (read_byte(&byte)) {
      bytes_.push_back(byte);
      
      // End of frame is 0x54 0x43
      if (bytes_.size() >= 2 && 
          bytes_[bytes_.size()-2] == 0x54 && 
          bytes_[bytes_.size()-1] == 0x43) {
        process_packet();
        bytes_.clear();
      }
      
      // Prevent buffer overflow
      if (bytes_.size() > 100) {
        ESP_LOGW(TAG, "Buffer overflow, clearing");
        bytes_.clear();
      }
    }
  }
}

void UARTSensor::process_packet() {
  if (bytes_.size() < 10) {
    ESP_LOGW(TAG, "Packet too short: %d bytes", bytes_.size());
    return;
  }

  // Presence information
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x80 && 
      bytes_[3] == 0x01 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (presence_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      presence_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Presence: %d", value);
    }
    return;
  }

  // Motion information
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x80 && 
      bytes_[3] == 0x02 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (motion_sensor_ != nullptr) {
      int value = (bytes_[6] == 0x02) ? 1 : 0;
      motion_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Motion: %d", value);
    }
    return;
  }

  // Body dynamic parameters
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x80 && 
      bytes_[3] == 0x03 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (activity_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      activity_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Activity: %d", value);
    }
    return;
  }

  // Active reporting of human distance
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x80 && 
      bytes_[3] == 0x04 && bytes_[4] == 0x00 && bytes_[5] == 0x02) {
    if (distance_sensor_ != nullptr && bytes_.size() >= 8) {
      int value = static_cast<int>(bytes_[6]) + static_cast<int>(bytes_[7]);
      distance_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Distance: %d", value);
    }
    return;
  }

  // Active reporting of human body orientation
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x80 && 
      bytes_[3] == 0x05 && bytes_[4] == 0x00 && bytes_[5] == 0x06) {
    if (bytes_.size() >= 12) {
      if (angle_x_sensor_ != nullptr) {
        int x_value = static_cast<int>(bytes_[6]) + static_cast<int>(bytes_[7]);
        angle_x_sensor_->publish_state(x_value);
      }
      if (angle_y_sensor_ != nullptr) {
        int y_value = static_cast<int>(bytes_[8]) + static_cast<int>(bytes_[9]);
        angle_y_sensor_->publish_state(y_value);
      }
      if (angle_z_sensor_ != nullptr) {
        int z_value = static_cast<int>(bytes_[10]) + static_cast<int>(bytes_[11]);
        angle_z_sensor_->publish_state(z_value);
      }
      ESP_LOGD(TAG, "Angles X:%d Y:%d Z:%d", 
               static_cast<int>(bytes_[6]) + static_cast<int>(bytes_[7]),
               static_cast<int>(bytes_[8]) + static_cast<int>(bytes_[9]), 
               static_cast<int>(bytes_[10]) + static_cast<int>(bytes_[11]));
    }
    return;
  }

  // Heart rate information
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x85 && 
      bytes_[3] == 0x01 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (heartstate_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      heartstate_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Heart state: %d", value);
    }
    return;
  }

  // Heart rate value
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x85 && 
      bytes_[3] == 0x02 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (heartrate_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      heartrate_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Heart rate: %d", value);
    }
    return;
  }

  // Respiratory information
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x81 && 
      bytes_[3] == 0x01 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (respstate_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      respstate_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Respiratory state: %d", value);
    }
    return;
  }

  // Respiratory value
  if (bytes_[0] == 0x53 && bytes_[1] == 0x59 && bytes_[2] == 0x81 && 
      bytes_[3] == 0x02 && bytes_[4] == 0x00 && bytes_[5] == 0x01) {
    if (resprate_sensor_ != nullptr) {
      int value = static_cast<int>(bytes_[6]);
      resprate_sensor_->publish_state(value);
      ESP_LOGD(TAG, "Respiratory rate: %d", value);
    }
    return;
  }

  ESP_LOGV(TAG, "Unknown packet: %s", hex_str(bytes_[0]).c_str());
}

std::string UARTSensor::hex_str(uint8_t data) {
  char hex[5];
  snprintf(hex, sizeof(hex), "0x%02X", data);
  return std::string(hex);
}

} // namespace mr60bha1
} // namespace esphome
