(defun matrizes()
	
	(format t "L1221F25 - José Guilherme Vanz ~1%")
	(setf matriz1 (make-array '(3 3)))
	(setf matriz2 (make-array '(3 3)))
	(setf matriz3 (make-array '(3 3)))

	(format t "~1%Leitura de M1~1%")
	(loop for linha from 0 to 2 do
		(loop for coluna from 0 to 2 do
			(format t "Informe o elemento ~D,~D de M1:" linha coluna )
			(setf (aref matriz1 linha coluna ) (read))			
		)
	)

	(format t "~1%Leitura de M2~1%")
	(loop for linha from 0 to 2 do
		(loop for coluna from 0 to 2 do
			(format t "Informe o elemento ~D,~D de M2: "linha coluna)				
			(setf (aref matriz2 linha coluna) (read))			
		)
	)

	(loop for linha from 0 to 2 do
		(loop for coluna from 0 to 2 do
			(setf result 0)
			(loop for x from 0 to 2 do
				(setf result (+ result (* (aref matriz1 linha x) (aref matriz2 x coluna))))			
			)
			(setf (aref matriz3 linha coluna) result)
		)
	)

	(format t "Listagem Matriz~1%")
	(format t "L1221F25 - José Guilherme Vanz ~1%")

	(format t "M1~1%")
	(loop for x from 0 to 2 do
		(loop for y from 0 to 2 do
			(format t "~4D " (aref matriz1 x y))
		)
		(format t "~1%")
	)

	(format t "~1%M2~1%")
	(loop for z from 0 to 2 do
		(loop for w from 0 to 2 do
			(format t "~4D " (aref matriz2 z w))
		)
		(format t "~1%")
	)
	
	(format t "~1%M3~1%")
	(loop for a from 0 to 2 do
		(loop for b from 0 to 2 do
			(format t "~4D " (aref matriz3 a b))
		)
		(format t "~1%")
	)
	

)
(matrizes)
