; Auto-generated. Do not edit!


(cl:in-package robomaster_msgs-msg)


;//! \htmlinclude robomaster.msg.html

(cl:defclass <robomaster> (roslisp-msg-protocol:ros-message)
  ((Motor_M3508_ID01_W
    :reader Motor_M3508_ID01_W
    :initarg :Motor_M3508_ID01_W
    :type cl:float
    :initform 0.0)
   (Motor_M3508_ID02_W
    :reader Motor_M3508_ID02_W
    :initarg :Motor_M3508_ID02_W
    :type cl:float
    :initform 0.0)
   (Motor_M3508_ID03_W
    :reader Motor_M3508_ID03_W
    :initarg :Motor_M3508_ID03_W
    :type cl:float
    :initform 0.0)
   (Motor_M3508_ID04_W
    :reader Motor_M3508_ID04_W
    :initarg :Motor_M3508_ID04_W
    :type cl:float
    :initform 0.0)
   (JY901S_Acc_X
    :reader JY901S_Acc_X
    :initarg :JY901S_Acc_X
    :type cl:float
    :initform 0.0)
   (JY901S_Acc_Y
    :reader JY901S_Acc_Y
    :initarg :JY901S_Acc_Y
    :type cl:float
    :initform 0.0)
   (JY901S_Acc_Z
    :reader JY901S_Acc_Z
    :initarg :JY901S_Acc_Z
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_Vel_X
    :reader JY901S_Ang_Vel_X
    :initarg :JY901S_Ang_Vel_X
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_Vel_Y
    :reader JY901S_Ang_Vel_Y
    :initarg :JY901S_Ang_Vel_Y
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_Vel_Z
    :reader JY901S_Ang_Vel_Z
    :initarg :JY901S_Ang_Vel_Z
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_X
    :reader JY901S_Ang_X
    :initarg :JY901S_Ang_X
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_Y
    :reader JY901S_Ang_Y
    :initarg :JY901S_Ang_Y
    :type cl:float
    :initform 0.0)
   (JY901S_Ang_Z
    :reader JY901S_Ang_Z
    :initarg :JY901S_Ang_Z
    :type cl:float
    :initform 0.0)
   (UWB_X
    :reader UWB_X
    :initarg :UWB_X
    :type cl:float
    :initform 0.0)
   (UWB_Y
    :reader UWB_Y
    :initarg :UWB_Y
    :type cl:float
    :initform 0.0))
)

