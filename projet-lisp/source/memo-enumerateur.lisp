(defclass memo-enumerateur
      (unary-relying-enumerator)
  ((enum-res :accessor enum-res
	     :initform (make-enum-res)))
  (:documentation
   "enumerateur avec une memoire"))

(defmethod make-memo-enumerateur
    ((e abstract-enumerator))
  (init-enumerator
   (make-instance
    ’memo-enumerateur
     :enum (copy-enumerator e))))

(defmethod set-memo-res
    ((e memo-enumerateur))
  (set-enum-res
   (enum-res e) (enum e)))

(defmethod init-enumerator :after
    ((e memo-enumerateur))
  (set-memo-res e))

(defmethod enum-found
    ((e memo-enumerateur))
  (enum-found (enum-res e)))
(defmethod enum-object
    ((e memo-enumerateur))
  (enum-object (enum-res e)))