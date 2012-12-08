(defclass produit-enumerator
      (unaire-combinaison-enumerator fun-mixin)
  ())

(defmethod make-produit-enumerateur
    (fun (enums (eql nil)))
  (make-empty-enumerator))

(defmethod make-produit-enumerateur
    (fun (enums list))
  (let ((v (map
	    ’vector
	     #’make-memo-enumerateur
	       enums)))
    (if (every #’enum-found v)
	(make-instance
	 ’produit-enumerateur
	  :underlying-enumerators v
	  :fun fun)
	(make-empty-enumerator))))

(defmethod enum-i
    ((e produit-enumerateur) (i integer))
  (aref (underlying-enumerators e) i))

(defmethod next-element-p
    ((e produit-enumerateur))
  (enum-found (enum-i e 0)))

(defmethod next-element
    ((e produit-enumerateur))
  (let ((enums (underlying-enumerators e)))
    (prog1
	(apply
	 (fun e)
	 (map ’list
	       (lambda (ei)
		 (enum-object ei)) enums))
      (let ((index (1- (length enums))))
	(set-memo-res (enum-i e index))
	(loop 
	  until (enum-found
		 (enum-i e index))
	  until (zerop index)
	  do (init-enumerator
	      (enum-i e index))
	  do (set-memo-res
	      (enum-i e (decf index))))))))