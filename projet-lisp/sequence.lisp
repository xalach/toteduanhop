(defclass sequence-enumerator (nnaire-combinaison-enumerator)
  ((restant-enumerators :type list :initarg :restant-enumerators :accessor restant-enumerators)))

(defmethod move-to-nonempty-sequence ((e sequence-enumerator))
  (loop
    while (restant-enumerators e)
    until (next-element-p (first (restant-enumerators e)))
    do (pop (restant-enumerators e))))

(defmethod init-enumerator :after ((e sequence-enumerator))
  (setf (restant-enumerators e) (sous-enumerators e))
  (move-to-nonempty-sequence e)))

(defun make-sequence-enumerator (depends)
  (assert (not (null depends)))
  (setf enums (mapcar #’copy-enumerator depends))
  (make-instance ’sequence-enumerator :sous-enumerators depends :restant-enumerators depends))

(defmethod next-element-p ((e sequence-enumerator))
  (let ((re (restant-enumerators e)))
    (and re (next-element-p (first re)))))

(defmethod next-element ((e sequence-enumerator))
  (prog1
    (next-element (first (restant-enumerators e)))
    (move-to-nonempty-sequence e)))
