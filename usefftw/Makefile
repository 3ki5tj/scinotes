prj = usefftw

tex = $(wildcard *.tex)
dvi = $(patsubst %.tex, %.dvi, $(tex))
pdf = $(patsubst %.tex, %.pdf, $(tex))
html = $(patsubst %.tex, %.html, $(tex))
htmldir = $(patsubst %.tex, %_html, $(tex))

c = $(wildcard *.c)
bin = $(filter-out 2d_t 2d_mpi, $(patsubst %.c, %, $(c)))
CC = gcc -Wall -Wextra
LM = -lfftw3 -lm

binx = 2d_th 2d_mp 2d_mpi

all: $(pdf) $(bin) $(binx)

$(pdf) : %.pdf: %.tex %.dvi
	pdflatex $<

$(dvi) : %.dvi: %.tex
	latex $<

# compile to latex .dvi first to figure out references

$(htmldir) : %_html : %.tex
	if [ ! -d "$@" ] ; then mkdir "$@" ; fi
	cd $@; ln -sf ../$< ../*.c .; htlatex $<

# html versions by tth are more basic and have problems
$(html) : %.html : %.tex
	tth -i $<

# -i: means to use italic font for equations

$(bin) : % : %.c
	$(CC) -o $@ $< $(LM)

2d_th : 2d_t.c
	$(CC) -o $@ $< -lfftw3_threads -lpthread $(LM)

2d_mp : 2d_t.c
	$(CC) -fopenmp -o $@ $< -lfftw3_omp $(LM) -L$(HOME)/app/lib

2d_mpi : 2d_mpi.c
	mpicc -Wall -Wextra -o $@ $< -lfftw3_mpi -lfftw3 $(LM) \
	  -I$(HOME)/app/include -L$(HOME)/app/lib

$(prj).zip: $(c) $(tex) Makefile
	zip $@ $^

zip: $(prj).zip

Bossman: $(pdf) $(c) $(prj).zip
	rsync -avzrL *.pdf *.tex *.c $(prj).zip cz1@he.host.utmb.edu:/Bossman/cz1/notes/$(prj)

# upload to github
github:
	git push origin master

push: github

clean:
	rm -f *~ *.out *.dat *.dvi *.aux *.log *.toc *.idv *.lg .*.un~
	rm -rf $(bin) $(binx) $(prj).zip
	rstrip.py

.PHONY: clean all

