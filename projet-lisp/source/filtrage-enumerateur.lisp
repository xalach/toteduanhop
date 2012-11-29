(defclass filtrage-enumerateur (unary-relying-enumerateur fun-mixin)
  ())

(defmethod skip-to-next ((e filtrage-enumerateur))
  (loop
     while (enum-found (enum e))
     until (funcall (fun e) (enum-object (enum e)))
    do (set-memo-res (enum e))))

(defmethod init-enumerator :after ((e filtrage-enumerateur))
  (skip-to-next e))

(defmethod next-element-p ((e filtrage-enumerateur))
  (enum-found (enum e)))

(defmethod next-element ((e filtrage-enumerator))
  (prog1
      (enum-object (enum e))
    (set-memo-res (enum e))
    (skip-to-next e)))

(defmethod make-filtrage-enumerateur ((e abstract-enumerator) filter-fun)
  (init-enumerator
   (make-instance
    ’filtrage-enumerateur
     :enum (make-memo-enumerateur e)
     :fun filter-fun)))