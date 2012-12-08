(defclass produit-enumerator (unaire-combinaison-enumerator fun-mixin)())

(defmethod make-produit-enumerator (fun (depends (eql nil)))
  (make-empty-enumerator))

(defmethod make-produit-enumerator (fun (depends list))
  (let ((v (map ’vector #’make-memo-enumerator depends)))
    (if (every #’trouve-depend v)
	(make-instance ’produit-enumerateur :sous-enumerators v :fun fun)
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