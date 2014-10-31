all: trayectoria3d.pdf proyeccion2d.pdf

trayectoria3d.pdf: trayectoria_1_30.dat
	python graficas.py trayectoria_1_30.dat

trayectoria_1_30.dat:particle_in_field.x graficas.py
	./particle_in_field.x 1 30

particle_in_field.x: particle_in_field.c
	cc particle_in_field.c -o particle_in_field.x -lm

proyeccion2d.pdf: trayectoria_1_30.dat
	python graficas.py trayectoria_1_30.dat

trayectoria_1_30.dat:particle_in_field.x graficas.py
	./particle_in_field.x 1 30

particle_in_field.x: particle_in_field.c
	cc particle_in_field.c -o particle_in_field.x -lm


clean:
	rm -f *.pdf
