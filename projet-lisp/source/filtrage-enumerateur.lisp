(defclass filtrage-enumerator (unaire-combinaison-enumerator fun-mixin)
  ())

(defmethod skip-to-next ((e filtrage-enumerator))
  (loop
     while (trouve-depend (depend e))
     until (funcall (fun e) (objet-depend (depend e)))
    do (set-memo-res (enum e))))

(defmethod init-enumerator :after ((e filtrage-enumerateur))
  (skip-to-next e))

(defmethod next-element-p ((e filtrage-enumerateur))
  (trouve-depend (depend e)))

(defmethod next-element ((e filtrage-enumerator))
  (prog1
      (obejet-depend (depend e))
    (set-memo-res (depend e))
    (skip-to-next e)))

(defmethod make-filtrage-enumerateur ((e abstract-enumerator) filter-fun)
  (init-enumerator
   (make-instance
    ’filtrage-enumerateur
     :depend (make-memo-enumerator e)
     :fun filter-fun)))