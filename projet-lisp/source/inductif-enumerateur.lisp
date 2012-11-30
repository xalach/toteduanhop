
; class mixin : defini la fonction d'induction
; utiliser par d'autre classe comme filtrage-enumerator
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
  (setf (current-value e) (init-value e))
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
