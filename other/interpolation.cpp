#include <iostream>

#define NUMBER_POINTS 5;

using namespace std;


typedef struct {
	float x;
	float y;
} ponto;

int main(int argc, char** argv)
{
	ponto* p1 = (ponto*) malloc(sizeof(ponto));
	ponto* p2 = (ponto*) malloc(sizeof(ponto));

	p1->x = 0;
	p1->y = 0;

	p2->x = 2;
	p2->y = 5;

	float currentX = p1->x;
	float sumFactor = (p2->x - p1->x) / NUMBER_POINTS;
	int contador = 0;
	while( currentX < p2->x ){
	 	float y = p1->y + ( (p2->y - p1->y)* ((currentX - p1->x)/(p2->x - p1->x)));
		cout << "P" << contador << " = ( " <<  currentX << ", " << y << " )" << endl;
		currentX += sumFactor;
		contador++;
	}
	cout << "P" << contador << " = ( 2, 5 ) " << endl;

	free(p1);
	free(p2);
}
