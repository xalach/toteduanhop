(defclass nnaire-combinaison-enumerator (combinaison-enumerator)
  ((depends :type list :initarg :depends :reader sous-enumerators))
  (:documentation "énumérateur qui dépend à plusierus autres énumérateurs"))