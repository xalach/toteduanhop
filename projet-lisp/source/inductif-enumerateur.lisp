(defclass fun-mixin ()
  ((fun :initarg :fun :reader fun)))


(defclass inductif-enumerateur 
      (abstract-enumerator fun-mixin) 
  ((init-value 
    :initarg :init-value 
    :accessor init-value) 
   (current-value 
    :initarg :current-value 
    :accessor current-value)))


(defmethod init-enumerator
    ((e inductif-enumerateur))
  (setf (current-value e)
	(init-value e))
  e)

(defmethod next-element-p
    ((e inductif-enumerateur))
  t)
(defmethod next-element
    ((e inductif-enumerateur))
  (setf
   (current-value e)
   (funcall
    (fun e)
    (current-value e))))

(defun make-inductif-enumerateur
    (init-value fun
     &optional current-value)
  (unless current-value
    (setf current-value init-value))
  (make-instance
   ’inductif-enumerateur
    :fun fun
    :init-value init-value
    :current-value current-value)
