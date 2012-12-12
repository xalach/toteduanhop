; ~~~~~~~ CLASS ABSTRAITE COMBINAISON ENUMERATEUR ~~~~~~~~~

(defclass combinaision-enumerator (abstract-enumerator) ()
  (:documentation "énumérateur qui dépend au moins une autre énumérateur"))

(defgeneric sous-enumerators (combinaison-enumerator)
  (:documentation "les enumerateurs le combinaison-enumerator est dépendant"))

(defmethod init-enumerator :after ((e combinaison-enumerator))
  (mapc #’init-enumerator (combinaison-enumerators e)))