(cl:defclass robomaster (<robomaster>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <robomaster>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'robomaster)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robomaster_msgs-msg:<robomaster> is deprecated: use robomaster_msgs-msg:robomaster instead.")))

(cl:ensure-generic-function 'Motor_M3508_ID01_W-val :lambda-list '(m))
(cl:defmethod Motor_M3508_ID01_W-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:Motor_M3508_ID01_W-val is deprecated.  Use robomaster_msgs-msg:Motor_M3508_ID01_W instead.")
  (Motor_M3508_ID01_W m))

(cl:ensure-generic-function 'Motor_M3508_ID02_W-val :lambda-list '(m))
(cl:defmethod Motor_M3508_ID02_W-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:Motor_M3508_ID02_W-val is deprecated.  Use robomaster_msgs-msg:Motor_M3508_ID02_W instead.")
  (Motor_M3508_ID02_W m))

(cl:ensure-generic-function 'Motor_M3508_ID03_W-val :lambda-list '(m))
(cl:defmethod Motor_M3508_ID03_W-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:Motor_M3508_ID03_W-val is deprecated.  Use robomaster_msgs-msg:Motor_M3508_ID03_W instead.")
  (Motor_M3508_ID03_W m))

(cl:ensure-generic-function 'Motor_M3508_ID04_W-val :lambda-list '(m))
(cl:defmethod Motor_M3508_ID04_W-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:Motor_M3508_ID04_W-val is deprecated.  Use robomaster_msgs-msg:Motor_M3508_ID04_W instead.")
  (Motor_M3508_ID04_W m))

(cl:ensure-generic-function 'JY901S_Acc_X-val :lambda-list '(m))
(cl:defmethod JY901S_Acc_X-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Acc_X-val is deprecated.  Use robomaster_msgs-msg:JY901S_Acc_X instead.")
  (JY901S_Acc_X m))

(cl:ensure-generic-function 'JY901S_Acc_Y-val :lambda-list '(m))
(cl:defmethod JY901S_Acc_Y-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Acc_Y-val is deprecated.  Use robomaster_msgs-msg:JY901S_Acc_Y instead.")
  (JY901S_Acc_Y m))

(cl:ensure-generic-function 'JY901S_Acc_Z-val :lambda-list '(m))
(cl:defmethod JY901S_Acc_Z-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Acc_Z-val is deprecated.  Use robomaster_msgs-msg:JY901S_Acc_Z instead.")
  (JY901S_Acc_Z m))

(cl:ensure-generic-function 'JY901S_Ang_Vel_X-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_Vel_X-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_Vel_X-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_Vel_X instead.")
  (JY901S_Ang_Vel_X m))

(cl:ensure-generic-function 'JY901S_Ang_Vel_Y-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_Vel_Y-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_Vel_Y-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_Vel_Y instead.")
  (JY901S_Ang_Vel_Y m))

(cl:ensure-generic-function 'JY901S_Ang_Vel_Z-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_Vel_Z-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_Vel_Z-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_Vel_Z instead.")
  (JY901S_Ang_Vel_Z m))

(cl:ensure-generic-function 'JY901S_Ang_X-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_X-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_X-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_X instead.")
  (JY901S_Ang_X m))

(cl:ensure-generic-function 'JY901S_Ang_Y-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_Y-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_Y-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_Y instead.")
  (JY901S_Ang_Y m))

(cl:ensure-generic-function 'JY901S_Ang_Z-val :lambda-list '(m))
(cl:defmethod JY901S_Ang_Z-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:JY901S_Ang_Z-val is deprecated.  Use robomaster_msgs-msg:JY901S_Ang_Z instead.")
  (JY901S_Ang_Z m))

(cl:ensure-generic-function 'UWB_X-val :lambda-list '(m))
(cl:defmethod UWB_X-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:UWB_X-val is deprecated.  Use robomaster_msgs-msg:UWB_X instead.")
  (UWB_X m))

(cl:ensure-generic-function 'UWB_Y-val :lambda-list '(m))
(cl:defmethod UWB_Y-val ((m <robomaster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robomaster_msgs-msg:UWB_Y-val is deprecated.  Use robomaster_msgs-msg:UWB_Y instead.")
  (UWB_Y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <robomaster>) ostream)
  "Serializes a message object of type '<robomaster>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Motor_M3508_ID01_W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Motor_M3508_ID02_W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Motor_M3508_ID03_W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Motor_M3508_ID04_W))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Acc_X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Acc_Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Acc_Z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_Vel_X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_Vel_Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_Vel_Z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'JY901S_Ang_Z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'UWB_X))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'UWB_Y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <robomaster>) istream)
  "Deserializes a message object of type '<robomaster>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Motor_M3508_ID01_W) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Motor_M3508_ID02_W) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Motor_M3508_ID03_W) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Motor_M3508_ID04_W) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Acc_X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Acc_Y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Acc_Z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_Vel_X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_Vel_Y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_Vel_Z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_Y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'JY901S_Ang_Z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'UWB_X) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'UWB_Y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<robomaster>)))
  "Returns string type for a message object of type '<robomaster>"
  "robomaster_msgs/robomaster")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'robomaster)))
  "Returns string type for a message object of type 'robomaster"
  "robomaster_msgs/robomaster")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<robomaster>)))
  "Returns md5sum for a message object of type '<robomaster>"
  "f486166047ceb697ecb8097101edead7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'robomaster)))
  "Returns md5sum for a message object of type 'robomaster"
  "f486166047ceb697ecb8097101edead7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<robomaster>)))
  "Returns full string definition for message of type '<robomaster>"
  (cl:format cl:nil "# 电机的线速度~%float32 Motor_M3508_ID01_W~%float32 Motor_M3508_ID02_W~%float32 Motor_M3508_ID03_W~%float32 Motor_M3508_ID04_W~%~%# JY901S角加速度~%float32 JY901S_Acc_X~%float32 JY901S_Acc_Y~%float32 JY901S_Acc_Z~%# JY901S角速度~%float32 JY901S_Ang_Vel_X~%float32 JY901S_Ang_Vel_Y~%float32 JY901S_Ang_Vel_Z~%# JY901S角度~%float32 JY901S_Ang_X~%float32 JY901S_Ang_Y~%float32 JY901S_Ang_Z~%~%# UWB~%float32 UWB_X~%float32 UWB_Y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'robomaster)))
  "Returns full string definition for message of type 'robomaster"
  (cl:format cl:nil "# 电机的线速度~%float32 Motor_M3508_ID01_W~%float32 Motor_M3508_ID02_W~%float32 Motor_M3508_ID03_W~%float32 Motor_M3508_ID04_W~%~%# JY901S角加速度~%float32 JY901S_Acc_X~%float32 JY901S_Acc_Y~%float32 JY901S_Acc_Z~%# JY901S角速度~%float32 JY901S_Ang_Vel_X~%float32 JY901S_Ang_Vel_Y~%float32 JY901S_Ang_Vel_Z~%# JY901S角度~%float32 JY901S_Ang_X~%float32 JY901S_Ang_Y~%float32 JY901S_Ang_Z~%~%# UWB~%float32 UWB_X~%float32 UWB_Y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <robomaster>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <robomaster>))
  "Converts a ROS message object to a list"
  (cl:list 'robomaster
    (cl:cons ':Motor_M3508_ID01_W (Motor_M3508_ID01_W msg))
    (cl:cons ':Motor_M3508_ID02_W (Motor_M3508_ID02_W msg))
    (cl:cons ':Motor_M3508_ID03_W (Motor_M3508_ID03_W msg))
    (cl:cons ':Motor_M3508_ID04_W (Motor_M3508_ID04_W msg))
    (cl:cons ':JY901S_Acc_X (JY901S_Acc_X msg))
    (cl:cons ':JY901S_Acc_Y (JY901S_Acc_Y msg))
    (cl:cons ':JY901S_Acc_Z (JY901S_Acc_Z msg))
    (cl:cons ':JY901S_Ang_Vel_X (JY901S_Ang_Vel_X msg))
    (cl:cons ':JY901S_Ang_Vel_Y (JY901S_Ang_Vel_Y msg))
    (cl:cons ':JY901S_Ang_Vel_Z (JY901S_Ang_Vel_Z msg))
    (cl:cons ':JY901S_Ang_X (JY901S_Ang_X msg))
    (cl:cons ':JY901S_Ang_Y (JY901S_Ang_Y msg))
    (cl:cons ':JY901S_Ang_Z (JY901S_Ang_Z msg))
    (cl:cons ':UWB_X (UWB_X msg))
    (cl:cons ':UWB_Y (UWB_Y msg))
))
