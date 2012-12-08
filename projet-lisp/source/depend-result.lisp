(defclass depend-result ()
  ((objet :accessor depend-objet)
  (trouve :accessor trouve-depend))
  (:documentation "enregistrer le résultat de call-enumerator que le(s) autre(s) a(ont) rerourné(s)"))

(defmethod set-depend-result
((result depend-result)
  (e abstract-enumerator))
  (multiple-value-bind (objet trouve)
    (call-enumerator e)
  (setf (trouve-depend result) trouve)
  (if trouve
    (setf (depend-objet result) objet)
    (slot-makunbound result ’objet))))

(defun make-depend-result ()
  (make-instance ’depend-result))