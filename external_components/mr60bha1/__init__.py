import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

mr60bha1_ns = cg.esphome_ns.namespace("mr60bha1")
UARTSensor = mr60bha1_ns.class_("UARTSensor", cg.Component, uart.UARTDevice)

# Define configuration keys
CONF_PRESENCE = "presence"
CONF_MOTION = "motion"
CONF_ACTIVITY = "activity"
CONF_DISTANCE = "distance"
CONF_ANGLE_X = "angle_x"
CONF_ANGLE_Y = "angle_y"
CONF_ANGLE_Z = "angle_z"
CONF_HEARTSTATE = "heartstate"
CONF_HEARTRATE = "heartrate"
CONF_RESPSTATE = "respstate"
CONF_RESPRATE = "resprate"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(UARTSensor),
    cv.Optional(CONF_PRESENCE): sensor.sensor_schema(),
    cv.Optional(CONF_MOTION): sensor.sensor_schema(),
    cv.Optional(CONF_ACTIVITY): sensor.sensor_schema(),
    cv.Optional(CONF_DISTANCE): sensor.sensor_schema(),
    cv.Optional(CONF_ANGLE_X): sensor.sensor_schema(),
    cv.Optional(CONF_ANGLE_Y): sensor.sensor_schema(),
    cv.Optional(CONF_ANGLE_Z): sensor.sensor_schema(),
    cv.Optional(CONF_HEARTSTATE): sensor.sensor_schema(),
    cv.Optional(CONF_HEARTRATE): sensor.sensor_schema(),
    cv.Optional(CONF_RESPSTATE): sensor.sensor_schema(),
    cv.Optional(CONF_RESPRATE): sensor.sensor_schema(),
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PRESENCE in config:
        sens = await sensor.new_sensor(config[CONF_PRESENCE])
        cg.add(var.set_presence_sensor(sens))
        
    if CONF_MOTION in config:
        sens = await sensor.new_sensor(config[CONF_MOTION])
        cg.add(var.set_motion_sensor(sens))
        
    if CONF_ACTIVITY in config:
        sens = await sensor.new_sensor(config[CONF_ACTIVITY])
        cg.add(var.set_activity_sensor(sens))
        
    if CONF_DISTANCE in config:
        sens = await sensor.new_sensor(config[CONF_DISTANCE])
        cg.add(var.set_distance_sensor(sens))
        
    if CONF_ANGLE_X in config:
        sens = await sensor.new_sensor(config[CONF_ANGLE_X])
        cg.add(var.set_angle_x_sensor(sens))
        
    if CONF_ANGLE_Y in config:
        sens = await sensor.new_sensor(config[CONF_ANGLE_Y])
        cg.add(var.set_angle_y_sensor(sens))
        
    if CONF_ANGLE_Z in config:
        sens = await sensor.new_sensor(config[CONF_ANGLE_Z])
        cg.add(var.set_angle_z_sensor(sens))
        
    if CONF_HEARTSTATE in config:
        sens = await sensor.new_sensor(config[CONF_HEARTSTATE])
        cg.add(var.set_heartstate_sensor(sens))
        
    if CONF_HEARTRATE in config:
        sens = await sensor.new_sensor(config[CONF_HEARTRATE])
        cg.add(var.set_heartrate_sensor(sens))
        
    if CONF_RESPSTATE in config:
        sens = await sensor.new_sensor(config[CONF_RESPSTATE])
        cg.add(var.set_respstate_sensor(sens))
        
    if CONF_RESPRATE in config:
        sens = await sensor.new_sensor(config[CONF_RESPRATE])
        cg.add(var.set_resprate_sensor(sens))
