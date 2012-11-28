(defclass conca-enumerateur
      (unary-relying-enumerator)
  ((next-elements
    :initform nil
    :accessor next-elements))
  )

(defmethod skip-to-next-non-null
    ((e conca-enumerateur))
  (loop
    until (next-elements e)
    while (next-element-p (enum e))
do (setf (next-elements e)
	 (next-element (enum e)))))

(defmethod init-enumerator :after
    ((e conca-enumerateur))
  (skip-to-next-non-null e))

(defmethod next-element-p
    ((e conca-enumerateur))
  (next-elements e))

(defmethod next-element
    ((e conca-enumerateur))
  (prog1
      (pop (next-elements e))
    (skip-to-next-non-null e)))

(defmethod make-conca-enumerateur
    ((e abstract-enumerator))
  (init-enumerator
   (make-instance
    ’conca-enumerateur
     :enum (copy-enumerator e))))