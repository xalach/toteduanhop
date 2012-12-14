(defclass conca-enumerator (nnaire-combinaison-enumerator)
	((next-elements
	:initform nil
	:accessor next-elements))
	(:documentation "concaténation les listes que le sous énuméteur ont énuméré"))

(defmethod skip-to-next-non-null ((e conca-enumerator))
	(loop
	  until (next-elements e)
	  while (next-element-p (depend e))
	  do (setf (next-elements e)
		   (next-element (depend e))

(defmethod init-enumerator :after ((e conca-enumerator))
	(skip-to-next-non-null e))

(defmethod next-element-p ((e conca-enumerator))
	(next-elements e))

(defmethod next-element ((e conca-enumerator))
	(prog1
		(pop (next-elements e))
	(skip-to-next-non-null e)))

(defun make-conca-enumerator (enum)
  (make-instance 'conca-enumerator :depend (copy-enumerator e)))