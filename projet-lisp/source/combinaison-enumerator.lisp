; ~~~~~~~ CLASS ABSTRAITE COMBINAISON ENUMERATEUR ~~~~~~~~~

(defclass combinaision-enumerator (abstract-enumerator) ()
  (:documentation "énumérateur qui dépend au moins une autre énumérateur"))

(defgeneric sous-enumerators (combinaison-enumerator)
  (:documentation "retourne les enumérateurs de la combinaison ?"))

(defmethod init-enumerator :after ((e combinaison-enumerator))
  (mapc #'init-enumerator (combinaison-enumerators e)))
  
; d'ou vient combinaison-enumerators ???
