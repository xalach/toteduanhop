(defclass parallele-enumerateur (nary-relying-enumerator)
  ())

(defmethod next-element-p ((e parallel-enumerator))
  (every #’next-element-p
	   (underlying-enumerators e)))

(defmethod next-element ((e parallel-enumerator))
  (loop
     for enumerator
     in (underlying-enumerators e)
     collect (next-element enumerator)))

; des methodes à implémenter

(defmethod init-enumerator ((e parallel-enumerator))
  (:documentation "reinitialise et retourne ENUMERATOR"))

(defgeneric copy-enumerator ((e parallel-enumerator))
  (:documentation "return une copie reinitialisé de ENUMERATOR"))