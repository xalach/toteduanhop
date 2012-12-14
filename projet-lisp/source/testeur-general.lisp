; ######## ENUMERATEUR ABSTRAIT ########"

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
; # Class abstraire qui représente 
; # un énumérateur d'énumérateurs

(defclass combinaision-enumerator (abstract-enumerator) ()
  (:documentation "énumérateur qui dépend au moins une autre énumérateur"))

(defmethod init-enumerator :after ((e combinaison-enumerator))
  (mapc #'init-enumerator (sous-enumerators e)))


; ############# COMBINAISON N-NAIRE ENUMERATEUR ##########

(defclass nnaire-combinaison-enumerator (combinaison-enumerator)
  ((depends :type list :initarg :depends :reader sous-enumerators))
  (:documentation "énumérateur qui dépend à plusierus autres énumérateurs"))


; ############ ENUMERATEUR PARALLELE ###############

(defclass parallele-enumerator (nnaire-combinaison-enumerator)
  ())

; test next-element-p des sous enumerators via l'accesseur en lecture
(defmethod next-element-p ((e parallele-enumerator))
  (every #'next-element-p (sous-enumerators e)))

(defmethod next-element ((e parallele-enumerator))
  (loop
     for enumerator
     in (sous-enumerators e)
     collect (next-element enumerator)))

(defmethod init-enumerator ((e parallele-enumerator))
  (every #'init-enumerator (sous-enumerators e)))

(defmethod copy-enumerator ((e parallele-enumerator))
  (let ((nl '()))  ; créer une nouvelle liste d'énumérateur
    (loop
      for enumerator
	in (sous-enumerators e)
      collect (setf nl (cons (copy-enumerator enumerator) nl)))
    (make-instance 'parallele-enumerator :depends nl)))

(defmethod call-enumerator ((e abstract-enumerator))
  (let ((l '()))  ; liste des resultats
    (loop
      for enumerator
	in (sous-enumerators e) collect 
	  (multiple-value-bind (v r) (next-element enumerator)
	    (if (not r)
		(return (values NIL NIL))
		(setf l (cons v l)))))
    (values l T)))

(defun make-parallele-enumerator (&rest enums)
  (make-instance 'parallele-enumerator :depends enums))


; ############ COMBINAISON U-NAIRE ENUMERATOR #########

(defclass unaire-combinaison-enumerator (combinaison-enumerator)
  ((depend 
  	:type abstract-enumerator 
  	:initarg :depend 
  	:reader depend))
  (:documentation "énumérateur qui dépend à un seul autre énumérateur"))

(defmethod init-enumerator ((e unaire-combinaison-enumerator))
  (init-enumerator (depend e)))

(defmethod copy-enumerator ((e unaire-combinaison-enumerator))
	(make-instance 'unaire-combinaison-enumerator :depend (copy-enumerator (depend e))))

(defmethod next-element-p ((e unaire-combinaison-enumerator))
  (next-element-p (depend e)))

(defmethod next-element-p ((e unaire-combinaison-enumerator))
  (next-element (depend e)))
  

; ########## FILTRAGE ENUMERATEUR ##############

(defclass filtrage-enumerator (unaire-combinaison-enumerator fun-mixin)
  ())

(defmethod init-enumerator ((e filtrage-enumerator))
  (init-enumerator (depend e)))

(defmethod init-enumerator ((e filtrage-enumerator))
  (init-enumerator (depend e)))

(defmethod copy-enumerator ((e filtrage-enumerator))
  (make-instance 'filtrage-enumerator :depend (copy-enumerator (depend e)) :fun (fun e)))

(defmethod next-element-p ((e filtrage-enumerator))
  (let ((ce (depend e)))    ; travail avec une copie
    (do ((fin T)) ((not fin))
      (multiple-value-bind (v trv) (call-enumerator ce)
	(setf fin trv)
	(if (funcall (fun e) v)
	    (return T)))))
  NIL)

(defmethod next-element ((e filtrage-enumerator))
  (do ((fin T) (v)) ((not fin))
    (if (funcall (fun e) (setf v (next-element (depend e))))
	(return v))))

(defun make-filtrage-enumerator (enum filter-fun)
  (make-instance 'filtrage-enumerator :depend enum :fun filter-fun))
  

; ########## MEMOIRE ENUMERATEUR ##############

(defclass memo-enumerator (unaire-combinaison-enumerator)
  ((memo :accessor memo :initform NIL))
  (:documentation "énumérateur avec une memoire"))
  
(defgeneric unset-memo-object (e)
	(:documentation "desaffecte le créneau mémoire"))
	
(defmethod unset-memo-object ((e memo-enumerator))
	(with-slots (memo) e
		(setf memo NIL)))

(defmethod init-enumerator ((e memo-enumerator))
  (init-enumerator (depend e))
  (unset-memo-object e))

(defmethod next-element :around ((e memo-enumerator))
	(if (not (memo e))
		(setf (memo e) (call-next-method))
		memo))

(defun make-memo-enumerator (enum)
	(make-instance 'memo-enumerator :depend e))
