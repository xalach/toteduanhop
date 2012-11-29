
;################### ABSTRACT ###################
;################################################

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
  
;################### LIST #######################
;################################################


(defpackage :list-enumerator
  (:export *)
  (:use :common-lisp)
  (:import-from :abstract-enumerator *))
(in-package :list-enumerator)

;voir comment importer facilement les fonctionnalités

; fonctionnera t'elle avec liste en cycle ?
; réponse de Quy: oui, mon cher Arnaud :P
; réponse d'arnaud : super ^^ faudra l'introduire dans
;                    un jeu d'essaie
(defun ncirc (l) (nconc l l))
(defun circ (l) (ncirc (copy-list l)))

(defclass list-enumerator (abstract-enumerator)
  ((enum-list :initarg :enum-list :initform '())
   (init-list :initarg :enum-list :initform '())))

; circp : definir si listre ciclique
(defun make-list-enumerator (l &optional (circp nil))
  (when circp
    (setf l (circ l)))
  (make-instance 'list-enumerator :initial-list l :current-list l))


(defmethod init-enumerator ((e list-enumerator))
  (with-slots (enum-list init-list) e
    (setf enum-list init-list)))

(defmethod copy-enumerator ((e list-enumerator))
  (with-slots ((l init-list)) e
    (make-instance 'list-enumerator :enum-list l)))


(defmethod next-element-p ((e list-enumerator))
  (not (endp (slot-value e 'enum-list))))

(defmethod next-element ((e list-enumerator))
  (with-slots ((e enum-list)) e
    (prog1
	(car e)
      (setf e (cdr e)))))
      
;################### INDUCTIF ###################
;################################################


; class mixin : defini la fonction d'induction
; pourquoi utiliser une classe mixin pour la fonction ?
(defclass fun-mixin ()
  ((fun :initarg :fun :reader fun)))


(defclass inductif-enumerateur (abstract-enumerator fun-mixin) 
  ((init-value 
    :initarg :init-value 
    :accessor init-value) 
   (current-value 
    :initarg :current-value 
    :accessor current-value)))


(defmethod init-enumerator ((e inductif-enumerateur))
  (setf (current-value e)
	(init-value e))
  e)

; pourquoi renvoyer toujours vrai ?
; si la fonction traite les valeur inferieur à 10
; et que current-value est à 12, ça renvoie NIL
(defmethod next-element-p ((e inductif-enumerateur))
  t)

(defmethod next-element ((e inductif-enumerateur))
  (setf (current-value e) (funcall (fun e) (current-value e))))

; mis en place de valeur par défault pour current-value
; pour eviter de faire un "unless" dans la fonction
(defun make-inductif-enumerateur (init-value fun &optional (current-value init-value))
  (make-instance ’inductif-enumerateur :fun fun :init-value init-value :current-value current-value)
  
  
;################### INDUCTIF ###################
;################################################
