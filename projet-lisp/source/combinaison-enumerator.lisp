; ~~~~~~~ CLASS ABSTRAITE COMBINAISON ENUMERATEUR ~~~~~~~~~

(defclass combinaision-enumerator (abstract-enumerator) ()
  (:documentation "énumérateur qui dépend au moins une autre énumérateur"))

(defgeneric sous-enumerators (combinaison-enumerator)
  (:documentation "retourne les enumérateurs de la combinaison ?"))

(defmethod init-enumerator :after ((e combinaison-enumerator))
  (mapc #'init-enumerator (combinaison-enumerators e)))
  
; d'ou vient combinaison-enumerators ???
;c'est une classe abstraite pour les deux autres classes abstraites (unaire-combinaison-enumerator et nnaire-combinaison-enumerator) afin d'implémenter les classes concrètes demandées.
; > je parlais pour cette ligne : (mapc #'init-enumerator (combinaison-enumerators e)))
; > est ce une erreur de frappe le "combinaison-enumerators" avec un "s" ?
; > mais comme c'est écrit un dirait une fonction 
