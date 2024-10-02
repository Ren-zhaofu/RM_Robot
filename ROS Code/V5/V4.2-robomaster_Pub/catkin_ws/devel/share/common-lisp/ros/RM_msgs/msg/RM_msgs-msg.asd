
(cl:in-package :asdf)

(defsystem "RM_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RM" :depends-on ("_package_RM"))
    (:file "_package_RM" :depends-on ("_package"))
  ))