; ~~~~~~~~~ CLASS COMBINAISON UNAIRE ENUMERATOR ~~~~~~~~~~

(defclass unaire-combinaison-enumerator (combinaison-enumerator)
  ((depend 
  	:type abstract-enumerator 
  	:initarg :depend 
  	:reader depend))
  (:documentation "énumérateur qui dépend à un seul autre énumérateur"))

(defmethod init-enumerator ((e unaire-combinaison-enumerator))
  (init-enumerator (depend e)))

(defmethod copy-enumerator ((e unaire-combinaison-enumerator))
	(make-instance 'unaire-combinaison-enumerator :depend (copy-enumerator (depend e))))

(defmethod next-element-p ((e unaire-combinaison-enumerator))
  (next-element-p (depend e)))

(defmethod next-element-p ((e unaire-combinaison-enumerator))
  (next-element (depend e)))

