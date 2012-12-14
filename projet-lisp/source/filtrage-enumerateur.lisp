(defclass filtrage-enumerator (unaire-combinaison-enumerator fun-mixin)
  ())

(defmethod init-enumerator ((e filtrage-enumerator))
  (init-enumerator (depend e)))

(defmethod copy-enumerator ((e filtrage-enumerator))
  (make-instance 'filtrage-enumerator :depend (copy-enumerator (depend e))))

(defmethod next-element-p ((e filtrage-enumerator))
  (let ((ce (depend e)))    ; travail avec une copie
    (do ((fin T)) ((not fin))
      (multiple-value-bind (v trv) (call-enumerator ce)
	(setf fin trv)
	(if (funcall (fun e) v)
	    (return T)))))
  NIL)

(defmethod next-element ((e filtrage-enumerator))
  (do ((fin T) (v)) ((not fin))
    (if (funcall (fun e) (setf v (next-element (depend e))))
	(return v))))

(defun make-filtrage-enumerator (enum filter-fun)
  (make-instance 'filtrage-enumerator :depend enum :fun filter-fun))
