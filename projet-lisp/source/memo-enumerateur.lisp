(defclass memo-enumerator (unaire-combinaison-enumerator)
  ((memo :accessor memo :initform NIL))
  (:documentation "énumérateur avec une memoire"))
  
(defgeneric unset-memo-object (e)
	(:documentation "desaffecte le créneau mémoire"))
	
(defmethod unset-memo-object ((e memo-enumerator))
	(with-slots (memo) e
		(setf memo NIL)))

(defmethod init-enumerator ((e memo-enumerator))
  (init-enumerator (depend e))
  (unset-memo-object e))

(defmethod next-element :around ((e memo-enumerator))
	(if (not (memo e))
		(setf (memo e) (call-next-method))
		memo))

(defun make-memo-enumerator (enum)
	(make-instance 'memo-enumerator :depend e))
