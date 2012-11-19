(defpackage :abstract-enumerator (:use :common-lisp))
(in-package :abstract-enumerator)

(defclass abstract-enumerator () ())

(defgeneric init-enumerator (enumerator)
  (:documentation "reinitialise et retourne ENUMERATOR"))

(defgeneric copy-enumerator (enumerator)
  (:documentation "return une copie reinitialisé de ENUMERATOR"))

(defgeneric next-element-p (enumerator)
  (:documentation "retourne NIL si il n'y a pas de prochain element, sinon retourne un non NIL"))

(defgeneric next-element (enumerator)
  (:documentation "retourne le prochain élément et change pour le prochain"))

(defgeneric call-enumerator (enumerator)
  (:documentation "si il y a un prochain element e, retourne e et T et change pour le prochain element;
Autrement retourne NIL et NIL"))

(defmethod call-enumerator ((e abstract-enumerator))
  (if (next-element-p e)
      (values (next-element e) T)
      (values (NIL NIL))))

(defmethod init-enumerator ((e abstract-enumerator))
  e)