(defclass memo-enumerator (unaire-combinaison-enumerator)
  ((depend-res :accessor depend-res :initform (make-depend-res)))
  (:documentation "énumérateur avec une memoire"))

; Il manque les defgeneric pour certain defmethod

(defmethod make-memo-enumerator ((e abstract-enumerator))
  (init-enumerator
   (make-instance ’memo-enumerator :enum (copy-enumerator e))))

(defmethod set-memo-res ((e memo-enumerator))
  (set-depend-res (depend-res e) (depend e)))

(defmethod init-enumerator :after ((e memo-enumerator))
  (set-memo-res e))

(defmethod trouve-depend ((e memo-enumerateur))
  (trouve-depend (depend-res e)))

(defmethod objet-depend ((e memo-enumerator))
  (objet-depend (depend-res e)))