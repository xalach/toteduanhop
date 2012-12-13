; ~~~~~~~~ CLASS ABSTRAITE : ENUMERATEUR ABSTRAIT ~~~~~~~~~~~~~

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
      (values NIL NIL)))

(defmethod init-enumerator ((e abstract-enumerator))
  e) 
  

; ############# LISTE ENUMERATEUR ################

(defun ncirc (l) (nconc l l))
(defun circ (l) (ncirc (copy-list l)))

(defclass list-enumerator (abstract-enumerator)
  ((enum-list :initarg :enum-list :initform '())   
   (init-list :initarg :enum-list :initform '())))   

(defun make-list-enumerator (l &optional (circp nil))
  (when circp
    (progn
      (setf l (circ l))
      (setf *print-cirlcle* t))) 
    (make-instance 'list-enumerator :enum-list l :enum-list l)))

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



; ############ ENUMERATEUR INDUCTIF ###############

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

(defmethod copy-enumerator ((e inductif-enumerateur))
  (with-slots ((init  init-value)) e
    (make-instance 'inductif-enumerateur :init-value init :current-value init)))

(defmethod next-element-p ((e inductif-enumerateur))
  t)

(defmethod next-element ((e inductif-enumerateur))
  (setf (current-value e) (funcall (fun e) (current-value e))))

(defun make-inductif-enumerateur (init-value fun &optional (current-value init-value))
  (make-instance 'inductif-enumerateur :fun fun :init-value init-value :current-value current-value))


; ############## COMBINAISON ENUMERATEUR #############

(defclass combinaision-enumerator (abstract-enumerator) ()
  (:documentation "énumérateur qui dépend au moins une autre énumérateur"))

(defgeneric sous-enumerators (combinaison-enumerator)
  (:documentation "les enumerateurs le combinaison-enumerator est dépendant"))

(defmethod init-enumerator :after ((e combinaison-enumerator))
  (mapc #'init-enumerator (combinaison-enumerators e)))