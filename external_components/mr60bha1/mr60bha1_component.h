#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace mr60bha1 {

class UARTSensor : public Component, public uart::UARTDevice {
public:
  UARTSensor() = default;

  void setup() override;
  void loop() override;
  
  // Setter methods for sensors (called from Python code)
  void set_presence_sensor(sensor::Sensor *sensor) { presence_sensor_ = sensor; }
  void set_motion_sensor(sensor::Sensor *sensor) { motion_sensor_ = sensor; }
  void set_activity_sensor(sensor::Sensor *sensor) { activity_sensor_ = sensor; }
  void set_distance_sensor(sensor::Sensor *sensor) { distance_sensor_ = sensor; }
  void set_angle_x_sensor(sensor::Sensor *sensor) { angle_x_sensor_ = sensor; }
  void set_angle_y_sensor(sensor::Sensor *sensor) { angle_y_sensor_ = sensor; }
  void set_angle_z_sensor(sensor::Sensor *sensor) { angle_z_sensor_ = sensor; }
  void set_heartstate_sensor(sensor::Sensor *sensor) { heartstate_sensor_ = sensor; }
  void set_heartrate_sensor(sensor::Sensor *sensor) { heartrate_sensor_ = sensor; }
  void set_respstate_sensor(sensor::Sensor *sensor) { respstate_sensor_ = sensor; }
  void set_resprate_sensor(sensor::Sensor *sensor) { resprate_sensor_ = sensor; }

protected:
  sensor::Sensor *presence_sensor_{nullptr};
  sensor::Sensor *motion_sensor_{nullptr};
  sensor::Sensor *activity_sensor_{nullptr};
  sensor::Sensor *distance_sensor_{nullptr};
  sensor::Sensor *angle_x_sensor_{nullptr};
  sensor::Sensor *angle_y_sensor_{nullptr};
  sensor::Sensor *angle_z_sensor_{nullptr};
  sensor::Sensor *heartstate_sensor_{nullptr};
  sensor::Sensor *heartrate_sensor_{nullptr};
  sensor::Sensor *respstate_sensor_{nullptr};
  sensor::Sensor *resprate_sensor_{nullptr};

  std::vector<uint8_t> bytes_;
  
  void process_packet();
  std::string hex_str(uint8_t data);
};

} // namespace mr60bha1
} // namespace esphome
