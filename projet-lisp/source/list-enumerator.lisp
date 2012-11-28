(defpackage :list-enumerator
  (:export *)
  (:use :common-lisp)
  (:import-from :abstract-enumerator *))
(in-package :list-enumerator)

;voir comment importer facilement les fonctionnalités

; fonctionnera t'elle avec liste en cycle ?
; réponse de Quy: oui, mon cher Arnaud :P
(defun ncirc (l) (nconc l l))
(defun circ (l) (ncirc (copy-list l)))

(defun make-list-enumerator
    (l &optional (circ nil))
  (when circ
    (setf l (circ l)))
  (make-instance
   'list-enumerator
    :initial-list l :current-list l))
    
    

(defclass list-enumerator (abstract-enumerator)
  ((enum-list :initarg :enum-list :initform '())
   (init-list :initarg :enum-list :initform '())))

(defmethod init-enumerator ((e list-enumerator))
  (setf (slot-value e 'enum-list) (slot-value e 'init-list)))

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
