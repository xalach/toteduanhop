(defclass memo-enumerator (unaire-combinaison-enumerator)
  ((depend-result :accessor depend-result :initform (make-depend-result)))
  (:documentation "énumérateur avec une memoire"))

; Il manque les defgeneric pour certain defmethod

(defmethod make-memo-enumerator ((e abstract-enumerator))
  (init-enumerator
   (make-instance ’memo-enumerator :depend (copy-enumerator e))))

(defmethod set-memo-result ((e memo-enumerator))
  (set-depend-result (depend-result e) (depend e)))

(defmethod init-enumerator :after ((e memo-enumerator))
  (set-memo-result e))

(defmethod trouve-depend ((e memo-enumerator))
  (trouve-depend (depend-result e)))

(defmethod objet-depend ((e memo-enumerator))
  (objet-depend (depend-res e)))