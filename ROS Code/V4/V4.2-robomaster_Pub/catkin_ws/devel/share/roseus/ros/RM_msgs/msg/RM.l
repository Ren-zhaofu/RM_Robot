;; Auto-generated. Do not edit!


(when (boundp 'RM_msgs::RM)
  (if (not (find-package "RM_MSGS"))
    (make-package "RM_MSGS"))
  (shadow 'RM (find-package "RM_MSGS")))
(unless (find-package "RM_MSGS::RM")
  (make-package "RM_MSGS::RM"))

(in-package "ROS")
;;//! \htmlinclude RM.msg.html


(defclass RM_msgs::RM
  :super ros::object
  :slots (_Motor_M3508_ID01_W _Motor_M3508_ID02_W _Motor_M3508_ID03_W _Motor_M3508_ID04_W _JY901S_Acc_X _JY901S_Acc_Y _JY901S_Acc_Z _JY901S_Ang_Vel_X _JY901S_Ang_Vel_Y _JY901S_Ang_Vel_Z _JY901S_Ang_X _JY901S_Ang_Y _JY901S_Ang_Z _UWB_X _UWB_Y ))

(defmethod RM_msgs::RM
  (:init
   (&key
    ((:Motor_M3508_ID01_W __Motor_M3508_ID01_W) 0)
    ((:Motor_M3508_ID02_W __Motor_M3508_ID02_W) 0)
    ((:Motor_M3508_ID03_W __Motor_M3508_ID03_W) 0)
    ((:Motor_M3508_ID04_W __Motor_M3508_ID04_W) 0)
    ((:JY901S_Acc_X __JY901S_Acc_X) 0.0)
    ((:JY901S_Acc_Y __JY901S_Acc_Y) 0.0)
    ((:JY901S_Acc_Z __JY901S_Acc_Z) 0.0)
    ((:JY901S_Ang_Vel_X __JY901S_Ang_Vel_X) 0.0)
    ((:JY901S_Ang_Vel_Y __JY901S_Ang_Vel_Y) 0.0)
    ((:JY901S_Ang_Vel_Z __JY901S_Ang_Vel_Z) 0.0)
    ((:JY901S_Ang_X __JY901S_Ang_X) 0.0)
    ((:JY901S_Ang_Y __JY901S_Ang_Y) 0.0)
    ((:JY901S_Ang_Z __JY901S_Ang_Z) 0.0)
    ((:UWB_X __UWB_X) 0.0)
    ((:UWB_Y __UWB_Y) 0.0)
    )
   (send-super :init)
   (setq _Motor_M3508_ID01_W (round __Motor_M3508_ID01_W))
   (setq _Motor_M3508_ID02_W (round __Motor_M3508_ID02_W))
   (setq _Motor_M3508_ID03_W (round __Motor_M3508_ID03_W))
   (setq _Motor_M3508_ID04_W (round __Motor_M3508_ID04_W))
   (setq _JY901S_Acc_X (float __JY901S_Acc_X))
   (setq _JY901S_Acc_Y (float __JY901S_Acc_Y))
   (setq _JY901S_Acc_Z (float __JY901S_Acc_Z))
   (setq _JY901S_Ang_Vel_X (float __JY901S_Ang_Vel_X))
   (setq _JY901S_Ang_Vel_Y (float __JY901S_Ang_Vel_Y))
   (setq _JY901S_Ang_Vel_Z (float __JY901S_Ang_Vel_Z))
   (setq _JY901S_Ang_X (float __JY901S_Ang_X))
   (setq _JY901S_Ang_Y (float __JY901S_Ang_Y))
   (setq _JY901S_Ang_Z (float __JY901S_Ang_Z))
   (setq _UWB_X (float __UWB_X))
   (setq _UWB_Y (float __UWB_Y))
   self)
  (:Motor_M3508_ID01_W
   (&optional __Motor_M3508_ID01_W)
   (if __Motor_M3508_ID01_W (setq _Motor_M3508_ID01_W __Motor_M3508_ID01_W)) _Motor_M3508_ID01_W)
  (:Motor_M3508_ID02_W
   (&optional __Motor_M3508_ID02_W)
   (if __Motor_M3508_ID02_W (setq _Motor_M3508_ID02_W __Motor_M3508_ID02_W)) _Motor_M3508_ID02_W)
  (:Motor_M3508_ID03_W
   (&optional __Motor_M3508_ID03_W)
   (if __Motor_M3508_ID03_W (setq _Motor_M3508_ID03_W __Motor_M3508_ID03_W)) _Motor_M3508_ID03_W)
  (:Motor_M3508_ID04_W
   (&optional __Motor_M3508_ID04_W)
   (if __Motor_M3508_ID04_W (setq _Motor_M3508_ID04_W __Motor_M3508_ID04_W)) _Motor_M3508_ID04_W)
  (:JY901S_Acc_X
   (&optional __JY901S_Acc_X)
   (if __JY901S_Acc_X (setq _JY901S_Acc_X __JY901S_Acc_X)) _JY901S_Acc_X)
  (:JY901S_Acc_Y
   (&optional __JY901S_Acc_Y)
   (if __JY901S_Acc_Y (setq _JY901S_Acc_Y __JY901S_Acc_Y)) _JY901S_Acc_Y)
  (:JY901S_Acc_Z
   (&optional __JY901S_Acc_Z)
   (if __JY901S_Acc_Z (setq _JY901S_Acc_Z __JY901S_Acc_Z)) _JY901S_Acc_Z)
  (:JY901S_Ang_Vel_X
   (&optional __JY901S_Ang_Vel_X)
   (if __JY901S_Ang_Vel_X (setq _JY901S_Ang_Vel_X __JY901S_Ang_Vel_X)) _JY901S_Ang_Vel_X)
  (:JY901S_Ang_Vel_Y
   (&optional __JY901S_Ang_Vel_Y)
   (if __JY901S_Ang_Vel_Y (setq _JY901S_Ang_Vel_Y __JY901S_Ang_Vel_Y)) _JY901S_Ang_Vel_Y)
  (:JY901S_Ang_Vel_Z
   (&optional __JY901S_Ang_Vel_Z)
   (if __JY901S_Ang_Vel_Z (setq _JY901S_Ang_Vel_Z __JY901S_Ang_Vel_Z)) _JY901S_Ang_Vel_Z)
  (:JY901S_Ang_X
   (&optional __JY901S_Ang_X)
   (if __JY901S_Ang_X (setq _JY901S_Ang_X __JY901S_Ang_X)) _JY901S_Ang_X)
  (:JY901S_Ang_Y
   (&optional __JY901S_Ang_Y)
   (if __JY901S_Ang_Y (setq _JY901S_Ang_Y __JY901S_Ang_Y)) _JY901S_Ang_Y)
  (:JY901S_Ang_Z
   (&optional __JY901S_Ang_Z)
   (if __JY901S_Ang_Z (setq _JY901S_Ang_Z __JY901S_Ang_Z)) _JY901S_Ang_Z)
  (:UWB_X
   (&optional __UWB_X)
   (if __UWB_X (setq _UWB_X __UWB_X)) _UWB_X)
  (:UWB_Y
   (&optional __UWB_Y)
   (if __UWB_Y (setq _UWB_Y __UWB_Y)) _UWB_Y)
  (:serialization-length
   ()
   (+
    ;; int16 _Motor_M3508_ID01_W
    2
    ;; int16 _Motor_M3508_ID02_W
    2
    ;; int16 _Motor_M3508_ID03_W
    2
    ;; int16 _Motor_M3508_ID04_W
    2
    ;; float32 _JY901S_Acc_X
    4
    ;; float32 _JY901S_Acc_Y
    4
    ;; float32 _JY901S_Acc_Z
    4
    ;; float32 _JY901S_Ang_Vel_X
    4
    ;; float32 _JY901S_Ang_Vel_Y
    4
    ;; float32 _JY901S_Ang_Vel_Z
    4
    ;; float32 _JY901S_Ang_X
    4
    ;; float32 _JY901S_Ang_Y
    4
    ;; float32 _JY901S_Ang_Z
    4
    ;; float32 _UWB_X
    4
    ;; float32 _UWB_Y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _Motor_M3508_ID01_W
       (write-word _Motor_M3508_ID01_W s)
     ;; int16 _Motor_M3508_ID02_W
       (write-word _Motor_M3508_ID02_W s)
     ;; int16 _Motor_M3508_ID03_W
       (write-word _Motor_M3508_ID03_W s)
     ;; int16 _Motor_M3508_ID04_W
       (write-word _Motor_M3508_ID04_W s)
     ;; float32 _JY901S_Acc_X
       (sys::poke _JY901S_Acc_X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Acc_Y
       (sys::poke _JY901S_Acc_Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Acc_Z
       (sys::poke _JY901S_Acc_Z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_Vel_X
       (sys::poke _JY901S_Ang_Vel_X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_Vel_Y
       (sys::poke _JY901S_Ang_Vel_Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_Vel_Z
       (sys::poke _JY901S_Ang_Vel_Z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_X
       (sys::poke _JY901S_Ang_X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_Y
       (sys::poke _JY901S_Ang_Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _JY901S_Ang_Z
       (sys::poke _JY901S_Ang_Z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _UWB_X
       (sys::poke _UWB_X (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _UWB_Y
       (sys::poke _UWB_Y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _Motor_M3508_ID01_W
     (setq _Motor_M3508_ID01_W (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _Motor_M3508_ID02_W
     (setq _Motor_M3508_ID02_W (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _Motor_M3508_ID03_W
     (setq _Motor_M3508_ID03_W (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _Motor_M3508_ID04_W
     (setq _Motor_M3508_ID04_W (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _JY901S_Acc_X
     (setq _JY901S_Acc_X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Acc_Y
     (setq _JY901S_Acc_Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Acc_Z
     (setq _JY901S_Acc_Z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_Vel_X
     (setq _JY901S_Ang_Vel_X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_Vel_Y
     (setq _JY901S_Ang_Vel_Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_Vel_Z
     (setq _JY901S_Ang_Vel_Z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_X
     (setq _JY901S_Ang_X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_Y
     (setq _JY901S_Ang_Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _JY901S_Ang_Z
     (setq _JY901S_Ang_Z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _UWB_X
     (setq _UWB_X (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _UWB_Y
     (setq _UWB_Y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get RM_msgs::RM :md5sum-) "97b056c437e37e3ccc8f73221431cb76")
(setf (get RM_msgs::RM :datatype-) "RM_msgs/RM")
(setf (get RM_msgs::RM :definition-)
      "# 电机的线速度
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
")



(provide :RM_msgs/RM "97b056c437e37e3ccc8f73221431cb76")


