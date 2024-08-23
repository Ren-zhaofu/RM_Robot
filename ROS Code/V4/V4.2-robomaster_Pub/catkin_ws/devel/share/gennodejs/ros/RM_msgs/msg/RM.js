// Auto-generated. Do not edit!

// (in-package RM_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RM {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Motor_M3508_ID01_W = null;
      this.Motor_M3508_ID02_W = null;
      this.Motor_M3508_ID03_W = null;
      this.Motor_M3508_ID04_W = null;
      this.JY901S_Acc_X = null;
      this.JY901S_Acc_Y = null;
      this.JY901S_Acc_Z = null;
      this.JY901S_Ang_Vel_X = null;
      this.JY901S_Ang_Vel_Y = null;
      this.JY901S_Ang_Vel_Z = null;
      this.JY901S_Ang_X = null;
      this.JY901S_Ang_Y = null;
      this.JY901S_Ang_Z = null;
      this.UWB_X = null;
      this.UWB_Y = null;
    }
    else {
      if (initObj.hasOwnProperty('Motor_M3508_ID01_W')) {
        this.Motor_M3508_ID01_W = initObj.Motor_M3508_ID01_W
      }
      else {
        this.Motor_M3508_ID01_W = 0;
      }
      if (initObj.hasOwnProperty('Motor_M3508_ID02_W')) {
        this.Motor_M3508_ID02_W = initObj.Motor_M3508_ID02_W
      }
      else {
        this.Motor_M3508_ID02_W = 0;
      }
      if (initObj.hasOwnProperty('Motor_M3508_ID03_W')) {
        this.Motor_M3508_ID03_W = initObj.Motor_M3508_ID03_W
      }
      else {
        this.Motor_M3508_ID03_W = 0;
      }
      if (initObj.hasOwnProperty('Motor_M3508_ID04_W')) {
        this.Motor_M3508_ID04_W = initObj.Motor_M3508_ID04_W
      }
      else {
        this.Motor_M3508_ID04_W = 0;
      }
      if (initObj.hasOwnProperty('JY901S_Acc_X')) {
        this.JY901S_Acc_X = initObj.JY901S_Acc_X
      }
      else {
        this.JY901S_Acc_X = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Acc_Y')) {
        this.JY901S_Acc_Y = initObj.JY901S_Acc_Y
      }
      else {
        this.JY901S_Acc_Y = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Acc_Z')) {
        this.JY901S_Acc_Z = initObj.JY901S_Acc_Z
      }
      else {
        this.JY901S_Acc_Z = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_Vel_X')) {
        this.JY901S_Ang_Vel_X = initObj.JY901S_Ang_Vel_X
      }
      else {
        this.JY901S_Ang_Vel_X = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_Vel_Y')) {
        this.JY901S_Ang_Vel_Y = initObj.JY901S_Ang_Vel_Y
      }
      else {
        this.JY901S_Ang_Vel_Y = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_Vel_Z')) {
        this.JY901S_Ang_Vel_Z = initObj.JY901S_Ang_Vel_Z
      }
      else {
        this.JY901S_Ang_Vel_Z = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_X')) {
        this.JY901S_Ang_X = initObj.JY901S_Ang_X
      }
      else {
        this.JY901S_Ang_X = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_Y')) {
        this.JY901S_Ang_Y = initObj.JY901S_Ang_Y
      }
      else {
        this.JY901S_Ang_Y = 0.0;
      }
      if (initObj.hasOwnProperty('JY901S_Ang_Z')) {
        this.JY901S_Ang_Z = initObj.JY901S_Ang_Z
      }
      else {
        this.JY901S_Ang_Z = 0.0;
      }
      if (initObj.hasOwnProperty('UWB_X')) {
        this.UWB_X = initObj.UWB_X
      }
      else {
        this.UWB_X = 0.0;
      }
      if (initObj.hasOwnProperty('UWB_Y')) {
        this.UWB_Y = initObj.UWB_Y
      }
      else {
        this.UWB_Y = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RM
    // Serialize message field [Motor_M3508_ID01_W]
    bufferOffset = _serializer.int16(obj.Motor_M3508_ID01_W, buffer, bufferOffset);
    // Serialize message field [Motor_M3508_ID02_W]
    bufferOffset = _serializer.int16(obj.Motor_M3508_ID02_W, buffer, bufferOffset);
    // Serialize message field [Motor_M3508_ID03_W]
    bufferOffset = _serializer.int16(obj.Motor_M3508_ID03_W, buffer, bufferOffset);
    // Serialize message field [Motor_M3508_ID04_W]
    bufferOffset = _serializer.int16(obj.Motor_M3508_ID04_W, buffer, bufferOffset);
    // Serialize message field [JY901S_Acc_X]
    bufferOffset = _serializer.float32(obj.JY901S_Acc_X, buffer, bufferOffset);
    // Serialize message field [JY901S_Acc_Y]
    bufferOffset = _serializer.float32(obj.JY901S_Acc_Y, buffer, bufferOffset);
    // Serialize message field [JY901S_Acc_Z]
    bufferOffset = _serializer.float32(obj.JY901S_Acc_Z, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_Vel_X]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_Vel_X, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_Vel_Y]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_Vel_Y, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_Vel_Z]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_Vel_Z, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_X]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_X, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_Y]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_Y, buffer, bufferOffset);
    // Serialize message field [JY901S_Ang_Z]
    bufferOffset = _serializer.float32(obj.JY901S_Ang_Z, buffer, bufferOffset);
    // Serialize message field [UWB_X]
    bufferOffset = _serializer.float32(obj.UWB_X, buffer, bufferOffset);
    // Serialize message field [UWB_Y]
    bufferOffset = _serializer.float32(obj.UWB_Y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RM
    let len;
    let data = new RM(null);
    // Deserialize message field [Motor_M3508_ID01_W]
    data.Motor_M3508_ID01_W = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [Motor_M3508_ID02_W]
    data.Motor_M3508_ID02_W = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [Motor_M3508_ID03_W]
    data.Motor_M3508_ID03_W = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [Motor_M3508_ID04_W]
    data.Motor_M3508_ID04_W = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [JY901S_Acc_X]
    data.JY901S_Acc_X = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Acc_Y]
    data.JY901S_Acc_Y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Acc_Z]
    data.JY901S_Acc_Z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_Vel_X]
    data.JY901S_Ang_Vel_X = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_Vel_Y]
    data.JY901S_Ang_Vel_Y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_Vel_Z]
    data.JY901S_Ang_Vel_Z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_X]
    data.JY901S_Ang_X = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_Y]
    data.JY901S_Ang_Y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [JY901S_Ang_Z]
    data.JY901S_Ang_Z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [UWB_X]
    data.UWB_X = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [UWB_Y]
    data.UWB_Y = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'RM_msgs/RM';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '97b056c437e37e3ccc8f73221431cb76';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 电机的线速度
    int16 Motor_M3508_ID01_W
    int16 Motor_M3508_ID02_W
    int16 Motor_M3508_ID03_W
    int16 Motor_M3508_ID04_W
    
    # JY901S角加速度
    float32 JY901S_Acc_X
    float32 JY901S_Acc_Y
    float32 JY901S_Acc_Z
    # JY901S角速度
    float32 JY901S_Ang_Vel_X
    float32 JY901S_Ang_Vel_Y
    float32 JY901S_Ang_Vel_Z
    # JY901S角度
    float32 JY901S_Ang_X
    float32 JY901S_Ang_Y
    float32 JY901S_Ang_Z
    
    # UWB
    float32 UWB_X
    float32 UWB_Y
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RM(null);
    if (msg.Motor_M3508_ID01_W !== undefined) {
      resolved.Motor_M3508_ID01_W = msg.Motor_M3508_ID01_W;
    }
    else {
      resolved.Motor_M3508_ID01_W = 0
    }

    if (msg.Motor_M3508_ID02_W !== undefined) {
      resolved.Motor_M3508_ID02_W = msg.Motor_M3508_ID02_W;
    }
    else {
      resolved.Motor_M3508_ID02_W = 0
    }

    if (msg.Motor_M3508_ID03_W !== undefined) {
      resolved.Motor_M3508_ID03_W = msg.Motor_M3508_ID03_W;
    }
    else {
      resolved.Motor_M3508_ID03_W = 0
    }

    if (msg.Motor_M3508_ID04_W !== undefined) {
      resolved.Motor_M3508_ID04_W = msg.Motor_M3508_ID04_W;
    }
    else {
      resolved.Motor_M3508_ID04_W = 0
    }

    if (msg.JY901S_Acc_X !== undefined) {
      resolved.JY901S_Acc_X = msg.JY901S_Acc_X;
    }
    else {
      resolved.JY901S_Acc_X = 0.0
    }

    if (msg.JY901S_Acc_Y !== undefined) {
      resolved.JY901S_Acc_Y = msg.JY901S_Acc_Y;
    }
    else {
      resolved.JY901S_Acc_Y = 0.0
    }

    if (msg.JY901S_Acc_Z !== undefined) {
      resolved.JY901S_Acc_Z = msg.JY901S_Acc_Z;
    }
    else {
      resolved.JY901S_Acc_Z = 0.0
    }

    if (msg.JY901S_Ang_Vel_X !== undefined) {
      resolved.JY901S_Ang_Vel_X = msg.JY901S_Ang_Vel_X;
    }
    else {
      resolved.JY901S_Ang_Vel_X = 0.0
    }

    if (msg.JY901S_Ang_Vel_Y !== undefined) {
      resolved.JY901S_Ang_Vel_Y = msg.JY901S_Ang_Vel_Y;
    }
    else {
      resolved.JY901S_Ang_Vel_Y = 0.0
    }

    if (msg.JY901S_Ang_Vel_Z !== undefined) {
      resolved.JY901S_Ang_Vel_Z = msg.JY901S_Ang_Vel_Z;
    }
    else {
      resolved.JY901S_Ang_Vel_Z = 0.0
    }

    if (msg.JY901S_Ang_X !== undefined) {
      resolved.JY901S_Ang_X = msg.JY901S_Ang_X;
    }
    else {
      resolved.JY901S_Ang_X = 0.0
    }

    if (msg.JY901S_Ang_Y !== undefined) {
      resolved.JY901S_Ang_Y = msg.JY901S_Ang_Y;
    }
    else {
      resolved.JY901S_Ang_Y = 0.0
    }

    if (msg.JY901S_Ang_Z !== undefined) {
      resolved.JY901S_Ang_Z = msg.JY901S_Ang_Z;
    }
    else {
      resolved.JY901S_Ang_Z = 0.0
    }

    if (msg.UWB_X !== undefined) {
      resolved.UWB_X = msg.UWB_X;
    }
    else {
      resolved.UWB_X = 0.0
    }

    if (msg.UWB_Y !== undefined) {
      resolved.UWB_Y = msg.UWB_Y;
    }
    else {
      resolved.UWB_Y = 0.0
    }

    return resolved;
    }
};

module.exports = RM;
