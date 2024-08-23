
(cl:in-package :asdf)

(defsystem "robomaster_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "robomaster" :depends-on ("_package_robomaster"))
    (:file "_package_robomaster" :depends-on ("_package"))
  ))