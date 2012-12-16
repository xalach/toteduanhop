; ######## ENUMERATEUR ABSTRAIT ########"

(defclass abstract-enumerator () ())

(defgeneric init-enumerator (enumerator)
  (:documentation "reinitialise et retourne ENUMERATOR"))

(defgeneric copy-enumerator (enumerator)
  (:documentation "return une copie non reinitialisé de ENUMERATOR"))

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
   (init-list :initarg :init-list :initform '())))   

(defun make-list-enumerator (l &optional (circp nil))
  (when circp
    (progn
      (setf l (circ l))
      (setf *print-cirlcle* t))) 
    (make-instance 'list-enumerator :enum-list l :init-list l)))

(defmethod init-enumerator ((e list-enumerator))
  (with-slots (enum-list init-list) e
    (setf enum-list init-list))
  e)

(defmethod copy-enumerator ((e list-enumerator))
  (with-slots (init-list enum-list) e
    (make-instance 'list-enumerator :init-list init-list :enum-list enum-list)))

(defmethod next-element-p ((e list-enumerator))
  (not (endp (slot-value e 'enum-list))))

(defmethod next-element ((e list-enumerator))
  (with-slots (enum-list) e
    (prog1
     (car enum-list)
     (setf enum-list (cdr enum-list)))))


; ###########################################
; ############ FONCTION MIXIN ###############

(defclass fun-mixin ()
  ((fun :initarg :fun :reader fun)))
  

; ################################################# 
; ############ ENUMERATEUR INDUCTIF ###############

(defclass inductif-enumerator (abstract-enumerator fun-mixin) 
  ((init-value 
    :initarg :init-value 
    :accessor init-value) 
   (current-value 
    :initarg :current-value 
    :accessor current-value)))

(defmethod init-enumerator ((e inductif-enumerator))
  (setf (current-value e) (init-value e))
  e)

(defmethod copy-enumerator ((e inductif-enumerator))
  (with-slots (init-value current-value fun) e
    (make-instance 'inductif-enumerator :init-value init-value :current-value current-value :fun fun)))

(defmethod next-element-p ((e inductif-enumerator))
  t)

(defmethod next-element ((e inductif-enumerator))
  (setf (current-value e) (funcall (fun e) (current-value e))))

(defun make-inductif-enumerator (init-value fun &optional (current-value init-value))
  (make-instance 'inductif-enumerator :fun fun :init-value init-value :current-value current-value))
  

; ######################################################## 
; ############ ENUMERATEUR MODULO INDUCTIF ###############
  
(defclass inductive-modulo-enumerator (inductive-enumerator)
  ((mod-fun :initarg :mod-fun
    :reader mod-fun)))

(defmethod init-enumerator :after ((e inductive-modulo-enumerator))
  (setf (current-value e)
    (funcall
    (mod-fun e)
    (current-value e)))
  e)

(defmethod next-element :after ((e inductive-modulo-enumerator))
  (setf (current-value e)
    (funcall
    (mod-fun e)
    (current-value e))))

(defun make-inductive-modulo-enumerator (initial-value fun mod-fun &optional current-value)
  (unless current-value
    (setf current-value initial-value))
  (make-instance
  'inductive-modulo-enumerator
  :fun fun
  :mod-fun mod-fun
  :initial-value initial-value
  :current-value current-value))


; ####################################################
; ############## COMBINAISON ENUMERATEUR #############

; 		~~~~~~~~~ Enumerateur N-naire ~~~~~~~~~~~

(defclass nnaire-combinaison-enumerator (abstract-enumerator)
  ((depends :type list :initarg :depends :reader sous-enumerators))
  (:documentation "énumérateur qui dépend à plusierus autres énumérateurs"))
  
(defmethod next-element ((e nnaire-combinaison-enumerator))
  (loop
     for enumerator
     in (sous-enumerators e)
     collect (next-element enumerator)))
     
(defmethod next-element-p ((e nnaire-combinaison-enumerator))
  (every #'next-element-p (sous-enumerators e)))

(defmethod init-enumerator ((e nnaire-combinaison-enumerator))
  (every #'init-enumerator (sous-enumerators e))
  e)

; 		~~~~~~~~~ Enumerateur U-naire ~~~~~~~~~~~ 
  
(defclass unaire-combinaison-enumerator (abstract-enumerator)
  ((depend 
  	:type abstract-enumerator 
  	:initarg :depend 
  	:reader depend))
  (:documentation "énumérateur qui dépend à un seul autre énumérateur"))

(defmethod init-enumerator ((e unaire-combinaison-enumerator))
  (init-enumerator (depend e))
  e)

(defmethod copy-enumerator ((e unaire-combinaison-enumerator))
	(make-instance 'unaire-combinaison-enumerator :depend (copy-enumerator (depend e))))

(defmethod next-element-p ((e unaire-combinaison-enumerator))
  (next-element-p (depend e)))

(defmethod next-element ((e unaire-combinaison-enumerator))
  (next-element (depend e)))


; ##################################################
; ############ ENUMERATEUR PARALLELE ###############

(defclass parallele-enumerator (nnaire-combinaison-enumerator)
  ())

(defmethod copy-enumerator ((e parallele-enumerator))
  (let ((nl '()))  ; créer une nouvelle liste d'énumérateur
    (loop
      for enumerator
	in (sous-enumerators e)
      collect (setf nl (cons (copy-enumerator enumerator) nl)))
    (make-instance 'parallele-enumerator :depends nl)))

(defmethod call-enumerator ((e parallele-enumerator))
  (let ((l '()))  ; liste des resultats
    (loop
      for enumerator
	in (sous-enumerators e) collect 
	  (multiple-value-bind (v r) (call-enumerator enumerator)
	    (if (not r)
		(progn
		  (setf l NIL)
		  (return))
		(setf l (cons v l)))))
    (if (not l)
	(values NIL NIL)
	(values l T))))

(defun make-parallele-enumerator (&rest enums)
  (make-instance 'parallele-enumerator :depends enums))

  
; ##############################################
; ########## FILTRAGE ENUMERATEUR ##############

(defclass filtrage-enumerator (unaire-combinaison-enumerator fun-mixin)
  ())

(defmethod copy-enumerator ((e filtrage-enumerator))
  (make-instance 'filtrage-enumerator :depend (copy-enumerator (depend e)) :fun (fun e)))

(defmethod next-element-p ((e filtrage-enumerator))
  (let ((ce (copy-enumerator (depend e))) (find NIL))    ; travail avec une copie non initializé
    (do ((fin T)) ((not fin))
      (multiple-value-bind (v r) (call-enumerator ce)
	(setf fin r)
	(when (funcall (fun e) v)
	  (progn
	    (setf find T)
	    (return)))))
    (or find NIL)))

(defmethod next-element ((e filtrage-enumerator))
  (let ((v NIL))
    (do ((fin T)) ((not fin))
      (setf v (next-element (depend e)))
      (if (funcall (fun e) v)
	  (return v)))))

(defmethod call-enumerator ((e filtrage-enumerator))
  (if (next-element-p e)
      (values (next-element e) T)
      (values NIL NIL)))

(defun make-filtrage-enumerator (enum filter-fun)
  (make-instance 'filtrage-enumerator :depend enum :fun filter-fun))
  

; #############################################
; ########## MEMOIRE ENUMERATEUR ##############

(defclass memo-enumerator (unaire-combinaison-enumerator)
  ((memo :accessor memo :initform NIL))
  (:documentation "énumérateur avec une memoire"))
  
(defgeneric unset-memo-object (e)
  (:documentation "desaffecte le créneau mémoire"))
	
(defmethod unset-memo-object ((e memo-enumerator))
  (setf (memo e) NIL)))

(defmethod init-enumerator ((e memo-enumerator))
  (init-enumerator (depend e))
  (unset-memo-object e)
  e)

(defmethod next-element-p :around ((e memo-enumerator))
  (if (not (memo e))
      (call-next-method)
      T))

(defmethod next-element :around ((e memo-enumerator))
  (if (not (memo e))
      (setf (memo e) (call-next-method))
      (memo e)))

(defun make-memo-enumerator (enum)
  (make-instance 'memo-enumerator :depend (copy-enumerator enum)))



; ###################################################
; ########## CONCATENATION ENUMERATEUR ##############
	
(defclass conca-enumerator (nnaire-combinaison-enumerator)
	((next-elements
	:initform nil
	:accessor next-elements))
	(:documentation "concaténation les listes que le sous énuméteur ont énuméré"))

(defmethod skip-to-next-non-null ((e conca-enumerator))
	(loop
	  until (next-elements e)
	  while (next-element-p (depend e))
	  do (setf (next-elements e)
		   (next-element (depend e)))))

(defmethod init-enumerator :after ((e conca-enumerator))
	(skip-to-next-non-null e))

(defmethod next-element-p ((e conca-enumerator))
	(next-elements e))

(defmethod next-element ((e conca-enumerator))
	(prog1
		(pop (next-elements e))
	(skip-to-next-non-null e)))

(defun make-conca-enumerator (enum)
  (make-instance 'conca-enumerator :depend (copy-enumerator enum)))


; #############################################
; ########## PRODUIT ENUMERATEUR ##############

(defclass produit-enumerator (nnaire-combinaison-enumerator fun-mixin)())

(defmethod make-produit-enumerator (fun (depends (eql nil)))
  (make-empty-enumerator))

(defmethod make-produit-enumerator (fun (depends list))
  (let ((v (map 'vector #'make-memo-enumerator depends)))
    (if (every #'trouve-depend v)
	(make-instance 'produit-enumerateur :sous-enumerators v :fun fun)
	(make-empty-enumerator))))

(defmethod depend-i ((e produit-enumerator) (i integer))
  (aref (sous-enumerators e) i))

(defmethod next-element-p ((e produit-enumerator))
	(trouve-depend (depend-i e 0)))

(defmethod next-element ((e produit-enumerator))
  (let ((depends (sous-enumerators e)))
    (prog1
	(apply
	 (fun e)
	 (map ’list
	       (lambda (ei)
		 (enum-object ei)) enums))
      (let ((index (1- (length enums))))
	(set-memo-result (depend-i e index))
	(loop 
	  until (trouve-depend
		 (depend-i e index))
	  until (zerop index)
	  do (init-enumerator
	      (depend-i e index))
	  do (set-memo-result
	      (depend-i e (decf index))))))))
