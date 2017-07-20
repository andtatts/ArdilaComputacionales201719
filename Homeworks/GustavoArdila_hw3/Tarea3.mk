Resultados_hw3.pdf: Resultados_hw3.tex Resultados_1.png orbitas.png
    pdflatex Resultados_hw3.tex
Resultados_1.png: Onda.py
    python Onda.py
orbitas.png: Plots_planetas.py
    python Plots_planetas.py
Plots_planetas.py: datos_x.txt datos_y.txt datos_z.txt
    python Plots_planetas.py
datos_x.txt: plans.x
    ./plans.x
plans.x : Planetas.c
    cc Planetas.c -o plans.x