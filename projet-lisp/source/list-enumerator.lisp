(defclass list-enumerator (abstract-enumerator)
  ((enum-list :initarg :enum-list :initform '())      ; --- la liste en cours d'énumération
   (init-list :initarg :enum-list :initform '())))    ; --- la liste initial

(defmethod init-enumerator ((e list-enumerator))
  (with-slots (enum-list init-list) e
    (setf enum-list init-list)))

(defmethod copy-enumerator ((e list-enumerator))
  (with-slots (init-list) e
    (make-instance 'list-enumerator :enum-list init-list)))


(defmethod next-element-p ((e list-enumerator))
  (not (endp (slot-value e 'enum-list))))

(defmethod next-element ((e list-enumerator))
  (with-slots (enum-list) e
    (prog1
     (car enum-list)
     (setf enum-list (cdr enum-list)))))

(defun make-list-enumerator (l)
  (init-enumerator
  (make-instance ’list-enumerator :initial-list l)))

; créer une liste circulaire avec ou sans destruction
(defun ncirc (l) 
  (setf (cdr (last l)) l))

(defun circ (l) (ncirc (copy-list l)))

; circp : definir si listre ciclique
(defun make-list-enumerator (l &optional (circp nil))
  (when circp
    (progn
      (setf l (circ l))
      (setf *print-cirlcle* t)))     ; rendre l'affiche circulaire
    (make-instance 'list-enumerator :init-list l :enum-list l))
