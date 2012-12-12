; ~~~~~~~~~ CLASS COMBINAISON UNAIRE ENUMERATOR ~~~~~~~~~~

(defclass unaire-combinaison-enumerator (combinaison-enumerator)
  ((depend 
  	:type abstract-enumerator 
  	:initarg :depend 
  	:reader depend))
  (:documentation "énumérateur qui dépend à un seul autre énumérateur"))