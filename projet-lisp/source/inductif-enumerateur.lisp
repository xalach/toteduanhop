; class mixin : defini la fonction d'induction
; utiliser par d'autre classe comme filtrage-enumerator

;La fonction f est stocké dans le slot fun apporté par héritage de la classe fun-mixin.
;QA: C'est juste une classe abstraite (revoir page 131 du poly;)

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

;QA: Le slot init-value contient la valeur initiale tandis que le slot current-value détient l'élément suivant à énumérer.
;Initialement, la valeur actuelle est la valeur initiale.
;Selon annoncé: une suite (sn)n∈N est d´efinie de mani`ere inductive avec une valeur initiale v et une fonction f qui calcule l’´el´ement suivant `a partir du pr´ec´edent.
;->ici, on peut toujours énumérer l'élément suivant à partir d'élément précédent, alors c'est normal que ça renvoie toujours vrai

; si la fonction traite les valeur inferieur à 10
; et que current-value est à 12, ça renvoie NIL
;QA: Ici, c'est une énumérateur simple donc on ne peut pas positionner sur un élément qu'on n'a pas encore crée.

(defmethod next-element-p ((e inductif-enumerateur))
  t)

(defmethod next-element ((e inductif-enumerateur))
  (setf (current-value e) (funcall (fun e) (current-value e))))

; mis en place de valeur par défault pour current-value
; pour eviter de faire un "unless" dans la fonction
(defun make-inductif-enumerateur (init-value fun &optional (current-value init-value))
  (make-instance ’inductif-enumerateur :fun fun :init-value init-value :current-value current-value)
