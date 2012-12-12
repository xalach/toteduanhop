(defclass filtrage-enumerator (unaire-combinaison-enumerator fun-mixin)
  ())

(defgeneric skip-to-next (enumerator)
  (:documentation "que fait cette fonction ?"))

; ~~~~~ MANQUE (ou je sais pas ou c'est défini) ~~~~~~
; (defun set-memo-result (depend enum) ... )
; (defun trouve-depend (depend enum) ... )
; (defun objet-depend (depend e) ... )

(defmethod skip-to-next ((e filtrage-enumerator))
  (loop
     while (trouve-depend (depend e))
     until (funcall (fun e) (objet-depend (depend e)))
     do (set-memo-result (depend e))))

; à définir
(defmethod copy-enumerator ((e filtrage-enumerator))
  )

(defmethod init-enumerator :after ((e filtrage-enumerateur))
  (skip-to-next e))

(defmethod next-element-p ((e filtrage-enumerateur))
  (trouve-depend (depend e)))

(defmethod next-element ((e filtrage-enumerator))
  (prog1
      (objet-depend (depend e))
    (set-memo-result (depend e))
    (skip-to-next e)))

(defmethod make-filtrage-enumerateur ((e abstract-enumerator) filter-fun)
  (init-enumerator
   (make-instance
    ’filtrage-enumerateur
     :depend (make-memo-enumerator e)
     :fun filter-fun)))