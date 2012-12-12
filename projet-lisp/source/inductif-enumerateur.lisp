; class mixin : defini la fonction d'induction
; utiliser par d'autre classe comme filtrage-enumerator

;La fonction f est stocké dans le slot fun apporté par héritage de la classe fun-mixin.
;QA: C'est juste une classe abstraite (revoir page 131 du poly;)

; ~~~~~~~~~~~ CLASS ABSTRAITE : FUNCTION MIXIN ~~~~~~~~~~~~~

(defclass fun-mixin ()
  ((fun :initarg :fun :reader fun)))

; ~~~~~~~~~~~ CLASS : ENUMERATEUR INDUCTIF ~~~~~~~~~~~~~

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


(defmethod copy-enumerator ((e inductif-enumerateur))
  (with-slots ((init  init-value)) e
    (make-instance 'inductif-enumerateur :init-value init :current-value init)))

; renvois toujours vrai car cette enumerateur sort toujours une valeur
(defmethod next-element-p ((e inductif-enumerateur))
  t)


(defmethod next-element ((e inductif-enumerateur))
  (setf (current-value e) (funcall (fun e) (current-value e))))

; mis en place de valeur par défault pour current-value
; pour eviter de faire un "unless" dans la fonction
(defun make-inductif-enumerateur (init-value fun &optional (current-value init-value))
  (make-instance ’inductif-enumerateur :fun fun :init-value init-value :current-value current-value)
