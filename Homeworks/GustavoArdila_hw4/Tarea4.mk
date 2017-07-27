PuntoNemo.pdf : Plots.py
	python  Plots.py
Plots.py : out.x
	./out.x
out.x : PuntoGeographicPoint.c
	cc PuntoGeographicPoint.c -lm -o out.x
