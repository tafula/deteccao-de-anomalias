LIBS = `pkg-config --libs opencv` 

all: learner tester AnomalyDetection

clean:
	chmod +x clean.sh
	./clean.sh

learner:
	g++ -o learner code/learner.cpp -O2 -I/usr/include/opencv -I/usr/local/include/opencv -L/usr/lib -L/usr/local/lib -larmadillo $(LIBS)	
tester:
	g++ -o tester code/tester.cpp -O2 -I/usr/include/opencv -I/usr/local/include/opencv -L/usr/lib -L/usr/local/lib -larmadillo $(LIBS)

AnomalyDetection:
	g++ -o AnomalyDetection code/main.cpp code/ParameterInfo.cpp code/DisplayImage.cpp code/AnomalyDetection.cpp -O2 -I/usr/include/opencv -I/usr/local/include/opencv -L/usr/lib -L/usr/local/lib -larmadillo $(LIBS)
