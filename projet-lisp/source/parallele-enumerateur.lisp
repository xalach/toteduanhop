(defclass parallele-enumerator (nnaire-combinaison-enumerator)
  ())

(defmethod next-element-p ((e parallel-enumerator))
  (every #’next-element-p
	   (sous-enumerators e)))

(defmethod next-element ((e parallel-enumerator))
  (loop
     for enumerator
     in (sous-enumerators e)
     collect (next-element enumerator)))

; des methodes à implémenter

(defmethod init-enumerator ((e parallel-enumerator))
  (:documentation "reinitialise et retourne ENUMERATOR"))

(defgeneric copy-enumerator ((e parallel-enumerator))
  (:documentation "return une copie reinitialisé de ENUMERATOR"))