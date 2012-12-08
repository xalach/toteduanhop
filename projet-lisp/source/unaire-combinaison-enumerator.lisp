(defclass unaire-combinaison-enumerator (combinaison-enumerator)
  ((depend
    :type abstract-enumerator
    :initarg :enum
    :reader enum))
  (:documentation "énumérateur qui dépend à un seul autre énumérateur"))