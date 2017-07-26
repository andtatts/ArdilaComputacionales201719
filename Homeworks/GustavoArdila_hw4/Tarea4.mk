PuntoNemo.pdf: Plots.py
    python -lm Plots.py
Plots.py: out.x
    ./out.x
out.x: PuntoGeographicPoint.c
    cc PuntoGeographicPoint.c -o out.x