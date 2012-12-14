; sous class de combinaison qui contient une liste d'énumérateur

(defclass nnaire-combinaison-enumerator (combinaison-enumerator)
  ((depends :type list :initarg :depends :reader sous-enumerators))
  (:documentation "énumérateur qui dépend à plusierus autres énumérateurs"))
  
(defmethod next-element ((e nnaire-combinaison-enumerator))
  (loop
     for enumerator
     in (sous-enumerators e)
     collect (next-element enumerator)))
     
(defmethod next-element-p ((e nnaire-combinaison-enumerator))
  (every #'next-element-p (sous-enumerators e)))

(defmethod init-enumerator ((e nnaire-combinaison-enumerator))
  (every #'init-enumerator (sous-enumerators e)))
