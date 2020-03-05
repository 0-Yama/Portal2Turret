
/*********************************************************/
/*        TP1: primitives 2D et transformations          */
/*********************************************************/
/*													     */
/*       ESGI: Algorithmiques pour l'infographies		 */
/*													     */
/*********************************************************/
/*													     */
/*  Objectif: afficher des formes 2D et les transformer  */
/*													     */
/*********************************************************/



#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//#include <GL/glut.h>
#endif
#include<math.h>
#include<glut.h>
#include<stdlib.h>
#include<stdio.h>




float alpha    = 0.0;
float phi      = 0.0;
float rayon    = 5.0;
float pasAngle = 0.1;
float pasRayon = 0.1;
/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // modélisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise à jour: appelle Timer pour l'animation de la scène
void keyboard(unsigned char key, int x, int y); // fonction clavier




float F1x(float x){
    return x*x-0.25*x;
}
float F2x(float x){
    return x*x*0.25;
}


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)


	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fenêtre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("TP1: formes 2D et transformation");  // nom

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appelées par glut */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est passée en argument à une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en même temps)
	alors qu'il ne les connaît pas par avance.*/


	/* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();         // lancement de la boucle de réception des évènements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* définit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  définit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Création de la scène */
void display(){

	/* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
	rq: buffer: mémoire tampon, c'est donc une surface en memoire utilisée pour stocker une image*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* la mat de visualisation-modélisation est modifiable par défaut */
	glMatrixMode(GL_MODELVIEW);

	/* on charge l'identité dans la matrice de modélisation-visualisation*/
	glLoadIdentity();


	/* Permet de créer un point de vue. Définit une matrice de modélisation-visualisation et la multiplie
	à droite de lma matrice active, ici l'identité*/

	gluLookAt((rayon*cos(phi)*sin(alpha)), (rayon*sin(phi)), (rayon*cos(phi)*cos(alpha)),      // position caméra
		      0.0, 0.0, 0.0,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation caméra






	/* A vous de jouer */

    glPushMatrix();
        glScalef(0,0,0);
        glutSolidSphere(0.5, 50, 50);

    glPopMatrix();


	/* On swap (échange) les buffers, càd, on fait passer l'image calculée et dessinée
	dans le back buffer au buffer qui va l'afficher: le front buffer (en général), c'est le bouble buffering
	Cela évite une image animée sacadée, si elle était directement tracée dans le front buffer*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush(); // nettoie les fenêtres précédentes
}



/*  Mise en forme de la scène pour l'affichage */
void reshape(int w,  // w: largeur fenêtre
			 int h)  // h: hauteur fenêtre
{
	/* Viewport: cadrage. Spécifie la région (position et taille en px) que l'image observée de la scène occupe
	à l'écran => réduction et agrandissement de l'image possible*/
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);

	/* Spécifie que la matrice de projection va être modifiée  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();             // matrice courante: l'identité
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	/* Perspective avec point de fuite */
	gluPerspective(60.0,                       // angle d'ouverture vertical caméra
				   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
				   1.0,						   // plan proche z=1
				   200.0);                     // plan éloigné z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a été pressée
                    int x, int y) {    // Coordonnées courante de la souris

		switch (key){
            case 's':
                phi+=phi<3.14/2-pasAngle?pasAngle:0;
                glutPostRedisplay();
                break;
             case 'z':
                phi-=phi>-3.14/2+pasAngle?pasAngle:0;
                glutPostRedisplay();
                break;
            case 'd':
                alpha-=alpha==0?6.28:pasAngle;
                glutPostRedisplay();
                break;
             case 'q':
                alpha+=alpha==6.28?-6.28:pasAngle;
                glutPostRedisplay();
                break;
            case 'a':
                rayon+=pasRayon;
                glutPostRedisplay();
                break;
             case 'e':
                rayon-=rayon==3?0:pasRayon;
                glutPostRedisplay();
                break;
			case 'w':   /* Quitter le programme */
				exit(0);
		}
}
