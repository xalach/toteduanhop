(defclass parallele-enumerator (nnaire-combinaison-enumerator)
  ())

(defmethod copy-enumerator ((e parallele-enumerator))
  (let ((nl '()))  ; créer une nouvelle liste d'énumérateur
    (loop
      for enumerator
	in (sous-enumerators e)
      collect (setf nl (cons (copy-enumerator enumerator) nl)))
    (make-instance 'parallele-enumerator :depends nl)))

(defmethod call-enumerator ((e abstract-enumerator))
  (let ((l '()))  ; liste des resultats
    (loop
      for enumerator
	in (sous-enumerators e) collect 
	  (multiple-value-bind (v r) (next-element enumerator)
	    (if (not r)
		(return (values NIL NIL))
		(setf l (cons v l)))))
    (values l T)))

(defun make-parallele-enumerator (&rest enums)
  (make-instance 'parallele-enumerator :depends enums))
